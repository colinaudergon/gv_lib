#ifndef _TAN_H_
#define _TAN_H_

#include "pico/stdlib.h"
#include <math.h>
#include <stdio.h>

// Enumeration for frequency approximation types
typedef enum {
    FREQUENCY_EXACT,
    FREQUENCY_ACCURATE,
    FREQUENCY_FAST,
    FREQUENCY_DIRTY
} frequency_approximation_t;

// Constants
#define M_PI_F 3.14159265358979323846f
#define M_PI_POW_3 (M_PI_F * M_PI_F * M_PI_F)
#define M_PI_POW_5 (M_PI_POW_3 * M_PI_F * M_PI_F)
#define M_PI_POW_7 (M_PI_POW_5 * M_PI_F * M_PI_F)
#define M_PI_POW_9 (M_PI_POW_7 * M_PI_F * M_PI_F)
#define M_PI_POW_11 (M_PI_POW_9 * M_PI_F * M_PI_F)

// Exact tangent calculation
float tan_exact(float f) {
    // Clip coefficient to about 100.
    f = f < 0.497f ? f : 0.497f;
    return tanf(M_PI_F * f);
}

// Accurate tangent approximation
float tan_accurate(float f) {
    const float a = 3.333314036e-01f * M_PI_POW_3;
    const float b = 1.333923995e-01f * M_PI_POW_5;
    const float c = 5.33740603e-02f * M_PI_POW_7;
    const float d = 2.900525e-03f * M_PI_POW_9;
    const float e = 9.5168091e-03f * M_PI_POW_11;
    float f2 = f * f;
    return f * (M_PI_F + f2 * (a + f2 * (b + f2 * (c + f2 * (d + f2 * e)))));
}

// Fast tangent approximation
float tan_fast(float f) {
    const float a = 3.260e-01f * M_PI_POW_3;
    const float b = 1.823e-01f * M_PI_POW_5;
    float f2 = f * f;
    return f * (M_PI_F + f2 * (a + b * f2));
}

// Dirty tangent approximation
float tan_dirty(float f) {
    if (f < 0.5f) {
        return f; // Approximation for small angles
    } else {
        return f * 1.2f; // Adjust scaling for larger angles
    }
}

// Dispatcher function for tangent calculation
float tan_with_approximation(frequency_approximation_t approximation, float f) {
    switch (approximation) {
        case FREQUENCY_EXACT:
            return tan_exact(f);
        case FREQUENCY_ACCURATE:
            return tan_accurate(f);
        case FREQUENCY_FAST:
            return tan_fast(f);
        case FREQUENCY_DIRTY:
            return tan_dirty(f);
        default:
            // Default to exact if an invalid approximation is provided
            return tan_exact(f);
    }
}

#endif /*_TAN_H_*/