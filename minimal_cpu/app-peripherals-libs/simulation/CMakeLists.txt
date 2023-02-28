cmake_minimum_required(VERSION 3.11)

project(uart_library)

add_library(${PROJECT_NAME} STATIC src/simulation_uart.c)

target_include_directories(${PROJECT_NAME}
        PUBLIC ${PROJECT_SOURCE_DIR}/../../include)

set(add_linker_script_dir ${CMAKE_CURRENT_LIST_DIR} CACHE INTERNAL "")

function(add_linker_script TARGET VISIBILITY)
    # Nothing to do here
endfunction()

function(add_platform_libraries TARGET)
    # linux specific libraries linked
endfunction()

