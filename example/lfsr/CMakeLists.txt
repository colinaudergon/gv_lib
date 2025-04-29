cmake_minimum_required(VERSION 3.16)

project(lfsr_example C CXX ASM)

set(CMAKE_C_STANDARD 11)


add_executable(lfsr_example main.c)

target_link_libraries(lfsr_example
PRIVATE gv_lib )


pico_add_extra_outputs(lfsr_example)
pico_enable_stdio_usb(lfsr_example 1)
pico_enable_stdio_uart(lfsr_example 1)