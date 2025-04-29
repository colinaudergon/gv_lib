cmake_minimum_required(VERSION 3.13)

# Define the library name
project(logger)

add_library(logger
logger.h
)

target_include_directories(logger PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(logger pico_stdlib)