#include "gv_delay_line.h"
#include <errno.h>
#include <string.h>
#include "dsp.h"

delay_line_t *create_delay_line(size_t max_delay)
{
    delay_line_t *delay_line = malloc(sizeof(delay_line_t));
    if (delay_line == NULL)
    {
        return NULL;
    }

    // delay_line->type = type;
    delay_line->max_delay = max_delay;
    delay_line->write_ptr = 0;

    delay_line->line = malloc(delay_line->max_delay * sizeof(float));
    reset_delay_line(delay_line);
    return delay_line;
}

int destroy_delay_line(delay_line_t **delay_line)
{
    if (*delay_line == NULL)
    {
        return -EINVAL;
    }

    free(*delay_line);
    return 0;
}

int reset_delay_line(delay_line_t *delay_line)
{
    if (delay_line == NULL)
    {
        return -EINVAL;
    }
    memset(delay_line->line, 0, delay_line->max_delay * sizeof(float));
    return 0;
}

int delay_line_set_delay(delay_line_t *delay_line, size_t delay)
{
    if (delay_line == NULL)
    {
        return -EINVAL;
    }

    delay_line->delay = delay;
    return 0;
}

int delay_line_write(delay_line_t *delay_line, float sample)
{
    if (delay_line == NULL)
    {
        return -EINVAL;
    }
    delay_line->line[delay_line->write_ptr] = sample;
    delay_line->write_ptr = (delay_line->write_ptr - 1 + delay_line->max_delay) % delay_line->max_delay;
    return 0;
}

float delay_line_allpass(delay_line_t *delay_line, float sample, size_t delay, float coeff)
{
    if (delay_line == NULL)
    {
        return 0.0f;
    }

    float read = delay_line->line[(delay_line->write_ptr + delay) % delay_line->max_delay];
    float write = sample + coeff * read;
    delay_line_write(delay_line, write);

    return -write * coeff + read;
}

float delay_line_writeread(delay_line_t *delay_line, float sample, float delay)
{
    float write = delay_line_write(delay_line, sample);

    return delay_line_read_external_delay(delay_line, delay);
}

float delay_line_read(delay_line_t *delay_line)
{
    return delay_line->line[(delay_line->write_ptr + delay_line->delay) % delay_line->max_delay];
}

float delay_line_read_external_delay(delay_line_t *delay_line, size_t delay)
{
    return delay_line->line[(delay_line->write_ptr + delay) % delay_line->max_delay];
}

float delay_line_read_fractional_delay(delay_line_t *delay_line, float delay)
{
    MAKE_INTEGRAL_FRACTIONAL(delay)
    const float a = delay_line->line[(delay_line->write_ptr + delay_integral) % delay_line->max_delay];
    const float b = delay_line->line[(delay_line->write_ptr + delay_integral + 1) % delay_line->max_delay];
    return a + (b - a) * delay_fractional;
}

float delay_line_read_hermite(delay_line_t *delay_line, float delay)
{
    MAKE_INTEGRAL_FRACTIONAL(delay);
    int32_t t = (delay_line->write_ptr + delay_integral + delay_line->max_delay);

    const float xm1 = delay_line->line[(t - 1) % delay_line->max_delay];
    const float x0 = delay_line->line[(t) % delay_line->max_delay];

    const float x1 = delay_line->line[(t + 1) % delay_line->max_delay];
    const float x2 = delay_line->line[(t + 2) % delay_line->max_delay];

    const float c = (x1 - xm1) * 0.5f;
    const float v = x0 - x1;
    const float w = c + v;

    const float a = w + v + (x2 - x0) * 0.5f;
    const float b_neg = w + a;
    const float f = delay_fractional;
    return (((a * f) - b_neg) * f + c) * f + x0;
}
