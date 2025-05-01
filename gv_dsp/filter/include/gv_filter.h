#ifndef _GV_FILTER_H_
#define _GV_FILTER_H_

#include "pico/stdlib.h"
#include <math.h>
#include <stdio.h>

#include "tan.h"

typedef enum {
    FILTER_MODE_LOW_PASS,
    FILTER_MODE_BAND_PASS,
    FILTER_MODE_BAND_PASS_NORMALIZED,
    FILTER_MODE_HIGH_PASS
}filter_mode_t;

typedef struct  
{
    float g;
    float g1;
    filter_mode_t mode;
    float state;
}one_pole_filter_t;

one_pole_filter_t *create_one_pole_filer(filter_mode_t mode);
int process_mult_one_pole_filter(one_pole_filter_t *filter, float *in_out, size_t size);
int one_pole_filter_reset(one_pole_filter_t *filter);

#if 0
typedef struct
{

}state_variable_filter_t;

state_variable_filter_t *create_state_variable_filter();
#endif 

#endif /*_GV_FILTER_H_*/