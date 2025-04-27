cmake_minimum_required(VERSION 3.16)

include(pico_sdk_import.cmake)

set(USE_GV_LIB true CACHE INTERNAL "Global flag for using gv_lib")
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/functions.cmake)


set(PROJECT_NAME "gv_lib") 
project(${PROJECT_NAME} C CXX ASM)

pico_sdk_init()

set(GV_LIB_CONF_FILE ${CMAKE_CURRENT_SOURCE_DIR}/gv_lib_conf.h)


set(CUSTOM_LIB_DEP "")

check_macro_defined_global(GV_LIB_USE_SSD1306 USE_SSD1306)
check_macro_defined_global(GV_LIB_USE_LED_PWM USE_LED_PWM)
check_macro_defined_global(GV_LIB_USE_LED_PWM USE_LED_PWM)
check_macro_defined_global(GV_LIB_USE_WAV_READER_SPI USE_WAV_READER_SPI)

if (USE_SSD1306)
    message(STATUS "Including pico_gv_ui")
    add_subdirectory(pico_gv_ui)
    list(APPEND CUSTOM_LIB_DEP pico_gv_ui)
endif()

if (USE_LED_PWM OR USE_ROTARY_ENCODER )
    message(STATUS "Including pico_gv_drivers")
    add_subdirectory(pico_gv_drivers)
    list(APPEND CUSTOM_LIB_DEP pico_gv_drivers)
endif()

if(USE_WAV_READER_SPI)
message(STATUS "Including gv_wav_reader")
add_subdirectory(gv_wav_reader)
list(APPEND CUSTOM_LIB_DEP gv_wav_reader)
endif()

add_library(gv_lib INTERFACE)

target_link_libraries(gv_lib INTERFACE
    pico_stdlib
    ${CUSTOM_LIB_DEP}
)

add_subdirectory(example)