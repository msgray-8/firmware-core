cmake_minimum_required(VERSION 3.20)

project(firmware_core LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_executable(firmware_core
    src/main.c
)

target_compile_options(firmware_core PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)