#ifndef _GPIO_INTERRUPTS_H_
#define _GPIO_INTERRUPTS_H_

#include "pico/stdlib.h"
#include <stdlib.h>

typedef void (*gpio_irq_handler_t)(void *argument);

typedef struct {
    void * argument;
    gpio_irq_handler_t fn;
  } gv_gpio_irq_handler_t;

  void register_gpio_irq(uint pin, int condition, gpio_irq_handler_t fn, void *arg);

#endif /* _GPIO_INTERRUPTS_H_ */