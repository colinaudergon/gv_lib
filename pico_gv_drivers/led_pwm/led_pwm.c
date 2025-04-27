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

// #ifndef PICO_DEFAULT_LED_PIN
// #warning pwm/led_fade example requires a board with a regular LED
// #else
//     // Tell the LED pin that the PWM is in charge of its value.
//     gpio_set_function(PICO_DEFAULT_LED_PIN, GPIO_FUNC_PWM);
//     // Figure out which slice we just connected to the LED pin
//     uint slice_num = pwm_gpio_to_slice_num(PICO_DEFAULT_LED_PIN);

//     // Mask our slice's IRQ output into the PWM block's single interrupt line,
//     // and register our interrupt handler
//     pwm_clear_irq(slice_num);
//     pwm_set_irq_enabled(slice_num, true);
//     irq_set_exclusive_handler(PWM_DEFAULT_IRQ_NUM(), on_pwm_wrap);
//     irq_set_enabled(PWM_DEFAULT_IRQ_NUM(), true);

//     // Get some sensible defaults for the slice configuration. By default, the
//     // counter is allowed to wrap over its maximum range (0 to 2**16-1)
//     pwm_config config = pwm_get_default_config();
//     // Set divider, reduces counter clock to sysclock/this value
//     pwm_config_set_clkdiv(&config, 4.f);
//     // Load the configuration into our PWM slice, and set it running.
//     pwm_init(slice_num, &config, true);

//     // Everything after this point happens in the PWM interrupt handler, so we
//     // can twiddle our thumbs
//     while (1)
//         tight_loop_contents();
// #endif