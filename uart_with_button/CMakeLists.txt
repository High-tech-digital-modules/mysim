cmake_minimum_required(VERSION 3.18)
project(mysim C)

if(NOT DEFINED BOARD)
    message( SEND_ERROR "BOARD variable must be one of \"stm32f4\", \"simulation\"" )
endif(NOT DEFINED BOARD)

if(BOARD STREQUAL "simulation")
    add_definitions(-DSIMULATION)
endif()

set(CMAKE_C_STANDARD 11)

add_subdirectory(app-peripherals-libs/${BOARD})
add_subdirectory(app-business-logic)
