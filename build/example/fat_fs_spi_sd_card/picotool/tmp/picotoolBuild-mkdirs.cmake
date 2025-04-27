# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/colin/1_DEV/SYNTH/1_Common_ressources/gv_lib/build/_deps/picotool-src"
  "/home/colin/1_DEV/SYNTH/1_Common_ressources/gv_lib/build/_deps/picotool-build"
  "/home/colin/1_DEV/SYNTH/1_Common_ressources/gv_lib/build/_deps"
  "/home/colin/1_DEV/SYNTH/1_Common_ressources/gv_lib/build/example/fat_fs_spi_sd_card/picotool/tmp"
  "/home/colin/1_DEV/SYNTH/1_Common_ressources/gv_lib/build/example/fat_fs_spi_sd_card/picotool/src/picotoolBuild-stamp"
  "/home/colin/1_DEV/SYNTH/1_Common_ressources/gv_lib/build/example/fat_fs_spi_sd_card/picotool/src"
  "/home/colin/1_DEV/SYNTH/1_Common_ressources/gv_lib/build/example/fat_fs_spi_sd_card/picotool/src/picotoolBuild-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/colin/1_DEV/SYNTH/1_Common_ressources/gv_lib/build/example/fat_fs_spi_sd_card/picotool/src/picotoolBuild-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/colin/1_DEV/SYNTH/1_Common_ressources/gv_lib/build/example/fat_fs_spi_sd_card/picotool/src/picotoolBuild-stamp${cfgdir}") # cfgdir has leading slash
endif()
