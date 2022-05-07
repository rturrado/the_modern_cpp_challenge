[![main CI](https://github.com/rturrado/the_modern_cpp_challenge/actions/workflows/main_ci.yml/badge.svg)](https://github.com/rturrado/the_modern_cpp_challenge/actions/workflows/main_ci.yml)

# The Modern C++ Challenge

My solutions to the 100 problems of The Modern C++ Challenge, a book by Marius Bancila's (published by Packt).

These exercises were initially implemented as a project within a bigger Visual Studio solution: [Catching up with modern C++](https://github.com/rturrado/CatchingUpWithModernCpp). And mainly in order to practice _modern C++ (11/14/17/20)_.

However, should you download that solution, you'd need to:
- First, make sure you have installed all the libraries used in the project.
- And then, update the Visual Studio project properties that contain absolute paths to those libraries (e.g., C/C++ > General > Additional Include Directories, and Linker > Input > Additional Dependencies).

The goal behind The Modern C++ Challenge project is to be downloaded, built, and executed with a minimal effort and without having to install any library.
And, in order to do that, to get some hands-on experience with _CMake_.

Also, while working on this project, I've taken the chance to complete the original code with:
  - _Tests_ (google tests).
  - _Benchmarks_ (google benchmarks).
  - _Continuous integration_ (GitHub actions).

## Installation

### Requirements [TODO]
My idea is to provide a docker with all the required software already installed (even this project). While creating that docker, I will properly document this section as well.

- **Boost libraries**: download a zip file and extract it (e.g., to C:\Libraries). This project has been tested with version 1.78.0. You can download the current version from https://www.boost.org/users/download/, or older versions from https://www.boost.org/users/history/. The extraction directory will be passed to CMake as a parameter (e.g. `-DBOOST_ROOT=C:\Libraries\boost_1_78_0`). This project only uses headers, not library binaries, so no build is needed.
- **CMake**: this project uses version 3.20.
- **git**.

### Clone
```bash
git clone https://github.com/rturrado/the_modern_cpp_challenge.git
```

### Build
The following code snippets make a few assumptions: first, that you are within the cloned directory; also, that Boost root directory is `C:\Libraries\boost_1_78_0`; you'll have to make `BOOST_ROOT` CMake's parameter point to your Boost's root directory.

Keep in mind that you can create the `build` folder elsewhere.

Also, that you can use other build types, e.g. `Debug` or `RelWithDebInfo`.

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release -DBOOST_ROOT=C:\Libraries\boost_1_78_0
cmake --build build --config Release
```

#### Output binaries
All successful builds will generate:
- `the_modern_c++_challenge.exe`: the main binary, a console application that interacts with the user to execute the different problems from the book.
- `the_modern_c++_challenge.lib`: a static library, used, for example, by the test and benchmark binaries.

Debug builds with the option `-DTHE_MODERN_C++_CHALLENGE_BUILD_TESTS=ON` will also generate:
- `the_modern_c++_challenge_test.exe`: a console application to test the code.

Release builds with the option `-DTHE_MODERN_C++_CHALLENGE_BUILD_BENCHMARKS=ON` will also generate:
- `the_modern_c++_challenge_benchmark.exe`: a console application to benchmark the code.

### Run
```bash
cd build\src
.\Release\the_modern_c++_challenge.exe
```

Notice some problems use the `res` folder within `build\src`, and expect the main binary to be executed from that directory.

### Tests
```bash
cmake -B build -DCMAKE_BUILD_TYPE=Debug -DTHE_MODERN_C++_CHALLENGE_BUILD_TESTS=ON -DBOOST_ROOT=C:\Libraries\boost_1_78_0
cmake --build build --config Debug
cd build
ctest -C Debug --output-on-failure
```

Alternatively, if you want a less verbose ouptut, you can run:

```bash
ctest -C Debug --output-on-failure --progress
```

Or:

```bash
cd build\test
.\Debug\the_modern_c++_challenge_test.exe --gtest_brief=1
```

Notice some problems use the `res` folder within `build\test`, and expect the test binary to be executed from that directory.

### Benchmarks
```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release -DTHE_MODERN_C++_CHALLENGE_BUILD_BENCHMARKS=ON -DBOOST_ROOT=C:\Libraries\boost_1_78_0
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

However, the libraries below need to be installed in the system:

- [boost](https://www.boost.org/): Boost libraries.
