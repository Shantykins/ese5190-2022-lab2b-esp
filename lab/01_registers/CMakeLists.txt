cmake_minimum_required(VERSION 3.13) # CMAKE (heading)
include(pico_sdk_import.cmake) # CMAKE -> PICO SDK (include)

project(registers C CXX ASM) # CMAKE ("project")
pico_sdk_init() # PICO SDK (initialization)

include(example_auto_set_url.cmake)


add_executable(registers) # CMAKE (target)

pico_generate_pio_header(registers ${CMAKE_CURRENT_LIST_DIR}/ws2812.pio OUTPUT_DIR ${CMAKE_CURRENT_LIST_DIR}/generated) # PICO SDK (PIO)

target_sources(registers PRIVATE registers.c neopixel.c) # CMAKE -> C (compiler)
target_link_libraries(registers PRIVATE pico_stdlib hardware_pio) # CMAKE -> C (linker)

pico_enable_stdio_usb(registers 1) # PICO SDK (USB)
pico_enable_stdio_uart(registers 0) # PICO SDK (USB)

pico_add_extra_outputs(registers) # PICO SDK (UF2)
