include(FetchContent)
FetchContent_Declare(libopencm3
        GIT_REPOSITORY https://github.com/libopencm3/libopencm3
        GIT_TAG master
        )
FetchContent_MakeAvailable(libopencm3)
FetchContent_GetProperties(libopencm3)

add_custom_target(libopencm3 make TARGETS=stm32/f4 WORKING_DIRECTORY ${libopencm3_SOURCE_DIR})



add_library(stm32f4 STATIC IMPORTED GLOBAL)

set_property(TARGET stm32f4 PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${libopencm3_SOURCE_DIR}/include)
set_property(TARGET stm32f4 PROPERTY IMPORTED_LOCATION
        ${libopencm3_SOURCE_DIR}/lib/libopencm3_stm32f4.a)
add_dependencies(stm32f4 libopencm3)
target_link_directories(stm32f4 INTERFACE ${libopencm3_SOURCE_DIR}/lib)

target_compile_definitions(stm32f4 INTERFACE -DSTM32F4)

set(COMPILE_OPTIONS
        --static
        -nostartfiles
        -fno-common
        -mcpu=cortex-m4
        -mthumb
        -mfloat-abi=hard
        -mfpu=fpv4-sp-d16
        )
target_compile_options(stm32f4 INTERFACE ${COMPILE_OPTIONS})
target_link_options(stm32f4 INTERFACE ${COMPILE_OPTIONS})


#execute_process(COMMAND make -C ${PROJECT_SOURCE_DIR}/libopencm3)

