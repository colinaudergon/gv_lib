
function(unset_config)

    unset(USE_LED_PWM CACHE)
    unset(USE_LOGGER CACHE)
    unset(USE_PWM_OUTPUT_AUDIO CACHE)
    unset(USE_SSD1306 CACHE)
    unset(USE_THREAD_HANDLER CACHE)
    unset(USE_WAV_READER_SPI CACHE)
endfunction()

function(check_macro_defined macro_name result_var)
    # Read the content of the configuration file
    file(READ ${GV_LIB_CONF_FILE} gv_lib_conf_content)
    # Use a regular expression to match uncommented #define directives and capture the value
    string(REGEX MATCH "#define[ \t]+${macro_name}[ \t]*([0-9]*)" match "${gv_lib_conf_content}")

    # Check if the match was found
    if (match)
        # Extract the value of the macro (if any)
        string(REGEX REPLACE ".*#define[ \t]+${macro_name}[ \t]*([0-9]*).*" "\\1" macro_value "${match}")

        # Check if the value is 1 or 0
        if (macro_value STREQUAL "1" OR macro_value STREQUAL "")
            set(${result_var} TRUE PARENT_SCOPE)
            else()
            set(${result_var} FALSE PARENT_SCOPE)
        endif()
    else()
    set(${result_var} FALSE PARENT_SCOPE)
    endif()
endfunction()



function(check_macro_defined_global macro_name result_var)
    # Read the content of the configuration file
    file(READ ${GV_LIB_CONF_FILE} gv_lib_conf_content)

    # Use a regular expression to match uncommented #define directives and capture the value
    string(REGEX MATCH "#define[ \t]+${macro_name}[ \t]*([0-9]*)" match "${gv_lib_conf_content}")

    # Check if the match was found
    if (match)
        # Extract the value of the macro (if any)
        string(REGEX REPLACE ".*#define[ \t]+${macro_name}[ \t]*([0-9]*).*" "\\1" macro_value "${match}")

        # Check if the value is 1 or 0
        if (macro_value STREQUAL "1" OR macro_value STREQUAL "")
            set(${result_var} TRUE CACHE INTERNAL "Global variable set by check_macro_defined_global")
        else()
            set(${result_var} FALSE CACHE INTERNAL "Global variable set by check_macro_defined_global")
        endif()
    else()
        set(${result_var} FALSE CACHE INTERNAL "Global variable set by check_macro_defined_global")
    endif()
endfunction()
