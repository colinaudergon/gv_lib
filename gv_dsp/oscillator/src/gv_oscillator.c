#include "gv_oscillator.h"
#include <errno.h>
#include <math.h>
// static void init_approximate(gv_oscillator_t *ctx, float frequency);

int gv_oscillator_init(gv_oscillator_t *ctx, cosine_oscillator_mode_t mode, float iir_coefficient, float initial_amplitude, float frequency)
{
    if (ctx == NULL)
    {
        return -EINVAL;
    }

    if (mode == COSINE_OSCILLATOR_APPROXIMATE)
    {
        init_approximate(ctx, frequency);
    }
    else
    {
        ctx->iir_coefficient = 2.0f * cosf(2.0f * (float)M_PI * frequency);
        ctx->initial_amplitude = ctx->iir_coefficient * 0.25f;
    }

    return 0;
}

void init_approximate(gv_oscillator_t *ctx, float frequency)
{

    float sign = 16.0f;
    frequency -= 0.25f;
    if (frequency < 0.0f)
    {
        frequency = -frequency;
    }
    else
    {
        if (frequency > 0.5f)
        {
            frequency -= 0.5f;
        }
        else
        {
            sign = -16.0f;
        }
    }

    ctx->iir_coefficient = sign * frequency * (1.0f - 2.0f * frequency);
    ctx->initial_amplitude = ctx->iir_coefficient * 0.25f;
}

void gv_oscillator_start(gv_oscillator_t *ctx)
{
    ctx->y1 = ctx->initial_amplitude;
    ctx->y0 = 0.5f;
}

float gv_oscillator_value(gv_oscillator_t *ctx)
{
    return ctx->y1 + 0.5f;
}

float gv_oscillator_next(gv_oscillator_t *ctx)
{
    float temp = ctx->y0;
    ctx->y0= ctx->iir_coefficient * ctx->y0 - ctx->y1;
    ctx->y1= temp;
    return temp + 0.5f;
}
