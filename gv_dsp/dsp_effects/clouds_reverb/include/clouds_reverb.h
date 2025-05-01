#ifndef _CLOUDS_REVERB_H_
#define _CLOUDS_REVERB_H_

#include "pico/stdlib.h"

typedef struct
{
    float l;
    float r;
} float_frame_t;

typedef struct
{
    // float *delay_line;   // Pointer to the delay line buffer
    // size_t delay_length; // Length of the delay line
    // size_t write_ptr;    // Write pointer for the delay line
    // float feedback;      // Feedback amount
    // float mix;           // Wet/dry mix

    float amount;
    float input_gain;
    float reverb_time;
    float diffusion;
    float lp;

    float lp_decay_1;
    float lp_decay_2;

} cloud_reverb_context_t;

inline void set_amount(cloud_reverb_context_t *ctx, float amount)
{
    ctx->amount = amount;
}

inline void set_input_gain(cloud_reverb_context_t *ctx, float input_gain)
{
    ctx->input_gain = input_gain;
}

inline void set_time(cloud_reverb_context_t *ctx, float reverb_time)
{
    ctx->reverb_time = reverb_time;
}

inline void set_diffusion(cloud_reverb_context_t *ctx, float diffusion)
{
    ctx->diffusion = diffusion;
}

inline void set_lp(cloud_reverb_context_t *ctx, float lp)
{
    ctx->lp = lp;
}

int clouds_reverb_init(cloud_reverb_context_t *ctx, size_t delay_length, float feedback, float mix);

int clouds_reverb_cleanup(cloud_reverb_context_t *ctx);
int clouds_reverb_process_mono(cloud_reverb_context_t *ctx,float_frame_t *in_out,size_t size);
int clouds_reverb_process_stereo(cloud_reverb_context_t *ctx,float_frame_t *in_out,size_t size);


#endif /*_CLOUDS_REVERB_H_*/