[![main CI](https://github.com/rturrado/the_modern_cpp_challenge/actions/workflows/main_ci.yml/badge.svg)](https://github.com/rturrado/the_modern_cpp_challenge/actions/workflows/main_ci.yml)

# The Modern C++ Challenge

My solutions to the 100 problems of The Modern C++ Challenge, a book by Marius Bancila's (published by Packt).

These exercises were initially implemented as a project within a bigger Visual Studio solution: [Catching up with modern C++](https://github.com/rturrado/CatchingUpWithModernCpp). And mainly in order to practice _modern C++ (11/14/17/20)_.

However, should you download that solution, you'd need to:
- First, make sure you have installed all the libraries used in the project.
- And then, update the Visual Studio project properties that contain absolute paths to those libraries (e.g., C/C++ > General > Additional Include Directories and Linker > Input > Additional Dependencies).

The goal behind The Modern C++ Challenge project is to be downloaded, built, and executed with a minimal effort and without having to install any library.
And, in order to do that, to get some hands-on experience with _CMake_.

Also, while working on this project, I've taken the chance to complete the original code with:
  - _Tests_ (google tests).
  - _Benchmarks_ (google benchmarks).
  - _Continuous integration_ (GitHub actions).

## Requirements
- cmake
- git

## Installation
### Clone
```bash
git clone https://github.com/rturrado/the_modern_cpp_challenge.git
```

### Build
The following code snippets assume that you are within the cloned directory.

Keep in mind that you can create the `build` folder elsewhere.

Also, that you can use other build types, e.g. `Debug` or `RelWithDebInfo`.

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```

### Run
```bash
cd build\src\Release
.\the_modern_c++_challenge.exe
```

### Tests
```bash
cmake -B build -DCMAKE_BUILD_TYPE=Debug -DTHE_MODERN_C++_CHALLENGE_BUILD_TESTS=ON
cmake --build build --config Debug
cd build
ctest -C Debug --output-on-failure
```
      
### Benchmarks
```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release -DTHE_MODERN_C++_CHALLENGE_BUILD_BENCHMARKS=ON
cmake --build build --config Release
cd build\benchmark\Release
.\the_modern_c++_challenge_benchmark.exe
```
  
## Dependencies

The following libraries are used in this project, but are automatically downloaded and made available via CMake's `FetchContent`.

- [benchmark](github.com/google/benchmark.git): Google benchmark.
- [fmt](https://github.com/fmtlib/fmt): formatting library with more features than C++ iostreams.
- [googletest](github.com/google/googletest.git): GoogleTest and GoogleMock.
- [range-v3](https://github.com/ericniebler/range-v3): range library with many more features than what have been added to C++20.
- [rtc](https://github.com/rturrado/rtc): some utilities I use in different C++ projects.
