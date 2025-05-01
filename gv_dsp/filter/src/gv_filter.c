#include "gv_filter.h"
#include <errno.h>
#include <stdlib.h>

static inline int set_freq(frequency_approximation_t freq_approx, float freq, float *g, float *g1)
{
    if (g == NULL || g1 == NULL)
    {
        return -EINVAL;
    }

    *g = tan_with_approximation(freq_approx, freq);
    *g1 = 1.0f / (1.0f + *g);

    return 0;
}

static inline int set_freq_exact(float freq, float *g, float *g1)
{
    if (g == NULL || g1 == NULL)
    {
        return -EINVAL;
    }

    *g = tan_exact(freq);
    *g1 = 1.0f / (1.0f + *g);

    return 0;
}

static inline int set_freq_accurate(float freq, float *g, float *g1)
{
    if (g == NULL || g1 == NULL)
    {
        return -EINVAL;
    }

    *g = tan_accurate(freq);
    *g1 = 1.0f / (1.0f + *g);

    return 0;
}

static inline int set_freq_fast(float freq, float *g, float *g1)
{
    if (g == NULL || g1 == NULL)
    {
        return -EINVAL;
    }

    *g = tan_fast(freq);
    *g1 = 1.0f / (1.0f + *g);

    return 0;
}

static inline int set_freq_dirty(float freq, float *g, float *g1)
{
    if (g == NULL || g1 == NULL)
    {
        return -EINVAL;
    }

    *g = tan_dirty(freq);
    *g1 = 1.0f / (1.0f + *g);

    return 0;
}

static float process_low_pass(one_pole_filter_t *filter, float in)
{
    float lp = (filter->g * in + filter->state) * filter->g1;
    filter->state = filter->g * (in - lp) + lp;
    return lp;
}

static float process_high_pass(one_pole_filter_t *filter, float in)
{
    float lp = (filter->g * in + filter->state) * filter->g1;
    filter->state = filter->g * (in - lp) + lp;
    return in - lp;
}


int process_mult_one_pole_filter(one_pole_filter_t *filter, float *in_out, size_t size)
{
    if (filter == NULL)
    {
        return -EINVAL;
    }

    if (filter->mode == FILTER_MODE_LOW_PASS)
    {
        while (size--)
        {
            *in_out = process_low_pass(filter, *in_out);
            ++in_out;
        }
    }

    else if (filter->mode == FILTER_MODE_HIGH_PASS)
    {
        while (size--)
        {
            *in_out = process_high_pass(filter, *in_out);
            ++in_out;
        }
    }

    else
    {
        while (size--)
        {
            *in_out = 0.0f;
            ++in_out;
        }
    }
    return 0;
}

one_pole_filter_t *create_one_pole_filer(filter_mode_t mode)
{
    one_pole_filter_t *filter = malloc(sizeof(one_pole_filter_t));
    if (filter == NULL)
    {
        return NULL;
    }
    // filter->fn_process = process_cb;

    set_freq_dirty(0.01f, &filter->g, &filter->g1);

    filter->mode = mode;

    return filter;
}

int one_pole_filter_reset(one_pole_filter_t *filter)
{
    if (filter == NULL)
    {
        return -EINVAL;
    }

    filter->state = 0.0f;
    return 0;
}