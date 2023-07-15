cmake_minimum_required(VERSION 3.10)
project(core)

set(CMAKE_C_STANDARD 99)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(TARGET_ARCHITECTURE "x64")

set(PROJECT_SOURCES
    ${PROJECT_SOURCE_DIR}/src/${PROJECT_NAME}/core.c
)

if(BUILD_SHARED_LIBS STREQUAL "ON")
    add_compile_definitions(BUILD_LIB_SHARED)
    option(BUILD_SHARED_LIBS "Build shared libraries" ON)
endif()

add_library(${PROJECT_NAME}
    ${PROJECT_SOURCES}
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${PROJECT_SOURCE_DIR}/src
)

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
target_link_libraries(${PROJECT_NAME} PRIVATE
    dl m SDL2 SDL2_mixer SDL2_image
)
endif()
