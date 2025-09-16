# WARP.md

This file provides guidance to WARP (warp.dev) when working with code in this repository.

## Project Overview

SecureBuffer is a multi-language memory safety library that demonstrates secure memory management concepts. The project implements secure buffer handling across four programming languages: C, C++, C#, and Java. Each implementation showcases language-specific memory safety patterns and secure memory wiping techniques.

## Architecture

The project is organized as a polyglot repository with separate implementations:

- **C Implementation** (`clang/`): Traditional C library with manual memory management and explicit secure memory wiping
- **C++ Implementation** (`cplus/`): Modern C++ using RAII patterns with `std::unique_ptr` and move semantics
- **C# Implementation** (`csharp/`): .NET implementation (currently skeleton)
- **Java Implementation** (`java/`): JVM-based implementation (currently skeleton)

### Core Security Concepts

All implementations focus on:
- **Secure Memory Wiping**: Explicitly clearing sensitive data before deallocation
- **Buffer Bounds Checking**: Preventing buffer overflows and underflows
- **RAII Patterns**: Where applicable, using automatic resource management
- **Move Semantics**: In C++, preventing unnecessary copies of sensitive data

### C Implementation Details

The C implementation (`clang/`) provides:
- `SecureBuffer` struct with `data` pointer and `size` fields
- `SecureBuffer_init()`: Allocates and zero-initializes buffer
- `SecureBuffer_free()`: Securely wipes memory with `memset()` before `free()`
- `SecureBuffer_write()`: Bounds-checked write operation
- `SecureBuffer_print()`: Safe buffer output

### C++ Implementation Details  

The C++ implementation (`cplus/`) features:
- RAII-compliant `SecureBuffer` class using `std::unique_ptr<char[]>`
- Deleted copy constructor/assignment to prevent accidental copies
- Move constructor/assignment for efficient transfers
- `secure_wipe()` static method using volatile pointer to prevent optimization
- Automatic memory clearing in destructor

## Development Commands

### C Implementation (`clang/`)

```bash
# Build all targets (static lib, shared lib, example)
make -C clang

# Build for specific architecture
make -C clang ARCH=arm64

# Build with different compiler
make -C clang CC=clang

# Build and run example
make -C clang run

# Clean build artifacts for current architecture
make -C clang clean

# Clean all architecture builds  
make -C clang distclean
```

### C++ Implementation (`cplus/`)

```bash
# Navigate to C++ directory
cd cplus

# The Makefile exists but is currently empty
# Standard C++ build would be:
# g++ -std=c++14 -Wall -Wextra -O2 -I include src/SecureBuffer.cpp examples/main.cpp -o build/main
```

### Architecture-Specific Builds

The C implementation supports cross-architecture builds:
- Default: `x86_64`
- Override with: `make ARCH=arm64` or `make ARCH=i386`
- Build artifacts go to `build/$(ARCH)/`

### Testing and Examples

Each language directory contains an `examples/` folder with demonstration code:
- `clang/examples/main.c`: Shows basic SecureBuffer usage in C
- `cplus/examples/main.cpp`: Currently empty, intended for C++ examples
- Other language examples are placeholders

## Language-Specific Notes

### Working with C Code
- The implementation uses standard C99 features
- Memory management is explicit - always pair `init()` with `free()`
- Compiler warnings are enabled (`-Wall -Wextra`)
- Position-independent code is generated (`-fPIC`)

### Working with C++ Code
- Requires C++14 or later for `std::make_unique`
- Uses modern RAII and move semantics patterns
- Copy operations are explicitly disabled for security
- Template specializations could be added for different data types

### Development Workflow
When adding new features:
1. Start with the C implementation as the reference
2. Implement equivalent functionality in C++ using modern patterns
3. Consider memory safety implications in all implementations
4. Update example programs to demonstrate new features

## Build System Notes

- C implementation uses Make with configurable compiler and architecture
- Build artifacts are organized by architecture in `build/$(ARCH)/`
- Static and shared libraries are both generated
- Cross-compilation support through `CC` and `ARCH` variables