cmake_minimum_required(VERSION 3.10)
project(game)

set(PROJECT_SOURCES ${PROJECT_SOURCE_DIR}/src/${PROJECT_NAME}/game.c)

add_compile_definitions(LIBRARY_SHARED)
add_library(${PROJECT_NAME} SHARED ${PROJECT_SOURCES})

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE ${PROJECT_SOURCE_DIR}/src ${CORE_SOURCE_DIR} ${ENGINE_SOURCE_DIR}
)

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
    target_link_libraries(${PROJECT_NAME} PRIVATE core)
endif()
