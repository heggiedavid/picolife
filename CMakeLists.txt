cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)
include(pimoroni_pico_import.cmake)

project(unicorn_blink)

pico_sdk_init()

add_executable(unicorn_blink
	unicorn_blink.cpp
)

pico_add_extra_outputs(unicorn_blink)

target_link_libraries(unicorn_blink pico_stdlib hardware_pio hardware_dma pico_unicorn)

add_subdirectory(../pimoroni-pico/common pimoroni-common)
add_subdirectory(../pimoroni-pico/drivers pimoroni-drivers)
add_subdirectory(../pimoroni-pico/libraries pimoroni-libraries)