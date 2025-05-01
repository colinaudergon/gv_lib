#ifndef _DSP_PROFFILER_H_
#define _DSP_PROFFILER_H_

#include "pico/stdlib.h"

typedef void (*fn_profile)(void* argv);

typedef struct {
    uint gpio;
    fn_profile fn;
}dsp_profiler_t;


dsp_profiler_t* dsp_profiler_init(uint gpio, fn_profile fn_to_profile);

int profile(dsp_profiler_t *profiler, void *args);

#endif /*_DSP_PROFFILER_H_*/