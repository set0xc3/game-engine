const std = @import("std");
const Step = std.build.Step;
const CrossTarget = std.zig.CrossTarget;

const flags = [_][]const u8{
    // "-Wall",
    // "-Wextra",
    // "-Werror",
    "-gen-cdb-fragment-path", "cdb",
    // "-MJ",                    "compile_commands.json",
    "-std=c99",
};

const iflags = [_][]const u8{ "-I", "core/src", "-I", "game/src", "-I", "runtime/src", "-I", "editor/src" };
const lflags = [_][]const u8{ "-L", "zig-out/lib" };
const dflags = [_][]const u8{ "-D", "LIBRARY_SHARED" };

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
    lib_core.addCSourceFile("core/src/core/core.c", &flags ++ iflags ++ dflags);
    lib_core.linkSystemLibrary("c");
    lib_core.linkLibC();
    platform_settings(lib_core, target);
    b.installArtifact(lib_core);

    // Build game
    const lib_game = b.addSharedLibrary(.{
        .name = "game",
        .target = target,
        .optimize = optimize,
    });
    lib_game.addCSourceFile("game/src/game/game.c", &flags ++ iflags ++ lflags);
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
    runtime.addCSourceFile("runtime/src/runtime/runtime.c", &flags ++ iflags ++ lflags);
    runtime.addLibraryPath("zig-out/lib");
    runtime.linkSystemLibrary("core");
    runtime.linkSystemLibrary("c");
    runtime.linkLibC();
    platform_settings(runtime, target);
    // b.installArtifact(runtime);
}
