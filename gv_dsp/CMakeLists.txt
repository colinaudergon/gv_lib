cmake_minimum_required(VERSION 3.16)

project(gv_dsp)

set(PICO_GV_DSP_SRC "")
set(PICO_GV_DSP_INC "")
set(PICO_GV_DSP_DEP "")

#utils
list(APPEND PICO_GV_DSP_INC utils)

#dsp profiler

list(APPEND PICO_GV_DSP_INC dsp_profiler/include)
list(APPEND PICO_GV_DSP_SRC dsp_profiler/src/dsp_profiler.c)
list(APPEND PICO_GV_DSP_DEP pico_stdlib)

#filter
list(APPEND PICO_GV_DSP_INC filter/include)
list(APPEND PICO_GV_DSP_SRC filter/src/gv_filter.c)
list(APPEND PICO_GV_DSP_DEP pico_stdlib)

#delay line
list(APPEND PICO_GV_DSP_INC delay_line/include)
list(APPEND PICO_GV_DSP_INC delay_line/template/include)
list(APPEND PICO_GV_DSP_SRC delay_line/src/gv_delay_line.c)                            

#oscillator
list(APPEND PICO_GV_DSP_INC oscillator/include)
list(APPEND PICO_GV_DSP_SRC oscillator/src/gv_oscillator.c)

#pre existing effects
# clouds reverb
list(APPEND PICO_GV_DSP_INC dsp_effects/clouds_reverb/include)
list(APPEND PICO_GV_DSP_SRC dsp_effects/clouds_reverb/src/clouds_reverb.c)                


add_library(gv_dsp
    ${PICO_GV_DSP_SRC}
)

target_include_directories(gv_dsp PUBLIC ${PICO_GV_DSP_INC})
target_link_libraries(gv_dsp ${PICO_GV_DSP_DEP})

