#ifndef _UI_FUNCTIONS_H_
#define _UI_FUNCTIONS_H_

#include "../pico_gv_ui_conf.h"

#ifdef USE_PICO_SSD1306_LIB
#include "../helpers/ssd1306_helpers.h"
#endif

// #include "pico/stdlib.h"

int ui_init(gv_ui_device_t *device);
// void ui_deinit(void);

int ui_show(gv_ui_device_t *device);
int ui_clear(gv_ui_device_t *device);

int ui_get_display_width(gv_ui_device_t *device);
int ui_get_display_height(gv_ui_device_t *device);

int ui_draw_pixel(gv_ui_device_t *device, int32_t x, int32_t y);
int ui_draw_line(gv_ui_device_t *device, int32_t x1, int32_t y1, int32_t x2, int32_t y2);
int ui_draw_doted_line(gv_ui_device_t *device, int32_t dot_width, int32_t dot_height, int32_t dot_spacing, int32_t x1, int32_t y1, int32_t x2, int32_t y2);
//TODO: make function faster and simpler
int ui_draw_clear_doted_line(gv_ui_device_t *device, int32_t dot_width, int32_t dot_height, int32_t dot_spacing, int32_t x1, int32_t y1, int32_t x2, int32_t y2);
int ui_draw_square(gv_ui_device_t *device, uint32_t x, uint32_t y, uint32_t width, uint32_t height);
int ui_clear_square(gv_ui_device_t *device, uint32_t x, uint32_t y, uint32_t width, uint32_t height);
int ui_draw_empty_square(gv_ui_device_t *device, uint32_t x, uint32_t y, uint32_t width, uint32_t height);
int ui_draw_rounded_rectangle(gv_ui_device_t *device, uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint8_t radius);
int ui_draw_grid(gv_ui_device_t *device, uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint8_t grid_v_size, uint8_t grid_h_size);
int ui_draw_char_with_font(gv_ui_device_t *device, uint32_t x, uint32_t y, uint32_t scale, const uint8_t *font, char c);
int ui_draw_string_with_font(gv_ui_device_t *device, uint32_t x, uint32_t y, uint32_t scale, const uint8_t *font, const char *s);
int ui_draw_char(gv_ui_device_t *device, uint32_t x, uint32_t y, uint32_t scale, char c);
int ui_draw_string(gv_ui_device_t *device, uint32_t x, uint32_t y, uint32_t scale, const char *s);
int ui_bmp_show_image(gv_ui_device_t *device, const uint8_t *data, const long size);
int ui_bmp_show_image_with_offset(gv_ui_device_t *device, const uint8_t *data, const long size, uint32_t x_offset, uint32_t y_offset);
int ui_get_rounded_rectangle_max_radius();

#endif /*_UI_FUNCTIONS_H_*/