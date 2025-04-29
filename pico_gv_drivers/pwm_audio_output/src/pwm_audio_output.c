#include "pwm_audio_output.h"

#include <stdlib.h>
#include <errno.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/irq.h"
#include "hardware/dma.h"
#include "hardware/clocks.h"
#include "hardware/structs/clocks.h"
#include <stdlib.h>
#include <stdio.h>

#include "../pwm_audio_logger/pwm_audio_logger.h"

void dmaHandler_internal(void)
{
    printf("hello dma\n");
    // LOG_INF("DMA HANDLER");
    // driver->current_buffer = 1 - driver->current_buffer;
    // pwm_audio_fill_buffer(driver);
}

pwm_audio_driver_t *pwm_audio_create_driver(uint gpio_output, float sample_freq, float repetion_rate, size_t buffer_size)
{
    pwm_audio_driver_t *driver = malloc(sizeof(pwm_audio_driver_t));
    if (driver == NULL)
    {
        return NULL;
    }

    driver->buffer_size = buffer_size;
    driver->buffer_0 = malloc(sizeof(uint8_t) * driver->buffer_size);
    if (driver->buffer_0 == NULL)
    {
        free(driver);
        return NULL;
    }

    driver->buffer_1 = malloc(sizeof(uint8_t) * driver->buffer_size);
    if (driver->buffer_1 == NULL)
    {
        free(driver->buffer_0);
        free(driver);
        return NULL;
    }
    driver->current_buffer = 1;

    driver->gpio_output = gpio_output;

    driver->repetion_rate = repetion_rate;
    driver->sample_freq = sample_freq;

    uint f_clk_sys = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_CLK_SYS);

    PWM_AUDIO_LOG_DEBUG("Freq: %d", f_clk_sys);
    driver->clock_div = ((float)f_clk_sys * 1000.0f) / 254.0f / (float)driver->sample_freq / (float)driver->repetion_rate;
    PWM_AUDIO_LOG_DEBUG("Clock div: %f\n", driver->clock_div);

    // uint32_t single_sample = 0;
    driver->single_sample = 0;
    driver->single_sample_ptr = &driver->single_sample;
    // uint32_t *single_sample_ptr = &single_sample;

    return driver;
}

int pwm_audio_init(pwm_audio_driver_t *driver, dma_irq_cb_t dma_irq_cb)
{
    if (driver == NULL || dma_irq_cb == NULL)
    {
        PWM_AUDIO_LOG_ERROR("Invalid argument");
        return -EINVAL;
    }

    gpio_set_function(driver->gpio_output, GPIO_FUNC_PWM);
    driver->pin_slice = pwm_gpio_to_slice_num(driver->gpio_output);
    pwm_config config = pwm_get_default_config();

    // pwm_config_set_clkdiv(&config, 22.1f / REPETITION_RATE);
    pwm_config_set_clkdiv(&config, driver->clock_div);
    pwm_config_set_wrap(&config, 254);
    pwm_init(driver->pin_slice, &config, true);

    driver->pwm_dma_chan = dma_claim_unused_channel(true);
    driver->trigger_dma_chan = dma_claim_unused_channel(true);
    driver->sample_dma_chan = dma_claim_unused_channel(true);

    dma_channel_config pwm_dma_chan_config = dma_channel_get_default_config(driver->pwm_dma_chan);
    channel_config_set_transfer_data_size(&pwm_dma_chan_config, DMA_SIZE_32);
    channel_config_set_read_increment(&pwm_dma_chan_config, false);
    channel_config_set_write_increment(&pwm_dma_chan_config, false);

    channel_config_set_chain_to(&pwm_dma_chan_config, driver->sample_dma_chan);

    channel_config_set_dreq(&pwm_dma_chan_config, DREQ_PWM_WRAP0 + driver->pin_slice);

    dma_channel_configure(
        driver->pwm_dma_chan,
        &pwm_dma_chan_config,
        // Write to PWM slice CC register
        &pwm_hw->slice[driver->pin_slice].cc,
        // Read from single_sample
        &driver->single_sample,
        // Transfer once per desired sample repetition
        driver->repetion_rate,
        // Don't start yet
        false);

    // Setup trigger DMA channel
    dma_channel_config trigger_dma_chan_config = dma_channel_get_default_config(driver->trigger_dma_chan);
    // Transfer 32-bits at a time
    channel_config_set_transfer_data_size(&trigger_dma_chan_config, DMA_SIZE_32);
    // Always read and write from and to the same address
    channel_config_set_read_increment(&trigger_dma_chan_config, false);
    channel_config_set_write_increment(&trigger_dma_chan_config, false);
    // Transfer on PWM cycle end
    channel_config_set_dreq(&trigger_dma_chan_config, DREQ_PWM_WRAP0 + driver->pin_slice);

    dma_channel_configure(
        driver->trigger_dma_chan,
        &trigger_dma_chan_config,
        // Write to PWM DMA channel read address trigger
        &dma_hw->ch[driver->pwm_dma_chan].al3_read_addr_trig,
        // Read from location containing the address of single_sample
        &driver->single_sample_ptr,
        // Need to trigger once for each audio sample but as the PWM DREQ is
        // used need to multiply by repetition rate
        driver->repetion_rate * driver->buffer_size,
        false);

    // Fire interrupt when trigger DMA channel is done
    dma_channel_set_irq0_enabled(driver->trigger_dma_chan, true);
    irq_set_exclusive_handler(DMA_IRQ_0, dma_irq_cb);
    irq_set_enabled(DMA_IRQ_0, true);


    // Setup sample DMA channel
    dma_channel_config sample_dma_chan_config = dma_channel_get_default_config(driver->sample_dma_chan);
    // Transfer 8-bits at a time
    channel_config_set_transfer_data_size(&sample_dma_chan_config, DMA_SIZE_8);
    // Increment read address to go through audio buffer
    channel_config_set_read_increment(&sample_dma_chan_config, true);
    // Always write to the same address
    channel_config_set_write_increment(&sample_dma_chan_config, false);

    dma_channel_configure(
        driver->sample_dma_chan,
        &sample_dma_chan_config,
        // Write to single_sample
        &driver->single_sample,
        // Read from audio buffer
        &driver->buffer_0[0],
        // Only do one transfer (once per PWM DMA completion due to chaining)
        1,
        // Don't start yet
        false);

    return 0;
}

// pwm_audio_driver_t *pwm_audio_init(uint gpio_output, float sample_freq, float repetion_rate, size_t buffer_size, dma_irq_cb_t dma_irq_cb)
// {

//     gpio_set_function(driver->gpio_output, GPIO_FUNC_PWM);
//     driver->pin_slice = pwm_gpio_to_slice_num(driver->gpio_output);
//     driver->pin_chan = pwm_gpio_to_channel(driver->gpio_output);

//     pwm_config config = pwm_get_default_config();
//     pwm_config_set_clkdiv(&config, driver->clock_div);
//     pwm_config_set_wrap(&config, 254);
//     pwm_init(driver->pin_slice, &config, true);

//     driver->pwm_dma_chan = dma_claim_unused_channel(true);
//     driver->trigger_dma_chan = dma_claim_unused_channel(true);
//     driver->sample_dma_chan = dma_claim_unused_channel(true);

//     driver->pwm_dma_chan_config = dma_channel_get_default_config(driver->pwm_dma_chan);
//     channel_config_set_transfer_data_size(&driver->pwm_dma_chan_config, DMA_SIZE_32);          // transfer 32 bits at a time
//     channel_config_set_read_increment(&driver->pwm_dma_chan_config, false);                    // always read from the same address
//     channel_config_set_write_increment(&driver->pwm_dma_chan_config, false);                   // always write to the same address
//     channel_config_set_chain_to(&driver->pwm_dma_chan_config, driver->sample_dma_chan);        // trigger sample DMA channel when done
//     channel_config_set_dreq(&driver->pwm_dma_chan_config, DREQ_PWM_WRAP0 + driver->pin_slice); // transfer on PWM cycle end
//     dma_channel_configure(driver->pwm_dma_chan,
//                           &driver->pwm_dma_chan_config,
//                           &pwm_hw->slice[driver->pin_slice].cc, // write to PWM slice CC register
//                           &driver->single_sample,               // read from _singleSample
//                           driver->repetion_rate,                // transfer once per desired sample repetition
//                           false                                 // don't start yet
//     );

//     // setup trigger DMA channel
//     driver->trigger_dma_chan_config = dma_channel_get_default_config(driver->trigger_dma_chan);
//     channel_config_set_transfer_data_size(&driver->trigger_dma_chan_config, DMA_SIZE_32);          // transfer 32-bits at a time
//     channel_config_set_read_increment(&driver->trigger_dma_chan_config, false);                    // always read from the same address
//     channel_config_set_write_increment(&driver->trigger_dma_chan_config, false);                   // always write to the same address
//     channel_config_set_dreq(&driver->trigger_dma_chan_config, DREQ_PWM_WRAP0 + driver->pin_slice); // transfer on PWM cycle end
//     dma_channel_configure(driver->trigger_dma_chan,
//                           &driver->trigger_dma_chan_config,
//                           &dma_hw->ch[driver->pwm_dma_chan].al3_read_addr_trig, // write to PWM DMA channel read address trigger
//                           &driver->single_sample_ptr,                           // read from location containing the address of _singleSample
//                           driver->repetion_rate * driver->buffer_size,          // trigger once per audio sample per repetition rate
//                           false                                                 // don't start yet
//     );

//     dma_channel_set_irq1_enabled(driver->trigger_dma_chan, true); // fire interrupt when trigger DMA channel is done
//     irq_set_exclusive_handler(DMA_IRQ_1, dma_irq_cb);
//     // irq_set_exclusive_handler(DMA_IRQ_1, dmaHandler_internal);
//     irq_set_enabled(DMA_IRQ_1, true);

//     // setup sample DMA channel
//     driver->sample_dma_chan_config = dma_channel_get_default_config(driver->sample_dma_chan);
//     channel_config_set_transfer_data_size(&driver->sample_dma_chan_config, DMA_SIZE_8); // transfer 8-bits at a time
//     channel_config_set_read_increment(&driver->sample_dma_chan_config, true);           // increment read address to go through audio buffer
//     channel_config_set_write_increment(&driver->sample_dma_chan_config, false);         // always write to the same address
//     dma_channel_configure(driver->sample_dma_chan,
//                           &driver->sample_dma_chan_config,
//                           (char *)&driver->single_sample + 2 * driver->pin_chan, // write to _singleSample
//                                                                                  //   &audio_buffers[0][0],                        // read from audio buffer
//                           &driver->buffer_0[0],                                  // read from audio buffer
//                           1,                                                     // only do one transfer (once per PWM DMA completion due to chaining)
//                           false                                                  // don't start yet
//     );

// }

int pwm_audio_start(pwm_audio_driver_t *driver)
{
    if (driver == NULL)
    {
        return -EINVAL;
    }

    irq_set_enabled(DMA_IRQ_1, true);
    dma_channel_start(driver->trigger_dma_chan);
    // pwm_set_enabled(driver->pin_slice, true);
    return 0;
}

int pwm_audio_stop(pwm_audio_driver_t *driver)
{
    if (driver == NULL)
    {
        return -EINVAL;
    }

    irq_set_enabled(DMA_IRQ_1, false);
    return 0;
}

int pwm_audio_register_cb(pwm_audio_driver_t *driver, fill_bufer_cb cb)
{
    if (driver == NULL || cb == NULL)
    {
        return -EINVAL;
    }

    driver->cb = cb;
    return 0;
}

int pwm_audio_fill_buffer(pwm_audio_driver_t *driver)
{
    if (driver == NULL)
    {
        return -EINVAL;
    }

    if (driver->cb)
    {
        if (driver->current_buffer == 0)
        {
            dma_hw->ch[driver->sample_dma_chan].al1_read_addr = (intptr_t)&driver->buffer_0[0]; // should give it the filled buffer buff0
            driver->cb(driver->buffer_0, driver->buffer_1, driver->buffer_size);                // Now will fill _buffer1
            // printf("fill buff 1\n");
        }
        else
        {
            dma_hw->ch[driver->sample_dma_chan].al1_read_addr = (intptr_t)&driver->buffer_1[0]; // should give it the filled buffer buff1
            driver->cb(driver->buffer_1, driver->buffer_0, driver->buffer_size);                // now will fill _buffer0
            // printf("fill buff 0\n");
        }
    }

    return 0;
}

void pwm_audio_IRQ_ack(pwm_audio_driver_t *driver)
{
    if (driver == NULL)
    {
        return;
    }

    dma_hw->ch[driver->trigger_dma_chan].al3_read_addr_trig = (intptr_t)&driver->single_sample_ptr;
    dma_hw->ints1 = 1u << driver->trigger_dma_chan;
}
