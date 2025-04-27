cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
project(simple_example C CXX ASM)

add_executable(fat_fs_spi_sd_card_simple_example main.c)



target_link_libraries(fat_fs_spi_sd_card_simple_example
PRIVATE gv_lib)


pico_add_extra_outputs(fat_fs_spi_sd_card_simple_example)
pico_enable_stdio_usb(fat_fs_spi_sd_card_simple_example 1)
pico_enable_stdio_uart(fat_fs_spi_sd_card_simple_example 1)