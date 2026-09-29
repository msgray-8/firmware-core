# Development Toolchain

Host development environment used for the Firmware Core project.

- Operating System: Windows
- Development Environment: MSYS2 UCRT64
- C Compiler: GCC 16.2.0
- Debugger: GDB 18.1
- Build System Generator: CMake 4.4.3
- Build Tool: Ninja 1.13.2
- Version Control: Git 2.54.0.windows.1

## Compiler Configuration

The project is compiled using the C11 standard with the following warning options:

-std=c11 -Wall -Wextra -Wpedantic

## Build Workflow

C Source
↓
CMake
↓
Ninja
↓
GCC
↓
Executable