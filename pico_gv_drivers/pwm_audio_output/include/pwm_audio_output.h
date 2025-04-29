#ifndef _PWM_AUDIO_OUTPUT_H_
#define _PWM_AUDIO_OUTPUT_H_

#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/dma.h"
#include "hardware/regs/intctrl.h"
#include "../conf/pwm_output_audio_conf.h"

#ifdef USE_8BIT_PWM
typedef void (*fill_bufer_cb)(uint8_t *to_fill_buffer, uint8_t *free_buffer, size_t size);
#endif

typedef void (*dma_irq_cb_t)(void);

typedef struct
{
    uint gpio_output;
    int pin_slice;
    int pin_chan;

    float sample_freq;
    float repetion_rate;
    float clock_div;
    uint16_t wrap;

    pwm_config config;
    int pwm_dma_chan;
    int trigger_dma_chan;
    int sample_dma_chan;

    dma_channel_config pwm_dma_chan_config;
    dma_channel_config trigger_dma_chan_config;
    dma_channel_config sample_dma_chan_config;
    uint32_t single_sample;
    uint32_t *single_sample_ptr;

    uint8_t current_buffer;

    size_t buffer_size;
    uint8_t *buffer_0;
    uint8_t *buffer_1;
    fill_bufer_cb cb;
} pwm_audio_driver_t;
pwm_audio_driver_t *pwm_audio_create_driver(uint gpio_output, float sample_freq, float repetion_rate, size_t buffer_size);
int pwm_audio_init(pwm_audio_driver_t *driver, dma_irq_cb_t dma_irq_cb);
int pwm_audio_start(pwm_audio_driver_t *driver);
int pwm_audio_stop(pwm_audio_driver_t *driver);
int pwm_audio_register_cb(pwm_audio_driver_t *driver, fill_bufer_cb cb);

int pwm_audio_fill_buffer(pwm_audio_driver_t *driver);

void pwm_audio_IRQ_ack(pwm_audio_driver_t *driver);

#endif /*_PWM_AUDIO_OUTPUT_H_*/