# gv_lib

## Overview

`gv_lib` is a collection of custom libraries and library wrappers designed for use with the Raspberry Pi Pico. These libraries provide functionality to simplify and enhance development on the Pico platform, including WAV file reading, SD card interaction, rotary encoders implementation and LCD display suport.

## Getting Started

### Prerequisites

- A Raspberry Pi Pico development environment set up with the Pico SDK.
- `cmake` and a compatible build system installed on your machine.

### Configuration

Before building the project, ensure the configuration file `gv_lib_conf.h` is properly set up. This file contains settings and options for the libraries included in the project.

### Building the Project

1. Clone the repository:
   ```bash
   git clone <repository-url>
   cd gv_lib
   ```
2. Configure the project using cmake:
   ```bash
   mkdir build
   cd build
   cmake ..
   ```
3. Build the project:
   ```bash
   make
   ```
4. Flash the resulting binary to your Raspberry Pi Pico.

### Basic Usage
1. Enable the desired configurations in gv_lib.conf.
2. Build the project using the standard cmake workflow as described above.
3. Use the provided libraries in your application code
