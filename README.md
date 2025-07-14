# Modern C++ Template Learning Repository

A comprehensive collection of C++ template examples and exercises covering fundamental to advanced template concepts. This repository serves as a learning resource for understanding modern C++ template programming techniques.

## 📋 Table of Contents

- [Overview](#overview)
- [Repository Structure](#repository-structure)
- [Topics Covered](#topics-covered)
- [Building and Running](#building-and-running)
- [Prerequisites](#prerequisites)
- [Examples](#examples)
- [Additional Resources](#additional-resources)

## Overview

This repository contains numbered examples demonstrating various C++ template concepts, from basic function templates to advanced template metaprogramming techniques. Each directory focuses on a specific template feature with practical code examples and Chinese comments for detailed explanations.

## Repository Structure

```
├── 6_template_overload/          # Template overloading
├── 7_variadic_template/          # Variadic templates
├── 8_template_document/          # Template documentation examples
├── 9_class_template/             # Basic class templates
├── 10_deduction_guide/           # Template argument deduction guides
├── 11_default_class_template/    # Default class template parameters
├── 12_class_template_parameter/  # Class template parameters
├── 13_function_member/           # Template member functions
├── 14_variadic_class_template/   # Variadic class templates
├── 15_class_template_document/   # Class template documentation
├── 16_template_variable/         # Variable templates
├── 17_variable_template_default/ # Variable template defaults
├── 18_variadic_variable_template/ # Variadic variable templates
├── 19_static_template_member/    # Static template members
├── 21_template_specialization/   # Template specialization
├── 22_class_template_speciliazation/ # Class template specialization
├── 23_variable_template_specilization/ # Variable template specialization
├── 24_detatil_template_specialization/ # Detailed template specialization
├── 25_conclude_template_specialization/ # Template specialization conclusions
├── 26_partial_specialization/    # Partial specialization
├── 27_class_template_partial_specialization/ # Class template partial specialization
├── 29_is_same_v/                # Type traits examples
├── 31_explicit_instantiation_document_2/ # Explicit instantiation
├── 32_explicit_instantiate_dylib/ # Dynamic library instantiation
├── 33_explicit_instantiate_static_lib/ # Static library instantiation
├── 34_fold_expression/          # C++17 fold expressions
├── 35_36_unqualified_name_lookup/ # Name lookup in templates
└── some_tests/                  # Additional test cases
    ├── template_deduction/      # Template argument deduction tests
    ├── test_enum/              # Enum-related tests
    └── test_enum_2/            # Advanced enum utilities
```

## Topics Covered

### Core Template Concepts
- **Function Templates**: Basic template functions and overloading
- **Class Templates**: Template classes with various parameter types
- **Variable Templates**: Template variables (C++14)
- **Template Argument Deduction**: Automatic type deduction mechanisms
- **Deduction Guides**: Custom deduction rules (C++17)

### Advanced Features
- **Variadic Templates**: Templates with variable numbers of parameters
- **Template Specialization**: Full and partial specialization
- **Fold Expressions**: Parameter pack folding (C++17)
- **SFINAE**: Substitution Failure Is Not An Error techniques
- **Template Metaprogramming**: Compile-time computations

### Practical Applications
- **Library Design**: Creating reusable template components
- **Type Traits**: Custom type checking and manipulation
- **Enum Utilities**: Template-based enum reflection and conversion
- **Explicit Instantiation**: Controlling template instantiation

## Building and Running

Each example directory contains its own `CMakeLists.txt` file. To build and run an example:

```bash
# Navigate to any example directory
cd 10_deduction_guide/

# Create build directory
mkdir build && cd build

# Configure with CMake
cmake ..

# Build
make

# Run the executable
./10_deduction_guide
```

Alternatively, many examples can be built directly using CLion or other IDEs that support CMake.

## Prerequisites

- **C++ Compiler**: GCC 8+, Clang 7+, or MSVC 2019+ with C++17 support
- **CMake**: Version 3.10 or higher
- **Build System**: Make, Ninja, or IDE with CMake support

### Required C++ Standards
- Most examples require **C++14** or higher
- Fold expression examples require **C++17**
- Some advanced features may require **C++20**

## Examples

### Template Deduction Guide (10_deduction_guide/)
```cpp
template<typename T>
struct Test {
    Test(T v): t{v} {}
private:
    T t;
};

// Custom deduction guide
Test(int) -> Test<std::size_t>;
```

### Fold Expressions (34_fold_expression/)
```cpp
template<typename ...Args>
void print(const Args &...args) {
    // C++17 fold expression
    ((std::cout << args << " "), ...);
}
```

### Enum Utilities (some_tests/test_enum_2/)
Advanced template-based enum reflection system providing:
- Compile-time enum to string conversion
- String to enum parsing
- Type-safe enum operations

## Additional Resources

### Learning Path
1. Start with basic function templates (6_template_overload)
2. Progress to class templates (9_class_template)
3. Learn variadic templates (7_variadic_template)
4. Explore template specialization (21_template_specialization)
5. Study advanced features like fold expressions (34_fold_expression)

### Build Integration
The repository demonstrates various build scenarios:
- Header-only templates
- Explicit instantiation in libraries
- Separating template declarations and definitions

## Contributing

This repository serves as a learning resource. When adding new examples:
- Follow the existing naming convention
- Include comprehensive comments (Chinese comments are welcome)
- Provide a complete CMakeLists.txt
- Test with multiple compilers when possible

## License

This educational repository is provided for learning purposes. Please respect any licensing terms of referenced materials or techniques.