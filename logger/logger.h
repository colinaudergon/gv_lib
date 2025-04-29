#ifndef _LOGGER_H_
#define _LOGGER_H_

#include "pico/stdlib.h"
#include <stdio.h>

#define LOG_DEBUG(fmt, ...) printf("[DEBUG] " fmt"\n", ##__VA_ARGS__)
#define LOG_INF(fmt, ...) printf("[INFO] " fmt"\n", ##__VA_ARGS__)
#define LOG_WARN(fmt, ...) printf("[WARN] " fmt"\n", ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...) printf("\033[1;31m[ERROR] " fmt "\033[0m\n", ##__VA_ARGS__)

#endif /*_LOGGER_H_*/

