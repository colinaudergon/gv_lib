cmake_minimum_required(VERSION 3.16)

project(gv_lfsr)

set(GV_LFSR_SRC "")
set(GV_LFSR_DEP "")
set(GV_LFSR_INC "")

set(
    GV_LFSR_SRC
    src/gv_lfsr.c
)

set(GV_LFSR_INC
${CMAKE_CURRENT_SOURCE_DIR}/include
)

set( GV_LFSR_DEP
    pico_stdlib
)

add_library(gv_lfsr ${GV_LFSR_SRC})
target_include_directories(gv_lfsr PUBLIC ${GV_LFSR_INC})
target_link_libraries(gv_lfsr  ${GV_LFSR_DEP})
