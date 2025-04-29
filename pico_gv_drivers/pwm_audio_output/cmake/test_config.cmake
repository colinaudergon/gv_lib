
include(${GV_LIB_FUNCTIONS_FILE})

set(List1
    "GV_LIB_USE_8BIT_PWM"
    "GV_LIB_USE_16BIT_PWM"
    "GV_LIB_USE_PWM_AUDIO_LOGGER"
)

set(List2
    "USE_8BIT_PWM"
    "USE_16BIT_PWM"
    "USE_PWM_AUDIO_LOGGER"
)


function(test_pwm_audio_config_fn )
    message(STATUS "pico_gv_drivers: Testing the pwm audio config")


    # Iterate through the lists
    list(LENGTH List1 list_length)
    math(EXPR last_index "${list_length} - 1")

    foreach(index RANGE 0 ${last_index})
        list(GET List1 ${index} macro_name)
        list(GET List2 ${index} cmake_var)

        # Unset the variable to ensure it is reset
        unset(${cmake_var} CACHE)

        # Call the function to check the macro and set the CMake variable
        check_macro_defined_global(${macro_name} ${cmake_var})
        if(${cmake_var})
            message(STATUS "pico_gv_drivers: ${macro_name} is defined")
        else()
            message(STATUS "pico_gv_drivers: ${macro_name} is not defined")
        endif()
    endforeach()
    message(STATUS "pico_gv_drivers: Finished testing the pwm audio config")
endfunction()



function(gen_config_pwm_audio_fn )
    message(STATUS "pico_gv_drivers: Testing the pwm audio config")


    # Iterate through the lists
    list(LENGTH List1 list_length)
    math(EXPR last_index "${list_length} - 1")

    foreach(index RANGE 0 ${last_index})
        list(GET List1 ${index} macro_name)
        list(GET List2 ${index} cmake_var)

        # Unset the variable to ensure it is reset
        unset(${cmake_var} CACHE)

        # Call the function to check the macro and set the CMake variable
        check_macro_defined_global(${macro_name} ${cmake_var})
        if(${cmake_var})
            message(STATUS "pico_gv_drivers: ${macro_name} is defined")
        else()
            message(STATUS "pico_gv_drivers: ${macro_name} is not defined")
        endif()
    endforeach()
    configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/pwm_audio_output/conf/pwm_output_audio_conf.h.in
        ${CMAKE_CURRENT_SOURCE_DIR}/pwm_audio_output/conf/pwm_output_audio_conf.h
    )
    message(STATUS "pico_gv_drivers: Finished testing the pwm audio config")
endfunction()


