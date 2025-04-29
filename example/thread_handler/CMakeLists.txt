cmake_minimum_required(VERSION 3.16)

project(thread_handler_example)

add_executable(thread_handler_example main.c)


target_link_libraries(thread_handler_example PRIVATE gv_lib)

pico_add_extra_outputs(thread_handler_example)
pico_enable_stdio_usb(thread_handler_example 1)
pico_enable_stdio_uart(thread_handler_example 1)