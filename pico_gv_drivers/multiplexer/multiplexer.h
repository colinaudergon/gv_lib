#ifndef _MULTIPLEXER_H_
#define _MULTIPLEXER_H_
#include "pico/stdlib.h"

typedef enum
{
    MUX_4051 = 0,
    MUX_4052 = 1,
    MUX_4053 = 3,
    MUX_UNSUPORTED = 255
} mux_type_t;

typedef struct __mux
{
    uint8_t mux_type; // MUX_4051, MUX_4052, MUX_4053
    uint8_t *mux_ctrl_pin;  // GPIO pin number for the MUX
    uint8_t *mux_inout_pin; // MUX channel number
} mux_t;

mux_t * mux_create(uint8_t mux_type, uint8_t *mux_ctrl_pin,size_t nbr_ctrl_pin, uint8_t *mux_inout_pin,size_t nbr_inout_pin);
int mux_destroy(mux_t *mux);

#endif /*_MULTIPLEXER_H_*/