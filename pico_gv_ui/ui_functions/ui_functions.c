#include <pico/stdlib.h>
#include <errno.h>

#include "../pico_gv_ui_conf.h"
#include "ui_functions.h"

#ifdef USE_PICO_SSD1306_LIB
#include "ssd1306.h"
#include "hardware/i2c.h"
#include <math.h>
#endif



#ifdef USE_PICO_SSD1306_LIB
#define I2C_INIT(instance, speed)               \
    do                                          \
    {                                           \
        if ((instance) == I2C_INSTANCE_DEFAULT) \
        {                                       \
            i2c_init(i2c_default, (speed));     \
        }                                       \
        else if ((instance) == I2C_INSTANCE_0)  \
        {                                       \
            i2c_init(i2c0, (speed));            \
        }                                       \
        else if ((instance) == I2C_INSTANCE_1)  \
        {                                       \
            i2c_init(i2c1, (speed));            \
        }                                       \
    } while (0)
#endif // USE_PICO_SSD1306_LIB

#ifdef USE_PICO_SSD1306_LIB
#define SSD1306_INIT(disp, width, height, address, i2c_instance)     \
    do                                                               \
    {                                                                \
        if ((i2c_instance) == I2C_INSTANCE_DEFAULT)                  \
        {                                                            \
                                                                     \
            ssd1306_init(disp, width, height, address, i2c_default); \
        }                                                            \
        else if ((i2c_instance) == I2C_INSTANCE_0)                   \
        {                                                            \
                                                                     \
            ssd1306_init(disp, width, height, address, i2c0);        \
        }                                                            \
        else if ((i2c_instance) == I2C_INSTANCE_1)                   \
        {                                                            \
                                                                     \
            ssd1306_init(disp, width, height, address, i2c1);        \
        }                                                            \
    } while (0)

#endif // USE_PICO_SSD1306_LIB

#ifdef USE_ROUNDED_RECTANGLE
// compute the offset lookup table

uint8_t offset_lut[ROUNDED_RECTANGLE_OFFSET_LUT_SIZE];

static int ui_rounded_rectangle_fill_lut(uint8_t *lut)
{
    if (lut == NULL)
    {
        return -EINVAL;
    }
    int index = 0;
    for (int radius = 0; radius < ROUNDED_RECTANGLE_RADIUS_MAX_RADIUS; radius++)
    {
        for (uint8_t i = 0; i < radius; i++)
        {
            lut[index++] = (uint8_t)sqrt(radius * radius - i * i);
        }
    }
    return 0;
}
#endif // USE_ROUNDED_RECTANGLE

inline static void swap(int32_t *a, int32_t *b)
{
    int32_t *t = a;
    *a = *b;
    *b = *t;
}

int ui_init(gv_ui_device_t *device)
{

    if (device == NULL)
    {
        return -EINVAL;
    }
#if USE_ROUNDED_RECTANGLE  == 1
// compute the offset lookup table
#endif // USE_ROUNDED_RECTANGLE
    ui_rounded_rectangle_fill_lut(offset_lut);

    // Initialize the device structure
    device->width = SSD1306_WIDTH;
    device->height = SSD1306_HEIGHT;
    device->external_vcc = false;

#if USE_PICO_SSD1306_LIB == 1
    // hardware_init of the I2C display
    I2C_INIT(SSD1306_I2C_INSTANCE, SSD1306_SPEED);

    // i2c_init(SSD1306_I2C_INSTANCE, SSD1306_SPEED);
    gpio_set_function(SSD1306_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SSD1306_I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(SSD1306_I2C_SDA_PIN);
    gpio_pull_up(SSD1306_I2C_SCL_PIN);

    // ssd1306_t disp;
    device->external_vcc = false;
    SSD1306_INIT(device, SSD1306_WIDTH, SSD1306_HEIGHT, SSD1306_I2C_ADDRESS, SSD1306_I2C_INSTANCE);
    ssd1306_clear(device);
#endif // USE_PICO_SSD1306_LIB


return 0;
}

int ui_show(gv_ui_device_t *device)
{
    if (device == NULL)
    {
        return -EINVAL;
    }

#ifdef USE_PICO_SSD1306_LIB
    ssd1306_show((ssd1306_t *)device);
#endif // USE_PICO_SSD1306_LIB
    return 0;
}

int ui_clear(gv_ui_device_t *device)
{
    if (device == NULL)
    {
        return -EINVAL;
    }

#ifdef USE_PICO_SSD1306_LIB
    ssd1306_clear(device);
#endif // USE_PICO_SSD1306_LIB
    return 0;
}

int ui_get_display_width(gv_ui_device_t *device)
{
    if (device == NULL)
    {
        return -EINVAL;
    }

    return device->width;
}

int ui_get_display_height(gv_ui_device_t *device)
{
    if (device == NULL)
    {
        return -EINVAL;
    }
    return device->height;
}

int ui_draw_pixel(gv_ui_device_t *device, int32_t x, int32_t y)
{
    if (device == NULL)
    {
        return -EINVAL;
    }

#ifdef USE_PICO_SSD1306_LIB
    ssd1306_draw_pixel(device, x, y);
#endif // USE_PICO_SSD1306_LIB

    return 0;
}

int ui_draw_line(gv_ui_device_t *device, int32_t x1, int32_t y1, int32_t x2, int32_t y2)
{
    if (device == NULL)
    {
        return -EINVAL;
    }

#ifdef USE_PICO_SSD1306_LIB
    ssd1306_draw_line(device, x1, y1, x2, y2);
#endif // USE_PICO_SSD1306_LIB
    return 0;
}

int ui_draw_doted_line(gv_ui_device_t *device, int32_t dot_width, int32_t dot_height, int32_t dot_spacing, int32_t x1, int32_t y1, int32_t x2, int32_t y2)
{
    if (device == NULL)
    {
        return -EINVAL;
    }

#ifdef USE_PICO_SSD1306_LIB

    if (x1 == x2)
    {
        if (y1 > y2)
        {
            swap(&y1, &y2);
        }
        int32_t dot_y_inst = dot_height + dot_spacing; 
        for (int32_t i = y1; i <= y2; i+= dot_y_inst)
        {
            for (int32_t y = 0; y < dot_height; ++y)
            {
                for (int32_t j = 0; j < dot_width; ++j)
                {
                    
                    ssd1306_draw_pixel(device, x1 + j, i + y);
                }
            }
            
        }
        
        return 0;
    }
    else if (y1 == y2)
    {
        if (x1 > x2)
        {
            swap(&x1, &x2);
        }
        int32_t dot_x_inst = dot_width + dot_spacing; 
        for (int32_t i = x1; i <= x2; i+= dot_x_inst)
        {
            for (int32_t y = 0; y < dot_height; ++y)
            {
                for (int32_t j = 0; j < dot_width; ++j)
                {
                    ssd1306_draw_pixel(device, i + j, y1 + y);
                }
            }
            
        }
        
        return 0;
    }
    
    // Diagonal line not supported
    return -ENOTSUP;
    #endif // USE_PICO_SSD1306_LIB

    return 0;
}

int ui_draw_clear_doted_line(gv_ui_device_t *device, int32_t dot_width, int32_t dot_height, int32_t dot_spacing, int32_t x1, int32_t y1, int32_t x2, int32_t y2)
{
    if (device == NULL)
    {
        return -EINVAL;
    }

#ifdef USE_PICO_SSD1306_LIB

    if (x1 == x2)
    {
        if (y1 > y2)
        {
            swap(&y1, &y2);
        }
        int32_t dot_y_inst = dot_height + dot_spacing; 
        for (int32_t i = y1; i <= y2; i+= dot_y_inst)
        {
            ssd1306_clear_square(device, x1, i, dot_width, dot_height);            
        }
        
        return 0;
    }
    else if (y1 == y2)
    {
        if (x1 > x2)
        {
            swap(&x1, &x2);
        }
        int32_t dot_x_inst = dot_width + dot_spacing; 
        for (int32_t i = x1; i <= x2; i+= dot_x_inst)
        {
            for (int32_t y = 0; y < dot_height; ++y)
            {
                for (int32_t j = 0; j < dot_width; ++j)
                {
                    ssd1306_clear_square(device, i + j, y1 + y, 1, 1);
                }
            }
            
        }
        
        return 0;
    }
    
    // Diagonal line not supported
    return -ENOTSUP;
    #endif // USE_PICO_SSD1306_LIB

    return 0;
}

int ui_draw_square(gv_ui_device_t *device, uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
    if (device == NULL)
    {
        return -EINVAL;
    }

#ifdef USE_PICO_SSD1306_LIB
    ssd1306_draw_square(device, x, y, width, height);
#endif // USE_PICO_SSD1306_LIB
    return 0;
}

int ui_clear_square(gv_ui_device_t *device, uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
    if (device == NULL)
    {
        return -EINVAL;
    }

#ifdef USE_PICO_SSD1306_LIB
    ssd1306_clear_square(device, x, y, width, height);
#endif // USE_PICO_SSD1306_LIB
    return 0;
}

int ui_draw_empty_square(gv_ui_device_t *device, uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
    if (device == NULL)
    {
        return -EINVAL;
    }

#ifdef USE_PICO_SSD1306_LIB
    ssd1306_draw_empty_square(device, x, y, width, height);
#endif // USE_PICO_SSD1306_LIB
    return 0;
}

int ui_draw_rounded_rectangle(gv_ui_device_t *device, uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint8_t radius)
{

    if (device == NULL)
    {
        return -EINVAL;
    }

#ifdef USE_ROUNDED_RECTANGLE
#ifdef USE_PICO_SSD1306_LIB

    if (radius > ROUNDED_RECTANGLE_RADIUS_MAX_RADIUS)
    {
        radius = ROUNDED_RECTANGLE_RADIUS_MAX_RADIUS; // Limit radius to the maximum defined
    }

    // Draw horizontal lines (top and bottom, excluding corners)
    ssd1306_draw_line(device, x + radius, y, x + width - radius, y);                   // Top
    ssd1306_draw_line(device, x + radius, y + height, x + width - radius, y + height); // Bottom

    // Draw vertical lines (left and right, excluding corners)
    ssd1306_draw_line(device, x, y + radius, x, y + height - radius);                 // Left
    ssd1306_draw_line(device, x + width, y + radius, x + width, y + height - radius); // Right

    // Draw corners (quarter circles)
    for (int32_t i = 0; i <= radius; i++)
    {
        // Calculate the offset for the arc
        // int32_t offset = (int32_t)(sqrt(radius * radius - i * i)); // Calculate the offset for the arc
        // take the offset from the lookup table
        int32_t offset = offset_lut[radius * (radius + 1) / 2 + i];
        // Top-left corner
        ssd1306_draw_pixel(device, x + radius - offset, y + radius - i);
        ssd1306_draw_pixel(device, x + radius - i, y + radius - offset);

        // Top-right corner
        ssd1306_draw_pixel(device, x + width - radius + offset, y + radius - i);
        ssd1306_draw_pixel(device, x + width - radius + i, y + radius - offset);

        // Bottom-left corner
        ssd1306_draw_pixel(device, x + radius - offset, y + height - radius + i);
        ssd1306_draw_pixel(device, x + radius - i, y + height - radius + offset);

        // Bottom-right corner
        ssd1306_draw_pixel(device, x + width - radius + offset, y + height - radius + i);
        ssd1306_draw_pixel(device, x + width - radius + i, y + height - radius + offset);
    }
#endif // USE_PICO_SSD1306_LIB
#else  // USE_ROUNDED_RECTANGLE
    // Fallback to a simple rectangle if rounded corners are not supported
    ui_draw_square(device, x, y, width, height);
#endif // USE_ROUNDED_RECTANGLE
    return 0;
}

int ui_draw_grid(gv_ui_device_t *device, uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint8_t grid_v_size, uint8_t grid_h_size)
{
    if (device == NULL)
    {
        return -EINVAL;
    }
#ifdef USE_PICO_SSD1306_LIB
    // Draw vertical lines
    for (uint32_t i = x; i < x + width; i += grid_v_size)
    {
        ssd1306_draw_line(device, i, y, i, y + height);
    }

    // Draw horizontal lines
    for (uint32_t i = y; i < y + height; i += grid_h_size)
    {
        ssd1306_draw_line(device, x, i, x + width, i);
    }
    // Draw the last vertical line
    ssd1306_draw_line(device, x + width, y, x + width, y + height);
    // Draw the last horizontal line
    ssd1306_draw_line(device, x, y + height, x + width, y + height);

#endif // USE_PICO_SSD1306_LIB
    return 0;
}

int ui_draw_char_with_font(gv_ui_device_t *device, uint32_t x, uint32_t y, uint32_t scale, const uint8_t *font, char c)
{
    if (device == NULL)
    {
        return -EINVAL;
    }

#ifdef USE_PICO_SSD1306_LIB
    ssd1306_draw_char_with_font(device, x, y, scale, font, c);
#endif // USE_PICO_SSD1306_LIB
    return 0;
}

int ui_draw_string_with_font(gv_ui_device_t *device, uint32_t x, uint32_t y, uint32_t scale, const uint8_t *font, const char *s)
{
    if (device == NULL)
    {
        return -EINVAL;
    }

#ifdef USE_PICO_SSD1306_LIB
    ssd1306_draw_string_with_font(device, x, y, scale, font, s);
#endif // USE_PICO_SSD1306_LIB

    return 0;
}

int ui_draw_char(gv_ui_device_t *device, uint32_t x, uint32_t y, uint32_t scale, char c)
{
    if (device == NULL)
    {
        return -EINVAL;
    }

#ifdef USE_PICO_SSD1306_LIB
    ssd1306_draw_char(device, x, y, scale, c);
#endif // USE_PICO_SSD1306_LIB

    return 0;
}

int ui_draw_string(gv_ui_device_t *device, uint32_t x, uint32_t y, uint32_t scale, const char *s)
{
    if (device == NULL)
    {
        return -EINVAL;
    }

#ifdef USE_PICO_SSD1306_LIB
    ssd1306_draw_string(device, x, y, scale, s);
#endif // USE_PICO_SSD1306_LIB

    return 0;
}

int ui_bmp_show_image(gv_ui_device_t *device, const uint8_t *data, const long size)
{
    if (device == NULL)
    {
        return -EINVAL;
    }

#ifdef USE_PICO_SSD1306_LIB
    ssd1306_bmp_show_image(device, data, size);
#endif // USE_PICO_SSD1306_LIB

    return 0;
}

int ui_bmp_show_image_with_offset(gv_ui_device_t *device, const uint8_t *data, const long size, uint32_t x_offset, uint32_t y_offset)
{

#ifdef USE_PICO_SSD1306_LIB
    ssd1306_bmp_show_image_with_offset(device, data, size, x_offset, y_offset);
#endif // USE_PICO_SSD1306_LIB
    return 0;
}

int ui_get_rounded_rectangle_max_radius()
{
    return ROUNDED_RECTANGLE_RADIUS_MAX_RADIUS - 1;
}
