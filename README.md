# Firmware Core

A host-based Embedded C development repository focused on building and testing portable firmware components using clean project structure, compiler warnings, automated builds, debugging, and version control.

## Current Status

The project currently includes:

- A modular ADC conversion component
- A pointer utilities module
- Host-side automated tests
- CMake/Ninja build support
- CTest-based test execution
- GDB-based debugging practice
- Technical documentation for module boundaries, pointers, ownership, and lifetime
- A bounded command tokenizer with explicit error handling
- A typed sensor/event model using structs, enums, and tagged unions
- Explicit little-endian sensor-record serialization

## Project Structure

```text
firmware-core/
├── docs/
│   ├── arrays_strings_bounds.md
│   ├── module_boundaries.md
│   ├── pointers_and_lifetime.md
│   ├── structs_unions_enums.md
│   └── toolchain.md
├── include/
│   ├── adc_conversion.h
│   ├── event_model.h
│   ├── pointer_utils.h
│   └── tokenizer.h
├── src/
│   ├── adc_conversion.c
│   ├── event_model.c
│   ├── pointer_utils.c
│   ├── tokenizer.c
│   ├── day02_types_control_flow.c
│   └── main.c
├── tests/
│   ├── test_adc_conversion.c
│   ├── test_event_model.c
│   ├── test_pointer_utils.c
│   └── test_tokenizer.c
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

### ADC Conversion

- Minimum valid ADC sample
- Mid-range ADC sample
- Maximum valid ADC sample
- Invalid ADC sample
- NULL output pointer

### Pointer Utilities

- Valid pointer-based value swap
- NULL pointer rejection during swap
- Valid bounded sample summation
- Zero-length buffer handling
- NULL input buffer rejection for non-zero length
- NULL output pointer rejection

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

## Pointer Utilities Module

The pointer utilities module demonstrates:

- Pointer dereferencing and caller-owned data
- Defensive NULL-pointer checks
- `const` correctness for read-only buffers
- Pointer + length APIs for bounded processing
- Safe value swapping through pointers
- Host-side tests for valid and failure cases
- GDB-based pointer inspection
- Ownership and lifetime reasoning

See `docs/pointers_and_lifetime.md` for the related pointer, ownership, and lifetime notes.

## Tokenizer Module

The tokenizer module demonstrates:

- Safe array and buffer bounds handling
- Capacity vs length reasoning
- C string null-termination checks
- Bounded scanning without relying on untrusted `strlen()`
- In-place tokenization using `'\0'`
- Pointer arrays for token references
- Explicit error/status codes
- Protection against too many tokens
- Host-side boundary and failure testing

Current tokenizer tests cover:

- Normal command parsing
- Empty input
- Multiple spaces
- Leading and trailing spaces
- Too many tokens
- Missing null terminator
- NULL input buffer

See `docs/arrays_strings_bounds.md` for the related array, string, and bounds notes.

## Event Model and Serialization

The event model module demonstrates:

- Typed sensor records using `struct`
- Enumerated event types
- Tagged unions for variant event payloads
- Constructor functions that keep tags and payloads consistent
- `sizeof()` and `offsetof()` layout inspection
- Alignment and padding awareness
- Explicit little-endian serialization
- Separation of in-memory layout from wire format

Current event-model tests cover:

- Sensor events
- Button events
- Error events
- Exact sensor-record serialization bytes
- Runtime layout inspection

See `docs/structs_unions_enums.md` for layout, tagged-union, and serialization notes.

## Debugging Checkpoint

Day 7 focused on structured debugging and root-cause analysis using GDB.

The checkpoint covered:

- NULL-pointer propagation
- Off-by-one array access
- Tagged-union tag/payload mismatches
- GDB breakpoints and variable inspection
- Call-stack analysis using backtraces
- Root-cause fixes instead of symptom masking
- Regression-test thinking

See `docs/day07_bug_report.md` for the debugging cases and lessons.

## Development Approach

The repository is being developed incrementally while practicing:

- Embedded C
- Modular firmware design
- Defensive API design
- Host-side testing
- CMake and Ninja
- CTest
- GDB debugging
- Git and GitHub workflows
- Technical documentation

The long-term goal is to evolve this repository from foundational host-side Embedded C exercises into a stronger firmware portfolio containing reusable modules, simulated embedded systems, and target-oriented firmware work.