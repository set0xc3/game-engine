const std = @import("std");
const Step = std.build.Step;
const CrossTarget = std.zig.CrossTarget;

const flags = [_][]const u8{
    // "-pedantic",
    "-Wall",
    "-Wextra",
    "-Werror",
    "-Wuninitialized",

    "-Wno-unused-parameter",
    "-Wno-unused-variable",
    "-Wno-unused-but-set-variable",
    "-Wno-macro-redefined",
    "-Wno-attributes",
    "-Wno-incompatible-library-redeclaration",

    "-gen-cdb-fragment-path",
    "cdb",
    "-std=c11",
};

const iflags = [_][]const u8{
    "-I",
    "core/src",
    "-I",
    "editor/src",
    "-I",
    "engine/src",
    "-I",
    "game/src",
    "-I",
    "runtime/src",
};

pub fn platform_settings(step: *Step.Compile, target: CrossTarget) void {
    if (target.os_tag.? == .linux) {
        step.addIncludePath("/usr/include");
        step.addLibraryPath("/usr/lib");
        step.linkSystemLibrary("c");
        step.linkSystemLibrary("m");
        step.linkSystemLibrary("uuid");
        step.linkSystemLibrary("SDL2");
    } else if (target.os_tag.? == .windows) {
        step.addIncludePath("/usr/x86_64-w64-mingw32/include");
        step.addLibraryPath("/usr/x86_64-w64-mingw32/bin");
        step.addLibraryPath("/usr/x86_64-w64-mingw32/lib");
        step.linkSystemLibrary("user32");
        step.linkSystemLibrary("gdi32");
        step.linkSystemLibrary("winmm");
        step.linkSystemLibrary("setupapi");
        step.linkSystemLibrary("oleaut32");
        step.linkSystemLibrary("ole32");
        step.linkSystemLibrary("imm32");
        step.linkSystemLibrary("version");
        step.linkSystemLibrary("SDL2");
        step.linkSystemLibrary("SDL2main");
    }
}

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const lib_core = b.addStaticLibrary(.{
        .name = "core",
        .target = target,
        .optimize = optimize,
    });
    lib_core.addCSourceFile("core/src/core/core.c", &flags ++ iflags);
    lib_core.linkSystemLibrary("c");
    lib_core.linkLibC();
    platform_settings(lib_core, target);
    b.installArtifact(lib_core);

    // Build engine
    const engine = b.addExecutable(.{
        .name = "engine",
        .target = target,
        .optimize = optimize,
    });
    engine.addCSourceFile("engine/src/engine/engine.c", &flags ++ iflags);
    engine.addLibraryPath("zig-out/lib");
    engine.linkSystemLibrary("core");
    engine.linkSystemLibrary("c");
    engine.linkLibC();
    platform_settings(engine, target);
    b.installArtifact(engine);

    // `zig build run -- arg1 arg2 etc`
    {
        const run_cmd = b.addRunArtifact(engine);
        run_cmd.step.dependOn(b.getInstallStep());
        if (b.args) |args| {
            run_cmd.addArgs(args);
        }

        const run_step = b.step("run:engine", "Run the app");
        run_step.dependOn(&run_cmd.step);
    }

    // Build game
    const lib_game = b.addSharedLibrary(.{
        .name = "game",
        .target = target,
        .optimize = optimize,
    });
    lib_game.addCSourceFile("game/src/game/game.c", &flags ++ iflags);
    lib_game.addLibraryPath("zig-out/lib");
    lib_game.linkSystemLibrary("core");
    lib_game.linkSystemLibrary("c");
    lib_game.linkLibC();
    platform_settings(lib_game, target);
    // b.installArtifact(lib_game);

    // Build runtime
    const runtime = b.addExecutable(.{
        .name = "runtime",
        .target = target,
        .optimize = optimize,
    });
    runtime.addCSourceFile("runtime/src/runtime/runtime.c", &flags ++ iflags);
    runtime.addLibraryPath("zig-out/lib");
    runtime.linkSystemLibrary("core");
    runtime.linkSystemLibrary("c");
    runtime.linkLibC();
    platform_settings(runtime, target);
    // b.installArtifact(runtime);
}
