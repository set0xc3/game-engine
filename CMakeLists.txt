cmake_minimum_required(VERSION 3.10)

project(game-engine)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(TARGET_ARCHITECTURE "x64")

set(CORE_SOURCE_DIR ${PROJECT_SOURCE_DIR}/core/src)
set(EDITOR_SOURCE_DIR ${PROJECT_SOURCE_DIR}/editor/src)
set(ENGINE_SOURCE_DIR ${PROJECT_SOURCE_DIR}/engine/src)
set(GAME_SOURCE_DIR ${PROJECT_SOURCE_DIR}/game/src)

if(CMAKE_BUILD_TYPE STREQUAL "debug")
    add_compile_definitions(BUILD_TYPE_DEBUG)
endif()

add_subdirectory(core)
add_subdirectory(editor)
add_subdirectory(engine)
add_subdirectory(game)
