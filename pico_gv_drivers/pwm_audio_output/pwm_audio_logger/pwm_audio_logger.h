#ifndef _PWM_AUDIO_LOGGER_H_
#define _PWM_AUDIO_LOGGER_H_


#ifdef USE_PWM_AUDIO_LOGGER
#include "pico/stdlib.h"
#include "logger.h"
#include <stdio.h>

#define PWM_AUDIO_LOG_DEBUG(fmt, ...) LOG_DEBUG(fmt, ##__VA_ARGS__)
#define PWM_AUDIO_LOG_INF(fmt, ...) LOG_INF(fmt, ##__VA_ARGS__)
#define PWM_AUDIO_LOG_WARN(fmt, ...) LOG_WARN(fmt, ##__VA_ARGS__)
#define PWM_AUDIO_LOG_ERROR(fmt, ...) LOG_ERROR(fmt, ##__VA_ARGS__)
#else

#define PWM_AUDIO_LOG_DEBUG(fmt, ...) 
#define PWM_AUDIO_LOG_INF(fmt, ...) 
#define PWM_AUDIO_LOG_WARN(fmt, ...) 
#define PWM_AUDIO_LOG_ERROR(fmt, ...)

#endif

#endif /*_PWM_AUDIO_LOGGER_H_*/