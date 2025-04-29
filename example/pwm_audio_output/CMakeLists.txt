cmake_minimum_required(VERSION 3.16)

project(pwm_audio_output_example C CXX ASM)

set(CMAKE_C_STANDARD 11)


add_executable(pwm_audio_output_example main.c)

target_link_libraries(pwm_audio_output_example
PRIVATE gv_lib hardware_adc)


pico_add_extra_outputs(pwm_audio_output_example)
pico_enable_stdio_usb(pwm_audio_output_example 1)
pico_enable_stdio_uart(pwm_audio_output_example 1)