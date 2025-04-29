#ifndef _PWM_AUDIO_LOGGER_H_
#define _PWM_AUDIO_LOGGER_H_

#ifdef USE_PWM_AUDIO_LOGGER
#include "pico/stdlib.h"
#include "logger.h"
#include <stdio.h>

// Define logging macros for PWM audio
#define PWM_AUDIO_LOG_DEBUG(fmt, ...) printf("[DEBUG] " fmt "\n", ##__VA_ARGS__)
#define PWM_AUDIO_LOG_INF(fmt, ...)   printf("[INFO] " fmt "\n", ##__VA_ARGS__)
#define PWM_AUDIO_LOG_WARN(fmt, ...)  printf("[WARN] " fmt "\n", ##__VA_ARGS__)
#define PWM_AUDIO_LOG_ERROR(fmt, ...) printf("\033[1;31m[ERROR] " fmt "\033[0m\n", ##__VA_ARGS__)

#else

// Define empty macros if logging is disabled
#define PWM_AUDIO_LOG_DEBUG(fmt, ...) 
#define PWM_AUDIO_LOG_INF(fmt, ...) 
#define PWM_AUDIO_LOG_WARN(fmt, ...) 
#define PWM_AUDIO_LOG_ERROR(fmt, ...) 

#endif // USE_PWM_AUDIO_LOGGER

#endif /* _PWM_AUDIO_LOGGER_H_ */