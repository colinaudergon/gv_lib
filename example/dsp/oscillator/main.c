
#include "pico/stdlib.h"
#include "logger.h"
#include "gv_oscillator.h"
#include <string.h>
#include "hardware/clocks.h"
#include "pwm_audio_output.h"
#include "hardware/adc.h"
#include "pico/multicore.h"
#include "gv_filter.h"

#define LED_GPIO 25
#define AUDIO_PIN 2
#define BUFFER_SIZE 512

void dmaHandler(void);
gv_oscillator_t oscillator;
pwm_audio_driver_t *driver;

bool in_IRQ = false;
bool is_data_protected = false;

void bufer_cb(uint8_t *to_fill_buffer, uint8_t *free_buffer, size_t size)
{
    in_IRQ = true;

    if (to_fill_buffer == NULL || free_buffer == NULL)
    {
        LOG_ERROR("BUFFER NULL");
        return;
    }

    if (is_data_protected != true)
    {

        for (int i = 0; i < size; i++)
        {
            // Copy audio data to the buffer
            to_fill_buffer[i] = (uint8_t)(gv_oscillator_next(&oscillator) * 255.0f);
        }
    }
    pwm_audio_IRQ_ack(driver);
    in_IRQ = false;
}

void update_frequency_from_adc()
{
    while (1)
    {
        while (in_IRQ)
        {
            // Wait until the IRQ is not active
        }

        is_data_protected = true;

        // Read ADC value
        uint16_t adc_value = adc_read();
        float normalized_frequency = (float)adc_value / 4095.0f; // Normalize ADC value to [0, 1]

        printf("adc value: %d\n", adc_value);
        // Set the oscillator frequency
        // gv_oscillator_set_frequency(&oscillator, normalized_frequency);
        init_approximate(&oscillator, normalized_frequency);
        is_data_protected = false;

        sleep_ms(10); // Adjust frequency update rate
    }
}

int main(void)
{
    stdio_init_all();
    set_sys_clock_khz(176000, true);
    sleep_ms(1000);

    int err;
    gpio_init(LED_GPIO);
    gpio_set_dir(LED_GPIO, GPIO_OUT);

    // Initialize the ADC
    adc_init();
    adc_gpio_init(26);   // Use GPIO 26 (ADC0) for input
    adc_select_input(0); // Select ADC input 0

    // Initialize the oscillator
    float frequency = 0.1f;                   // Example frequency (normalized to [0, 1])
    int mode = COSINE_OSCILLATOR_APPROXIMATE; // Use approximate mode
    if (gv_oscillator_init(&oscillator, mode, 0.0f, 0.0f, frequency) != 0)
    {
        LOG_ERROR("Failed to initialize oscillator");
        return -1;
    }

    // Start the oscillator
    gv_oscillator_start(&oscillator);

    driver = pwm_audio_create_driver(AUDIO_PIN, 44100, 4.f, BUFFER_SIZE);
    sleep_ms(5000);

    err = pwm_audio_init(driver, dmaHandler);
    if (err < 0)
    {
        LOG_ERROR("Failed to initialiaze the pwm audio");
    }
    else
    {
        err = pwm_audio_register_cb(driver, bufer_cb);
        if (err < 0)
        {
            LOG_ERROR("Failed to register the buffer callback");
        }
        else
        {
            LOG_INF("Starting PWM audio");
            pwm_audio_start(driver);
        }
    }

    // Start a thread to update the oscillator frequency from the ADC
    multicore_launch_core1(update_frequency_from_adc);

    // Initialize variables
    bool gpio_val = true;
    gpio_put(LED_GPIO, gpio_val);

    while (1)
    {
        gpio_val = !gpio_val;
        gpio_put(LED_GPIO, gpio_val);
        sleep_ms(1000);
    }

    return 0;
}

void dmaHandler(void)
{
    static int buff = 1;
    buff = 1 - buff;
    driver->current_buffer = buff;
    pwm_audio_fill_buffer(driver);
}