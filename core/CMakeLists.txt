cmake_minimum_required(VERSION 3.10)
project(core)

set(PROJECT_SOURCES ${PROJECT_SOURCE_DIR}/src/${PROJECT_NAME}/core.c)

if(LIBRARY_SHARED STREQUAL "ON")
    add_compile_definitions(LIBRARY_SHARED)
    add_library(${PROJECT_NAME} SHARED ${PROJECT_SOURCES})
else()
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)
    add_library(${PROJECT_NAME} STATIC ${PROJECT_SOURCES})
endif()

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/src)

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
    target_link_libraries(${PROJECT_NAME} PRIVATE m SDL2 SDL2_mixer SDL2_image)
endif()
