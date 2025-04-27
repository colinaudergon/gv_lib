cmake_minimum_required(VERSION 3.13)

# Define the library name
project(pico_gv_ui)

if(USE_GV_LIB)
message(STATUS "Lib used via gv_lib")
else()
message(STATUS "Lib used directly")
endif()

include_directories(lib/pico-ssd1306
)

# Add the library source files
add_library(pico_gv_ui
    ui_functions/ui_functions.c
    lib/pico-ssd1306/ssd1306.c

    # ui_functions/ui_functions.h
)

# Include directories for the library
target_include_directories(pico_gv_ui PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/ui_functions
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/pico-ssd1306
)

# Link with Pico SDK (if applicable)
target_link_libraries(pico_gv_ui pico_stdlib hardware_i2c)