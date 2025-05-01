#ifndef _GV_OSCILLATOR_H_
#define _GV_OSCILLATOR_H_
#include "pico/stdlib.h"

typedef enum
{
    COSINE_OSCILLATOR_APPROXIMATE,
    COSINE_OSCILLATOR_EXACT
}cosine_oscillator_mode_t;

typedef struct
{
    float y1;
    float y0;
    float iir_coefficient;
    float initial_amplitude;
  
}gv_oscillator_t;


int gv_oscillator_init(gv_oscillator_t *ctx,cosine_oscillator_mode_t mode, float iir_coefficient, float initial_amplitude,float frequency);
void gv_oscillator_start(gv_oscillator_t *ctx);
float gv_oscillator_value(gv_oscillator_t *ctx);
float gv_oscillator_next(gv_oscillator_t *ctx);

void init_approximate(gv_oscillator_t *ctx, float frequency);


#endif /* _GV_OSCILLATOR_H_ */