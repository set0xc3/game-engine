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

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE ${PROJECT_SOURCE_DIR}/src /usr/include
)

target_link_libraries(${PROJECT_NAME} PRIVATE /usr/lib)

# target_include_directories(
#     ${PROJECT_NAME}
#     PRIVATE ${PROJECT_SOURCE_DIR}/src /usr/x86_64-w64-mingw32/include
# )

# target_link_libraries(
#     ${PROJECT_NAME}
#     PRIVATE /usr/x86_64-w64-mingw32/bin /usr/x86_64-w64-mingw32/lib
# )

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
    target_link_libraries(${PROJECT_NAME} PRIVATE mingw32 SDL2 SDL2main)
elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
    target_link_libraries(${PROJECT_NAME} PRIVATE m uuid SDL2 SDL2main)
endif()
