#ifndef _GV_DELAY_LINE_H_
#define _GV_DELAY_LINE_H_

#include "pico/stdlib.h"
#include <stdlib.h>

typedef enum
{
    DELAY_LINE_FLOAT = 0,
    DELAY_LINE_INT,
    DELAY_LINE_UINT,
    DELAY_LINE_UINT8,
    DELAY_LINE_UINT16,
    DELAY_LINE_UINT32
} delay_line_type_t;

typedef struct
{
    size_t max_delay;
    size_t delay;
    size_t write_ptr;
    // void *line;
    float *line;
    delay_line_type_t type;
} delay_line_t;

// delay_line_t *create_delay_line(size_t max_delay, delay_line_type_t type);
delay_line_t *create_delay_line(size_t max_delay);

int destroy_delay_line(delay_line_t **delay_line);

int reset_delay_line(delay_line_t *delay_line);

int delay_line_set_delay(delay_line_t *delay_line, size_t delay);

int delay_line_write(delay_line_t *delay_line,float sample);

float delay_line_allpass(delay_line_t *delay_line, float sample, size_t delay, float coeff);

float delay_line_writeread(delay_line_t *delay_line,float sample, float delay);
float delay_line_read(delay_line_t *delay_line);

float delay_line_read_external_delay(delay_line_t *delay_line,size_t delay);

float delay_line_read_fractional_delay(delay_line_t *delay_line,float delay);
float delay_line_read_hermite(delay_line_t *delay_line,float delay);

#endif /*_GV_DELAY_LINE_H_*/