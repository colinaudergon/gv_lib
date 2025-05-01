#include "dsp_profiler.h"
#include <errno.h>
#include <stdlib.h>

dsp_profiler_t *dsp_profiler_init(uint gpio, fn_profile fn_to_profile)
{
    dsp_profiler_t * profiler = malloc(sizeof(dsp_profiler_t));
    if(profiler == NULL)
    {
        return NULL;
    }
    profiler->fn = fn_to_profile;

    gpio_init(gpio);
    gpio_set_dir(gpio, GPIO_OUT);

    return profiler;
}

int profile(dsp_profiler_t *profiler, void *args)
{
    if(profiler == NULL)
    {
        return -EINVAL;
    }
    
    gpio_put(profiler->gpio,1);
    
    profiler->fn(args);

    gpio_put(profiler->gpio,0);

    return 0;
}

int dsp_profiler_end(dsp_profiler_t **profiler)
{
    if(*profiler == NULL)
    {
        return -EINVAL;
    }

    free(*profiler);
    return 0;
}