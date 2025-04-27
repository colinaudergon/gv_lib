#include "multiplexer.h"
#include "pico/stdlib.h"
#include <stdlib.h>
#include <errno.h>
#include <string.h>

mux_t * mux_create(uint8_t mux_type, uint8_t *mux_ctrl_pin,size_t nbr_ctrl_pin, uint8_t *mux_inout_pin,size_t nbr_inout_pin)
{
    if(mux_type >= MUX_UNSUPORTED)
    {
        return NULL;
    }
    mux_t *mux = (mux_t *)malloc(sizeof(mux_t));
    if(mux == NULL)
    {
        return NULL;
    }
    mux->mux_type = mux_type;
    mux->mux_ctrl_pin = (uint8_t *)malloc(nbr_ctrl_pin * sizeof(uint8_t));
    if(mux->mux_ctrl_pin == NULL)
    {
        free(mux);
        return NULL;
    }
    mux->mux_inout_pin = (uint8_t *)malloc(nbr_inout_pin * sizeof(uint8_t));
    if(mux->mux_inout_pin == NULL)
    {
        free(mux->mux_ctrl_pin);
        free(mux);
        return NULL;
    }
    memcpy(mux->mux_ctrl_pin, mux_ctrl_pin, nbr_ctrl_pin * sizeof(uint8_t));
    memcpy(mux->mux_inout_pin, mux_inout_pin, nbr_inout_pin * sizeof(uint8_t));
    return mux;
}

int mux_destroy(mux_t *mux)
{
    if(mux == NULL)
    {
        return -EINVAL;
    }
    if(mux->mux_ctrl_pin != NULL)
    {
        free(mux->mux_ctrl_pin);
    }
    if(mux->mux_inout_pin != NULL)
    {
        free(mux->mux_inout_pin);
    }
    free(mux);
    return 0;
}

