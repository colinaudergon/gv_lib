# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/colin/pico/pico-sdk/tools/pioasm"
  "/home/colin/1_DEV/SYNTH/1_Common_ressources/gv_lib/build/pioasm"
  "/home/colin/1_DEV/SYNTH/1_Common_ressources/gv_lib/build/pioasm-install"
  "/home/colin/1_DEV/SYNTH/1_Common_ressources/gv_lib/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/tmp"
  "/home/colin/1_DEV/SYNTH/1_Common_ressources/gv_lib/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src/pioasmBuild-stamp"
  "/home/colin/1_DEV/SYNTH/1_Common_ressources/gv_lib/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src"
  "/home/colin/1_DEV/SYNTH/1_Common_ressources/gv_lib/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src/pioasmBuild-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/colin/1_DEV/SYNTH/1_Common_ressources/gv_lib/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src/pioasmBuild-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/colin/1_DEV/SYNTH/1_Common_ressources/gv_lib/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src/pioasmBuild-stamp${cfgdir}") # cfgdir has leading slash
endif()
