cmake_minimum_required(VERSION 3.18)
project(uart_example)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_DEBUG_POSTFIX -d)

add_executable(${PROJECT_NAME} src/main.c)

target_include_directories(${PROJECT_NAME}
        PUBLIC ${PROJECT_SOURCE_DIR}/../include)

target_link_libraries(${PROJECT_NAME} uart_library)
add_platform_libraries(${PROJECT_NAME})

set_target_properties(${PROJECT_NAME}  PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})

add_linker_script(${PROJECT_NAME} PRIVATE)