cmake_minimum_required(VERSION 3.10)
project(engine)

set(PROJECT_SOURCES ${PROJECT_SOURCE_DIR}/src/${PROJECT_NAME}/engine.c)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE ${PROJECT_SOURCE_DIR}/src ${CORE_SOURCE_DIR}
)

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
    if(LAYER_TARGET STREQUAL "engine")
        add_compile_definitions(LAYER_TARGET_NONE)
        target_link_libraries(${PROJECT_NAME} PRIVATE core)
    else()
        target_link_libraries(${PROJECT_NAME} PRIVATE core ${LAYER_TARGET})
    endif()
endif()

add_custom_target(
    run
    COMMAND cd ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} && ./${PROJECT_NAME} ${ARGS}
)
