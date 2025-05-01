#ifndef _DSP_H_
#define _DSP_H_

#include "pico/stdlib.h"
#include <stdlib.h>

#define MAKE_INTEGRAL_FRACTIONAL(x) \
  int32_t x ## _integral = (int32_t)(x); \
  float x ## _fractional = x - (float)(x ## _integral);

#endif /*_DSP_H_*/