cmake_minimum_required(VERSION 3.19)

project(pico_gv_drivers)

set(PICO_GV_DRIVERS_DEP "")
set(PICO_GV_DRIVERS_SRC "")
set(PICO_GV_DRIVERS_INC "")


message(STATUS "pico_gv_drivers: lib used via gv_lib")
if(USE_ROTARY_ENCODER)
    message(STATUS "pico_gv_drivers: rotary encoder used")
    set(PICO_GV_ENCODER_SRC 
        gpio_interrupts/gpio_interrupts.c 
        rotary_encoder/rotary_encoder.c
        )

    set(PICO_GV_ENCODER_INC
    ${CMAKE_CURRENT_SOURCE_DIR}/gpio_interrupts
    ${CMAKE_CURRENT_SOURCE_DIR}/rotary_encoder
    )

    list(APPEND PICO_GV_DRIVERS_SRC ${PICO_GV_ENCODER_SRC})
    list(APPEND PICO_GV_DRIVERS_INC ${PICO_GV_ENCODER_INC})
endif()#USE_ROTARY_ENCODER

if(USE_LED_PWM)
    message(STATUS "pico_gv_drivers: led pwm used")
    set(PICO_GV_LED_PWM_SRC 
        led_pwm/led_pwm.c
        )

    set(PICO_GV_LED_PWM_INC
    ${CMAKE_CURRENT_SOURCE_DIR}/led_pwm
    )
    
    set(PICO_GV_LED_PWM_DEP hardware_pwm)
    list(APPEND PICO_GV_DRIVERS_SRC ${PICO_GV_LED_PWM_SRC})
    list(APPEND PICO_GV_DRIVERS_INC ${PICO_GV_LED_PWM_INC})
    list(APPEND PICO_GV_DRIVERS_DEP ${PICO_GV_LED_PWM_DEP})
endif()#USE_LED_PWM

if(USE_PWM_OUTPUT_AUDIO)

include(${CMAKE_CURRENT_SOURCE_DIR}/pwm_audio_output/cmake/test_config.cmake)

message(STATUS "pico_gv_drivers: USE_PWM_OUTPUT_AUDIO is enabled")

if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/pwm_audio_output/conf/pwm_output_audio_conf.h.in)
    message(STATUS "pico_gv_drivers: pwm audio output used")
    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/pwm_audio_output/conf/pwm_output_audio_conf.h)
        file(REMOVE ${CMAKE_CURRENT_SOURCE_DIR}/pwm_audio_output/conf/pwm_output_audio_conf)
    endif()
else()
    message(FATAL_ERROR "pwm_output_audio_conf.h.in not found in ${CMAKE_CURRENT_SOURCE_DIR}/pwm_audio_output/conf/")
endif()


gen_config_pwm_audio_fn()

set(PWM_AUDIO_OUTPUT_SRC ${CMAKE_CURRENT_SOURCE_DIR}/pwm_audio_output/src/pwm_audio_output.c)
set(PWM_AUDIO_OUTPUT_INC ${CMAKE_CURRENT_SOURCE_DIR}/pwm_audio_output/include)
set(PWM_AUDIO_OUTPUT_DEP 
logger
hardware_dma 
hardware_pwm 
hardware_irq 
hardware_clocks 
hardware_structs
)



list(APPEND PICO_GV_DRIVERS_SRC ${PWM_AUDIO_OUTPUT_SRC})
list(APPEND PICO_GV_DRIVERS_INC ${PWM_AUDIO_OUTPUT_INC})
list(APPEND PICO_GV_DRIVERS_DEP ${PWM_AUDIO_OUTPUT_DEP})

endif()#USE_PWM_AUDIO_OUTPUT


#i2s driver
if(USE_I2S)
set(GV_I2S_DRIVER_SRC "")
set(GV_I2S_DRIVER_DEP "")
set(GV_I2S_DRIVER_INC "")

# Source files
set(GV_I2S_DRIVER_SRC
i2s_driver/rp2040_i2s_example/i2s.c
)



# Include directories
set(GV_I2S_DRIVER_INC
    ${CMAKE_CURRENT_SOURCE_DIR}/i2s_driver/rp2040_i2s_example
)

# Dependencies
set(GV_I2S_DRIVER_DEP
    pico_stdlib
    hardware_i2c
    hardware_dma
    hardware_pio
    hardware_clocks
)

list(APPEND PICO_GV_DRIVERS_SRC ${GV_I2S_DRIVER_SRC})
list(APPEND PICO_GV_DRIVERS_INC ${GV_I2S_DRIVER_INC})
list(APPEND PICO_GV_DRIVERS_DEP ${GV_I2S_DRIVER_DEP})
endif()#USE_I2S

# Only add the library if there are source files
if(PICO_GV_DRIVERS_SRC)
    add_library(pico_gv_drivers  ${PICO_GV_DRIVERS_SRC})
    target_include_directories(pico_gv_drivers PUBLIC ${PICO_GV_DRIVERS_INC})
    target_link_libraries(pico_gv_drivers pico_stdlib ${PICO_GV_DRIVERS_DEP})


# Generate the PIO header file for i2s
pico_generate_pio_header(pico_gv_drivers ${CMAKE_CURRENT_LIST_DIR}/i2s_driver/rp2040_i2s_example/i2s.pio)

else()
    message(WARNING "pico_gv_drivers: No source files to build the library")
endif()

