#ifndef _ROTARY_ENCODER_H_
#define _ROTARY_ENCODER_H_

#include "pico/stdlib.h"
#include <stdlib.h>

typedef struct rotary_encoder_t {
    int pin_a, pin_b;
    int state;
    long int position;
    // encoder_change_handler_t fn;
    void (*fn)(struct rotary_encoder_t *button);
} rotary_encoder_t;

typedef void (*encoder_change_handler_t)(struct rotary_encoder_t *encoder);

rotary_encoder_t *create_encoder(int pin_a, int pin_b, void (*fn)(rotary_encoder_t *encoder)); 
// rotary_encoder_t *create_encoder(int pin_a, int pin_b, encoder_change_handler_t fn);
#endif /*_ROTARY_ENCODER_H_*/