cmake_minimum_required(VERSION 3.16)

project(gv_i2s_driver)

set(GV_I2S_DRIVER_SRC "")
set(GV_I2S_DRIVER_DEP "")
set(GV_I2S_DRIVER_INC "")

# Source files
set(GV_I2S_DRIVER_SRC
    rp2040_i2s_example/i2s.c
)

# Generate the PIO header file
pico_generate_pio_header(gv_i2s_driver ${CMAKE_CURRENT_LIST_DIR}/rp2040_i2s_example/i2s.pio)

# Include directories
set(GV_I2S_DRIVER_INC
    ${CMAKE_CURRENT_SOURCE_DIR}/rp2040_i2s_example
)

# Dependencies
set(GV_I2S_DRIVER_DEP
    pico_stdlib
    hardware_i2c
    hardware_dma
    hardware_pio
    hardware_clocks
)

# Add the library
add_library(gv_i2s_driver ${GV_I2S_DRIVER_SRC})

# Include the generated PIO header and source directories
target_include_directories(gv_i2s_driver PUBLIC ${GV_I2S_DRIVER_INC})

# Link the library with dependencies
target_link_libraries(gv_i2s_driver ${GV_I2S_DRIVER_DEP})