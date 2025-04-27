cmake_minimum_required(VERSION 3.16)

project(pico_gv_drivers_example)

add_executable(pico_gv_drivers_example main.c)

# target_include_directories(pico_gv_drivers_example PRIVATE
#     ${CMAKE_CURRENT_SOURCE_DIR}/../led_pwm
# )

target_link_libraries(pico_gv_drivers_example PRIVATE gv_lib)

pico_add_extra_outputs(pico_gv_drivers_example)
pico_enable_stdio_usb(pico_gv_drivers_example 1)
pico_enable_stdio_uart(pico_gv_drivers_example 1)