cmake_minimum_required(VERSION 3.12)

# Pull in SDK (must be before project)
include(/home/pi/develop/pico/pico-sdk/external/pico_sdk_import.cmake)
# include(/home/pi/develop/pico/pico-sdk/external/pico_extras_import_optional.cmake)
project(own C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)
if (PICO_SDK_VERSION_STRING VERSION_LESS "1.3.0")
    message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.3.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()
set(PICO_EXAMPLES_PATH ${PROJECT_SOURCE_DIR})
# Initialize the SDK
pico_sdk_init()
# include(example_auto_set_url.cmake)
add_compile_options(-Wall
        -Wno-format          # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
        -Wno-unused-function # we have some for the docs that aren't called
        -Wno-maybe-uninitialized
        )


add_executable(blink main.cpp)
# pull in common dependencies
target_link_libraries(blink pico_stdlib pico_multicore)
# create map/bin/hex file etc.
pico_add_extra_outputs(blink)        
# Serial through USB
# pico_enable_stdio_usb(blink 1)
# Serial through pin outs
pico_enable_stdio_uart(blink 1)


#add_executable(led 
#    ws28128-rpi/ws2812-rpi-test.cpp
#    ws28128-rpi/ws2812-rpi.cpp
#)