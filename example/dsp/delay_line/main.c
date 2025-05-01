
#include "pico/stdlib.h"
#include "logger.h"
#include "gv_delay_line.h"
#include <string.h>

#define LED_GPIO 25

int main(void)
{
    stdio_init_all();
    sleep_ms(1000);

    gpio_init(LED_GPIO);
    gpio_set_dir(LED_GPIO, GPIO_OUT);

    // Initialize variables
    bool gpio_val = true;
    gpio_put(LED_GPIO, gpio_val);

    int err;
    size_t max_delay = 10; // Maximum delay size
    size_t delay = 5;      // Delay to apply
    float sample = 1.0f;   // Example input sample
    float output;          // Output sample

    // Create a delay line
    delay_line_t *delay_line = create_delay_line(max_delay);
    if (delay_line == NULL)
    {
        LOG_ERROR("Failed to create delay line");
        return -1;
    }

    // Set the delay
    err = delay_line_set_delay(delay_line, delay);
    if (err < 0)
    {
        LOG_ERROR("Failed to set delay");
        destroy_delay_line(&delay_line);
        return -1;
    }

    // Reset the delay line
    err = reset_delay_line(delay_line);
    if (err < 0)
    {
        LOG_ERROR("Failed to reset delay line");
        destroy_delay_line(&delay_line);
        return -1;
    }

    gpio_val = !gpio_val;
    gpio_put(LED_GPIO, gpio_val);
    // Test the delay line
    LOG_INF("Testing delay line...");

    for (int i = 0; i < 15; i++)
    {
        // Write and read from the delay line
        output = delay_line_allpass(delay_line, sample, delay, 0.5f);

        // Log the input and output
        printf("Input: %f, Output: %f\n", sample, output);

        // Update the input sample for the next iteration
        // sample += 1.0f;
        gpio_val = !gpio_val;
        gpio_put(LED_GPIO, gpio_val);
    }
    printf("\n\n");

    // Reset the delay line
    err = reset_delay_line(delay_line);
    if (err < 0)
    {
        LOG_ERROR("Failed to reset delay line");
        destroy_delay_line(&delay_line);
        return -1;
    }
    LOG_INF("Testing delay line delay_line_writeread...");
    float pulse[15];
    float out[15];
    memset(pulse,0,15*sizeof(float));
    memset(out,0,15*sizeof(float));
    pulse[0] = 1.0f;

    for (int i = 0; i < 15; i++)
    {
        out[i] = delay_line_writeread(delay_line,pulse[i],delay);
        // Log the input and output
        printf("Input: %f, Output: %f\n", out[i], pulse[i]);
    }
    // Destroy the delay line
    destroy_delay_line(&delay_line);

    while (1)
    {
        gpio_val = !gpio_val;
        gpio_put(LED_GPIO, gpio_val);
        sleep_ms(1000);
    }

    return 0;
}