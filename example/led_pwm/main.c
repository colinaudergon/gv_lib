// #include "led_pwm.h"
// #include "pico/stdlib.h"

// #include <stdio.h>

// int main() {
//     stdio_init_all();
//     sleep_ms(1000);
//     sleep_ms(1000);
//     sleep_ms(1000);
//     // Initialize LED PWM
//     led_pwm_t *led_pwm = led_pwm_basic_create(25, 4, 1.0f, PWM_CHAN_A); // GPIO 25 is the onboard LED
//     if (led_pwm == NULL) {
//         printf("Failed to create LED PWM\n");
//         return -1;
//     }

//     int err = led_pwm_basic_init(led_pwm);
//     if(err != 0)
//     {
//         printf("Failed to init LED PWM\n");
//         return -1;
//     }

//     err = led_pwm_basic_start(led_pwm);
//     if(err != 0)
//     {
//         printf("Failed to start LED PWM\n");
//         return -1;
//     }

//     while (1)
//     {
//         // printf("Failed to create LED PWM\n");
//         // tight_loop_contents();
//         sleep_ms(1000);
//         printf("LED PWM running\n");
//     }

//     return 0;
// }

/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

// Fade an LED between low and high brightness. An interrupt handler updates
// the PWM slice's output level each time the counter wraps.

// #include "pico/stdlib.h"
// #include <stdio.h>
// #include "pico/time.h"
// #include "hardware/irq.h"
// #include "hardware/pwm.h"

// #ifdef PICO_DEFAULT_LED_PIN
// void on_pwm_wrap() {
//     static int fade = 0;
//     static bool going_up = true;
//     // Clear the interrupt flag that brought us here
//     pwm_clear_irq(pwm_gpio_to_slice_num(PICO_DEFAULT_LED_PIN));

//     if (going_up) {
//         ++fade;
//         if (fade > 255) {
//             fade = 255;
//             going_up = false;
//         }
//     } else {
//         --fade;
//         if (fade < 0) {
//             fade = 0;
//             going_up = true;
//         }
//     }
//     // Square the fade value to make the LED's brightness appear more linear
//     // Note this range matches with the wrap value
//     pwm_set_gpio_level(PICO_DEFAULT_LED_PIN, fade * fade);
// }
// #endif

// int main() {
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
// }
