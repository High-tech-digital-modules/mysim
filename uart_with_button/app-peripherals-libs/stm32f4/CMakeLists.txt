cmake_minimum_required(VERSION 3.11)

project(uart_library)

include(cmake/stm32f4.cmake)

add_library(${PROJECT_NAME} STATIC src/stm32f4_uart.c)

target_include_directories(${PROJECT_NAME}
        PUBLIC ${PROJECT_SOURCE_DIR}/../../include ${libopencm3_SOURCE_DIR}/include)

add_dependencies(${PROJECT_NAME} stm32f4)


target_compile_options(${PROJECT_NAME} PRIVATE ${COMPILE_OPTIONS})

set(add_linker_script_dir ${CMAKE_CURRENT_LIST_DIR} CACHE INTERNAL "")

function(add_linker_script TARGET VISIBILITY)
    get_filename_component(SCRIPT "${add_linker_script_dir}/stm32f4.ld" ABSOLUTE)
    target_link_options(${TARGET} ${VISIBILITY} -T "${SCRIPT}")
endfunction()

function(add_platform_libraries TARGET)
    target_link_libraries(${TARGET} stm32f4)
endfunction()


#execute_process(COMMAND make -C ${PROJECT_SOURCE_DIR}/libopencm3)

