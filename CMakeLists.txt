cmake_minimum_required(VERSION 3.20)

project(firmware_core LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# ADC conversion module
add_library(adc_conversion
    src/adc_conversion.c
)

target_include_directories(adc_conversion PUBLIC
    include
)

target_compile_options(adc_conversion PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)

# Main application
add_executable(firmware_core
    src/main.c
)

target_link_libraries(firmware_core PRIVATE
    adc_conversion
)

target_compile_options(firmware_core PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)

# ADC conversion tests
add_executable(test_adc_conversion
    tests/test_adc_conversion.c
)

target_link_libraries(test_adc_conversion PRIVATE
    adc_conversion
)

target_compile_options(test_adc_conversion PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)

enable_testing()

add_test(
    NAME adc_conversion_tests
    COMMAND test_adc_conversion
)