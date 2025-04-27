cmake_minimum_required(VERSION 3.16)

project(gv_wav_reader)

add_subdirectory(lib/no-OS-FatFS-SD-SPI-RPi-Pico/FatFs_SPI )

set(GV_WAV_READER_SRC "")
set(GV_WAV_READER_DEP "")
set(GV_WAV_READER_INC "")

set(
    GV_WAV_READER_SRC
    src/wav_reader.c
    src/hw_config.c
    src/file_handler.c
)

set(GV_WAV_READER_INC
${CMAKE_CURRENT_SOURCE_DIR}/include
)
set( GV_WAV_READER_DEP
    pico_stdlib
    FatFs_SPI
)

add_library(gv_wav_reader ${GV_WAV_READER_SRC})
target_include_directories(gv_wav_reader PUBLIC ${GV_WAV_READER_INC})
target_link_libraries(gv_wav_reader  ${GV_WAV_READER_DEP})