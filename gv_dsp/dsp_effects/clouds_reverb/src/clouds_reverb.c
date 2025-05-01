#include "clouds_reverb.h"
#include <errno.h>

int clouds_reverb_init(cloud_reverb_context_t *ctx, size_t delay_length, float feedback, float mix)
{
    if (ctx == NULL)
    {
        return -1; // Error: Null context
    }

    return 0; // Success
}


int clouds_reverb_cleanup(cloud_reverb_context_t *ctx)
{
    // if (ctx == NULL && ctx->delay_line == NULL)
    // {
    //     return -EINVAL;
    // }

    // free(ctx->delay_line);
    // ctx->delay_line = NULL;

    return 0;
}


int clouds_reverb_process_mono(cloud_reverb_context_t *ctx, float_frame_t *in_out, size_t size)
{
    if(ctx == NULL || in_out == NULL)
    {
        return -EINVAL;
    }
    const float kap = ctx->diffusion;
    const float klp = ctx->lp;
    const float krt = ctx->reverb_time;
    const float amount = ctx->amount;
    const float gain = ctx->input_gain;

    while (size--) 
    {
        
    }

    return 0;
}

int clouds_reverb_process_stereo(cloud_reverb_context_t *ctx, float_frame_t *in_out, size_t size)
{
    if(ctx == NULL || in_out == NULL)
    {
        return -EINVAL;
    }

    const float kap = ctx->diffusion;
    const float klp = ctx->lp;
    const float krt = ctx->reverb_time;
    const float amount = ctx->amount;
    const float gain = ctx->input_gain;
    while (size--) 
    {

    }
    return 0;
}

// typedef FxEngine<16384, FORMAT_12_BIT> E;
// E engine_;