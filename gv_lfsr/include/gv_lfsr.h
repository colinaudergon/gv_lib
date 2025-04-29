#ifndef _GV_LFSR_H_
#define _GV_LFSR_H_
#include "pico/stdlib.h"
#include <stdint.h>

typedef struct
{
    uint32_t seed;
    uint32_t feedback;
} lfsr_t;


int lfsr_init(lfsr_t *lfsr, uint32_t seed, uint32_t feedback);
uint32_t lfsr_next(lfsr_t *lfsr);
uint32_t lfsr_next_n(lfsr_t *lfsr, uint32_t n);

#endif /*_GV_LFSR_H_*/