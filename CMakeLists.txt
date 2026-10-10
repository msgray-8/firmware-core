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

# Pointer utilities module
add_library(pointer_utils
    src/pointer_utils.c
)

target_include_directories(pointer_utils PUBLIC
    include
)

target_compile_options(pointer_utils PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)

# Tokenizer module
add_library(tokenizer
    src/tokenizer.c
)

target_include_directories(tokenizer PUBLIC
    include
)

target_compile_options(tokenizer PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)

# Event model module
add_library(event_model
    src/event_model.c
)

target_include_directories(event_model PUBLIC
    include
)

target_compile_options(event_model PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)

# Bitfield module
add_library(bitfield
    src/bitfield.c
)

target_include_directories(bitfield PUBLIC
    include
)

target_compile_options(bitfield PRIVATE
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
    pointer_utils
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

# Pointer utilities tests
add_executable(test_pointer_utils
    tests/test_pointer_utils.c
)

target_link_libraries(test_pointer_utils PRIVATE
    pointer_utils
)

target_compile_options(test_pointer_utils PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)

# Tokenizer tests
add_executable(test_tokenizer
    tests/test_tokenizer.c
)

target_link_libraries(test_tokenizer PRIVATE
    tokenizer
)

target_compile_options(test_tokenizer PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)

# Event model tests
add_executable(test_event_model
    tests/test_event_model.c
)

target_link_libraries(test_event_model PRIVATE
    event_model
)

target_compile_options(test_event_model PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)

# Bitfield tests
add_executable(test_bitfield
    tests/test_bitfield.c
)

target_link_libraries(test_bitfield PRIVATE
    bitfield
)

target_compile_options(test_bitfield PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)

enable_testing()

add_test(
    NAME adc_conversion_tests
    COMMAND test_adc_conversion
)

add_test(
    NAME pointer_utils_tests
    COMMAND test_pointer_utils
)

add_test(
    NAME tokenizer_tests
    COMMAND test_tokenizer
)

add_test(
    NAME event_model_tests
    COMMAND test_event_model
)

add_test(
    NAME bitfield_tests
    COMMAND test_bitfield
)