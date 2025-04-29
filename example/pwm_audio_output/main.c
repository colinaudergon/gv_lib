#include "pico/stdlib.h"
#include "pwm_audio_output.h"
#include "logger.h"

#include "rock.h"
#define AUDIO_PIN 2
#define ADC_CHANNEL 2
#define BUFFER_SIZE 512

void dmaHandler(void);
pwm_audio_driver_t *driver;

#define REPETITION_RATE 1

void bufer_cb(uint8_t *to_fill_buffer, uint8_t *free_buffer, size_t size)
{
    if (to_fill_buffer == NULL || freeBuffer == NULL)
    {
        LOG_ERROR("BUFFER NULL");
        return;
    }

    static int cnt = 0;

    for (int i = 0; i < size; i++)
    {
        int counter = cnt * size + i;
        if (counter >= AUDIO_SAMPLES)
        {
            cnt = 0;
            counter = 0;
        }

        to_fill_buffer[i] = free_buffer[counter];
    }
    cnt++;

    pwm_audio_IRQ_ack(driver);
}

int main(void)
{
    stdio_init_all();
    int err;
    
    driver = pwm_audio_create_driver(AUDIO_PIN, 44100.f, 1, BUFFER_SIZE);
    if (driver == NULL)
    {
        LOG_ERROR("Failed to create driver");
    }
    
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

    while (1)
    {
        sleep_ms(1000);
    }
}

void dmaHandler(void)
{
    static int buff = 1;
    buff = 1 - buff;
    driver->current_buffer = buff;
    pwm_audio_fill_buffer(driver);
}