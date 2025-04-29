#include "led_pwm.h"

#include "pico/stdlib.h"
#include <stdio.h>
#include "pico/time.h"
#include "hardware/irq.h"
#include "hardware/pwm.h"
#include <stdlib.h>

#include <errno.h>

led_pwm_t *led_pwm_basic_create(uint led_pin,uint wrap,float clock_divider, enum pwm_chan channel )
{
    led_pwm_t *led_pwm = (led_pwm_t *)malloc(sizeof(led_pwm_t));

    if(led_pwm == NULL)
    {
        return NULL;
    }

    led_pwm->led_pin = led_pin;
    led_pwm->slice_num = pwm_gpio_to_slice_num(led_pwm->led_pin);
    led_pwm->pwm_wrap = wrap;
    led_pwm->clock_divider = clock_divider;

    led_pwm->config = pwm_get_default_config();
    led_pwm->channel = channel;

    return led_pwm;
}

void led_pwm_basic_destroy(led_pwm_t *led_pwm)
{
    if(led_pwm != NULL)
    {
        free(led_pwm);
    }
}


int led_pwm_basic_init(led_pwm_t *led_pwm)
{
    if(led_pwm == NULL)
    {
        return -EINVAL;
    }

    gpio_set_function(led_pwm->led_pin, GPIO_FUNC_PWM);

    led_pwm->slice_num = pwm_gpio_to_slice_num(led_pwm->led_pin);
    pwm_set_wrap(led_pwm->slice_num, led_pwm->pwm_wrap);
    pwm_set_enabled(led_pwm->slice_num, true);
    // pwm_set_chan_level(led_pwm->slice_num, led_pwm->channel, 1);
    return 0;
}

int led_pwm_basic_start(led_pwm_t *led_pwm)
{
    if(led_pwm == NULL)
    {
        return -EINVAL;
    }

    pwm_set_enabled(led_pwm->slice_num, true);

    return 0;
}

int led_pwm_basic_stop(led_pwm_t *led_pwm)
{
    if(led_pwm == NULL)
    {
        return -EINVAL;
    }
    pwm_set_enabled(led_pwm->slice_num, false);

    return 0;
}