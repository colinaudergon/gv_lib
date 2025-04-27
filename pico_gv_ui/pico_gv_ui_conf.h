#ifndef _PICO_GV_UI_CONF_H_
#define _PICO_GV_UI_CONF_H_
// #include "helpers/pico_gv_ui_conf_helper.h"
/* set to 1 to enable, 0 to disable*/

#define USE_PICO_SSD1306_LIB  1 // Use the pico-ssd1306 library
#define USE_ROUNDED_RECTANGLE 1 // Use rounded rectangle



#if USE_PICO_SSD1306_LIB == 1
/*
Define I2C instances as macros for compile-time checks
*/
#define I2C_INSTANCE_DEFAULT 0
#define I2C_INSTANCE_0       1
#define I2C_INSTANCE_1       2
/*
Select the I2C instance to use
- I2C_INSTANCE_0 => pico_sdk i2c0
- I2C_INSTANCE_1 => pico_sdk i2c1
- I2C_INSTANCE_DEFAULT => pico_sdk i2c_default
*/

#define SSD1306_I2C_INSTANCE I2C_INSTANCE_DEFAULT // I2C instance to use

#if SSD1306_I2C_INSTANCE == I2C_INSTANCE_DEFAULT
#define SSD1306_I2C_SDA_PIN 4
#define SSD1306_I2C_SCL_PIN 5
#else
/*
Select the I2C pins to use
- SDA pin
    i2c0: 0/4/8/12/16/20
    i2c1: 2/6/10/14/18/26
- SCL pin
    i2c0: 1/5/9/13/17/21
    i2c1: 3/7/11/15/19/27
*/
#define SSD1306_I2C_SDA_PIN 4
#define SSD1306_I2C_SCL_PIN 5
#endif // SSD1306_I2C_INSTANCE == i2c_default

#define SSD1306_WIDTH 128
#define SSD1306_HEIGHT 64
#define SSD1306_MAX_DIMENSION MAX(SSD1306_WIDTH, SSD1306_HEIGHT)
#define SSD1306_MIN_DIMENSION MIN(SSD1306_WIDTH, SSD1306_HEIGHT)
#define SSD1306_I2C_ADDRESS 0x3C // I2C address of the display
#define SSD1306_SPEED 400000    // I2C communication speed
#endif // USE_PICO_SSD1306_LIB

#if USE_ROUNDED_RECTANGLE == 1

#if USE_PICO_SSD1306_LIB == 1
#define ROUNDED_RECTANGLE_RADIUS_MAX_RADIUS SSD1306_MIN_DIMENSION/2 // Maximum radius for rounded rectangle
#endif // USE_PICO_SSD1306_LIB

#define ROUNDED_RECTANGLE_RADIUS_MIN_RADIUS 1 // Minimum radius for rounded rectangle
#define ROUNDED_RECTANGLE_RADIUS_DEFAULT_RADIUS 5 // Default radius for rounded rectangle
#define ROUNDED_RECTANGLE_OFFSET_LUT_SIZE ((ROUNDED_RECTANGLE_RADIUS_MAX_RADIUS * (ROUNDED_RECTANGLE_RADIUS_MAX_RADIUS + 1)) / 2)

#endif // USE_ROUNDED_RECTANGLE

#endif /*_PICO_GV_UI_CONF_H_*/