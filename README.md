# Firmware Core

A host-based Embedded C development repository focused on building and testing portable firmware components using clean project structure, compiler warnings, automated builds, and version control.

## Current Status

The project currently includes a modular ADC conversion component with host-side automated tests.

## Project Structure

```text
firmware-core/
├── docs/
│   ├── module_boundaries.md
│   └── toolchain.md
├── include/
│   └── adc_conversion.h
├── src/
│   ├── adc_conversion.c
│   ├── day02_types_control_flow.c
│   └── main.c
├── tests/
│   └── test_adc_conversion.c
├── .gitignore
├── CMakeLists.txt
└── README.md
```

## Build

This project uses CMake and Ninja.

Configure the project:

```powershell
cmake -S . -B build -G Ninja
```

Build all targets:

```powershell
cmake --build build
```

## Tests

Run the registered tests with CTest:

```powershell
ctest --test-dir build --output-on-failure
```

Current host-side tests cover:

- Minimum valid ADC sample
- Mid-range ADC sample
- Maximum valid ADC sample
- Invalid ADC sample
- NULL output pointer

## ADC Conversion Module

The ADC conversion module demonstrates:

- `.c` / `.h` modular separation
- Public API design
- Named status codes
- Output parameters
- Defensive NULL-pointer checking
- Input-range validation
- Fixed-width integer arithmetic
- Host-side automated testing

See `docs/module_boundaries.md` for the module architecture and design decisions.

## Development Approach

The repository is being developed incrementally while practicing Embedded C, modular firmware design, testing, build systems, debugging, and version control.