cmake_minimum_required(VERSION 3.16)

project(delay_line_example C CXX ASM)

set(CMAKE_C_STANDARD 11)


add_executable(delay_line_example main.c)

target_link_libraries(delay_line_example
PRIVATE gv_lib )


pico_add_extra_outputs(delay_line_example)
pico_enable_stdio_usb(delay_line_example 1)
pico_enable_stdio_uart(delay_line_example 1)