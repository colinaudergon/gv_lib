#ifndef _LED_PWM_H_
#define _LED_PWM_H_

#include "pico/stdlib.h"
#include "hardware/pwm.h"

/*needed: 
gpio pin
pwm slice
float clock_divider
pwm_config 
*/


typedef struct __led_pwm{
    uint led_pin; // GPIO pin number for the LED
    uint slice_num; // PWM slice number
    uint pwm_wrap; // PWM wrap value
    float clock_divider; // Clock divider for PWM
    pwm_config config; // PWM configuration
    enum pwm_chan channel; // PWM channel (0 or 1)
} led_pwm_t;

led_pwm_t *led_pwm_basic_create(uint led_pin,uint wrap,float clock_divider, enum pwm_chan channel);
int led_pwm_basic_init(led_pwm_t *led_pwm);
int led_pwm_basic_start(led_pwm_t *led_pwm);
int led_pwm_basic_stop(led_pwm_t *led_pwm);

#endif /*_LED_PWM_H_*/