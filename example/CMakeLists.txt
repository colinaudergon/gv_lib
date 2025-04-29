cmake_minimum_required(VERSION 3.16)

# add_subdirectory(led_pwm)
if(USE_WAV_READER_SPI)
add_subdirectory(fat_fs_spi_sd_card)
endif()

if(USE_THREAD_HANDLER)
add_subdirectory(thread_handler)
endif()

if(USE_PWM_OUTPUT_AUDIO)
add_subdirectory(pwm_audio_output)
endif()