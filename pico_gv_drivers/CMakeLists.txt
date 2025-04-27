cmake_minimum_required(VERSION 3.13)

project(pico_gv_drivers)

set(PICO_GV_DRIVERS_DEP "")
set(PICO_GV_DRIVERS_SRC "")
set(PICO_GV_DRIVERS_INC "")

if(USE_GV_LIB)
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


    # Only add the library if there are source files
    if(PICO_GV_DRIVERS_SRC)
        add_library(pico_gv_drivers  ${PICO_GV_DRIVERS_SRC})
        target_include_directories(pico_gv_drivers PUBLIC ${PICO_GV_DRIVERS_INC})
        target_link_libraries(pico_gv_drivers pico_stdlib ${PICO_GV_DRIVERS_DEP})
    else()
        message(WARNING "pico_gv_drivers: No source files to build the library")
    endif()
else()
message(STATUS "pico_gv_drivers: lib is  used directly")
pico_gv_drivers_direct_include()
endif()

function(pico_gv_drivers_direct_include)
    add_library(pico_gv_drivers
    gpio_interrupts/gpio_interrupts.c
    rotary_encoder/rotary_encoder.c
    )

    target_include_directories(pico_gv_drivers PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/gpio_interrupts
        ${CMAKE_CURRENT_SOURCE_DIR}/rotary_encoder
    )

    # Link with Pico SDK (if applicable)
    target_link_libraries(pico_gv_drivers pico_stdlib )
endfunction()