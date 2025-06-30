# satgalaxy-core 🌌

**A unified C interface for SAT solvers, supporting multiple operating systems.**

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Build Status](https://img.shields.io/badge/Build-Passing-brightgreen)](https://github.com/sat-galaxy/satgalaxy-core/actions) 
[![Contributors](https://img.shields.io/github/contributors/sat-galaxy/satgalaxy-core)](https://github.com/sat-galaxy/satgalaxy-core/graphs/contributors) 

### Platform & Build Compatibility


![Linux](https://img.shields.io/badge/OS-Linux-informational?logo=linux&logoColor=white)
![macOS](https://img.shields.io/badge/OS-macOS-informational?logo=apple&logoColor=white)
![Windows](https://img.shields.io/badge/OS-Windows-informational?logo=windows&logoColor=white)
![Build System: CMake](https://img.shields.io/badge/Build%20System-CMake-blue?logo=cmake&logoColor=white)
---

`satgalaxy-core` aims to provide a standardized C language interface for SAT (Boolean Satisfiability Problem) solvers, simplifying the integration and use of various SAT solvers across different operating systems. Currently, we've integrated **Minisat** and **Glucose** solvers.



## 🚀 Project Goals

* **Unified Interface**: Offer a clean, consistent C API to interact with different SAT solvers, abstracting away low-level implementation details.
* **Multi-OS Support**: Ensure that integrated SAT solvers compile and run smoothly on major operating systems like Linux, macOS, and Windows.
* **Simplified Integration**: Make it easy for other projects (e.g., higher-level language bindings, domain-specific applications) to leverage powerful SAT solving capabilities.
* **Modularity & Extensibility**: Design a modular architecture for easy addition of more SAT solvers in the future.

---

## ✨ Supported Solvers

* **Minisat**: A widely popular and robust SAT solver, known for its concise code and good performance.
* **Glucose**: An acclaimed improvement over Minisat, consistently performing well in SAT competitions, especially when dealing with complex and unsatisfiable (UNSAT) instances.

---

## 📦 How to Use

### Building `satgalaxy-core`

`satgalaxy-core` uses **CMake** for its build system.

1.  **Clone the repository**:
    ```bash
    git clone https://github.com/sat-galaxy/satgalaxy-core.git
    cd satgalaxy-core
    ```

2.  **Build with CMake**:
    ```bash
    mkdir build
    cd build
    cmake ..
    make
    ```
    This command will automatically  build and configure the integrated SAT solvers. Upon successful compilation, you'll find the static library files (`.a` or `.lib`) in `${CMAKE_BINARY_DIR}/lib` (e.g., `build/lib`) and the necessary header files in `${CMAKE_BINARY_DIR}/include` (e.g., `build/include`).

### Integrating into Your Project

`satgalaxy-core` is designed to be used as a static or dynamic library.

1.  **Include Headers**:
    Configure your compiler to look for header files in the `${CMAKE_BINARY_DIR}/include` directory of your `satgalaxy-core` build.

2.  **Link Libraries**:
    Link against the static library files found in the `${CMAKE_BINARY_DIR}/lib` directory. Depending on your build system (CMake, Makefiles, etc.), this might involve adding flags like `-L/path/to/satgalaxy-core/build/lib -lsatgalaxy_minisat -lsatgalaxy_glucose` (actual library names may vary based on your CMakeLists.txt).

### Example Code (Minisat)

This example demonstrates how to use the Minisat interface provided by `satgalaxy-core` to solve a simple SAT problem. This assumes you've correctly configured your build system to find the `satgalaxy-core` headers and link to its libraries.
```c
#include <stdio.h>
#include "satgalaxy/satgalaxy_minisat.h" 

int main() {
    void * solver = minisat_new_solver();

    // Add some variables
    minisat_new_var(solver); // Variable 1
    minisat_new_var(solver); // Variable 2
    minisat_new_var(solver); // Variable 3

    // Add clause: (1 OR -2)
    int clause1[] = {1, -2}; // 0 indicates end of clause
    minisat_add_clause(solver, clause1,2);

    // Add clause: (2 OR 3)
    int clause2[] = {2, 3};
    minisat_add_clause(solver, clause2,2);

    // Solve
    if (minisat_solve(solver)) {
        printf("SATISFIABLE!\n");
        // Get model (assignment)
        printf("Model: var 1 = %d, var 2 = %d, var 3 = %d\n",
               minisat_get_value(solver, 1),
               minisat_get_value(solver, 2),
               minisat_get_value(solver, 3));
    } else {
        printf("UNSATISFIABLE!\n");
    }

    minisat_destroy_solver(solver);
    return 0;
}
```

## 🛠️ Development & Contribution

We welcome community contributions! If you're interested in adding new SAT solvers to `satgalaxy-core` or improving existing code, please follow these steps:

  1. **Fork** this repository.
  2. Create your feature branch (`git checkout -b feature/AmazingFeature`).
  3. Commit your changes (`git commit -m 'Add some AmazingFeature`).
  4. Push to the branch (`git push origin feature/AmazingFeature`).
  5. Open a Pull Request.

Before contributing, please ensure your code adheres to project standards and is thoroughly tested.

## 📜 License

This project is distributed under the MIT License.

## 📧 Contact

If you have any questions or suggestions, feel free to open an Issue.