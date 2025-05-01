cmake_minimum_required(VERSION 3.16)

project(oscillator_example C CXX ASM)

set(CMAKE_C_STANDARD 11)


add_executable(oscillator_example main.c)

target_link_libraries(oscillator_example
PRIVATE gv_lib hardware_adc pico_multicore)


pico_add_extra_outputs(oscillator_example)
pico_enable_stdio_usb(oscillator_example 1)
pico_enable_stdio_uart(oscillator_example 1)