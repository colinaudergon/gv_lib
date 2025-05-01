cmake_minimum_required(VERSION 3.16)

project(i2s_example)

add_executable(i2s_example i2s_example.c)

target_link_libraries(i2s_example PRIVATE gv_lib)

pico_add_extra_outputs(i2s_example)
pico_enable_stdio_usb(i2s_example 1)
pico_enable_stdio_uart(i2s_example 1)