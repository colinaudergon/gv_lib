#include "gpio_interrupts.h"

gv_gpio_irq_handler_t irq_handlers[28] = {NULL};

static void handle_interupt(uint gpio, uint32_t events)
{
    gv_gpio_irq_handler_t handler = irq_handlers[gpio];
    handler.fn(handler.argument);
}

void register_gpio_irq(uint pin, int condition, gpio_irq_handler_t fn, void *arg)
{
    gpio_init(pin);
    gpio_pull_up(pin);
    gpio_set_irq_enabled_with_callback(pin, condition, true, handle_interupt);
    gv_gpio_irq_handler_t *handler = malloc(sizeof(gv_gpio_irq_handler_t));
    handler->argument = arg;
    handler->fn = fn;
    irq_handlers[pin] = *handler;
}