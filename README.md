[![main CI](https://github.com/rturrado/the_modern_cpp_challenge/actions/workflows/main_ci.yml/badge.svg)](https://github.com/rturrado/the_modern_cpp_challenge/actions/workflows/main_ci.yml)
[![unixlike-builds CI](https://github.com/rturrado/the_modern_cpp_challenge/actions/workflows/unixlike-builds_ci.yml/badge.svg)](https://github.com/rturrado/the_modern_cpp_challenge/actions/workflows/unixlike-builds_ci.yml)
[![codecov](https://codecov.io/github/rturrado/the_modern_cpp_challenge/branch/unixlike-builds/graph/badge.svg?token=GAF6OX0ZVE)](https://codecov.io/github/rturrado/the_modern_cpp_challenge)

# The Modern C++ Challenge

My solutions to the 100 problems of The Modern C++ Challenge, a book by Marius Bancila's (published by Packt).

These exercises were initially implemented as a project within a bigger Visual Studio solution, [Catching up with modern C++](https://github.com/rturrado/CatchingUpWithModernCpp), as a way of practicing _modern C++ (11/14/17/20)_. However, anyone downloading that project would need to:
- Make sure they have installed all the libraries used in the code.
- And update the Visual Studio project properties containing absolute paths to those libraries (e.g., _C/C++ > General > Additional Include Directories, and Linker > Input > Additional Dependencies_).

The goal behind The Modern C++ Challenge project is twofold. On one hand, let users download, build, and execute the code with a minimal effort (ideally without needing to install any library). On the personal side, get some hands-on experience with _CMake_ and other tools of the C++ ecosystem. I've also taken the chance to improve the original code with:
  - _Tests_ (google tests).
  - _Benchmarks_ (google benchmarks).
  - _Continuous integration_ (GitHub actions).
  - _Static analysis tools_ (CLion's Inspect Code)

And I plan to better it further by sanitizers.

At the moment, the `main` branch only builds on Windows/msvc. There is though a `unixlike-builds` branch (release `unixlike-builds-v1.0.0`) that compiles on Unix-like systems, and provides the same functionality as `main` (release `v2.0.0`).

The instructions below refer to Windows/msvc. For Unix, my intention is to provide a docker with the project and all the software needed to build it and run it.

## Installation

### Requirements

- **Boost libraries**: this project has been tested with version 1.78.0. 
- **Microsoft Visual C++ (MSVC) compiler toolset**.
- **CMake**: required minimum version is 3.22.
- **git**.

Most of the required software can be installed from the [Visual Studio 2022 Installer](https://visualstudio.microsoft.com/thank-you-downloading-visual-studio/?sku=Community&channel=Release&version=VS2022&source=VSLandingPage&cid=2030&passive=false).

- **Microsoft Visual C++ (MSVC) compiler toolset**: *Workloads* tab, *Desktop development with C++* item.
- **CMake**: *Individual components* tab, *Compilers, build tools, and runtimes* section, *C++ CMake tools for Windows* item.
- **git**: *Individual components* tab, *Code tools* section, *Git for Windows* item.

You can download the current version of the **Boost libraries** from https://www.boost.org/users/download/.
- Notice it's not necessary to build them, since the code only uses headers.
- Create a `BOOST_ROOT` environment variable, and set it to Boost libraries's root directory (e.g. C:\libraries\boost_1_78_0).

### Clone

From a `cmd`, as administrator:
```bash
C:\projects> git clone --recurse-submodules https://github.com/rturrado/the_modern_cpp_challenge
```

### Config

There are several options to run CMake from Visual Studio.
- CMake should start automatically, with a `msvc Debug` configuration preset and a `Build windows-msvc-debug` build preset, when opening `the_modern_cpp_challenge` project.
- CMake should also start automatically when choosing a *Configuration* and a *Build Preset* (e.g. `msvc Debug` and `Build windows-msvc-debug`) in the tool bar.
- CMake can be started manually from the *Configure Cache* option in the *Project* menu.
- Finally, CMake can also be started manually from a *Developer Command Prompt* (*Tools* menu, *Command Line* option):
```bash
C:\projects\the_modern_cpp_challenge> cmake --preset windows-msvc-debug
```

### Build

From Visual Studio, once CMake finishes, type CTRL+B or build from *Build > Build All* menu.

Or, from the command line:
```bash
C:\projects\the_modern_cpp_challenge> cmake --build --preset windows-msvc-debug
```

#### Output binaries

All successful builds will generate:
- `the_modern_c++_challenge.exe`: the main binary, a console application that interacts with the user to execute the different problems from the book.
- `the_modern_c++_challenge<MAJOR_VERSION>-<MINOR_VERSION>.lib`: a static library, used, for example, by the test and benchmark binaries.

Builds with the option `-DTHE_MODERN_C++_CHALLENGE_BUILD_TESTS=ON` will also generate:
- `the_modern_c++_challenge_test.exe`: a console application to test the code.

Builds with the option `-DTHE_MODERN_C++_CHALLENGE_BUILD_BENCHMARKS=ON` will also generate:
- `the_modern_c++_challenge_benchmark.exe`: a console application to benchmark the code.

### Run

From Visual Studio: the main binary receives a `res` folder as an argument (a resource directory used by some of the problems). The way to set this parameter from within Visual Studio is via the `.vs\launch.vs.json`, which is not in the repository since it is a user file. The example below shows a possible `launch.vs.json` file. Notice `args` only contains the path of the `res` folder. Notice also that you should provide one configuration entry per output binary (not for the benchmark binary).

```json
{
  "version": "0.2.1",
  "defaults": {},
    "configurations": [
        {
            "type": "default",
            "project": "CMakeLists.txt",
            "projectTarget": "the_modern_c++_challenge.exe (src\\Debug\\the_modern_c++_challenge.exe)",
            "name": "the_modern_c++_challenge.exe (src\\Debug\\the_modern_c++_challenge.exe)",
            "args": [
                "C:\\projects\\the_modern_c++_challenge\\res"
            ]
        }
    ]
}
```

Choose `the_modern_c++_challenge.exe` from *Select Startup Item*, and click the green "play" button.

Or, from the command line:
```bash
C:\projects\the_modern_cpp_challenge> .\out\build\windows-msvc-debug\src\Debug\the_modern_c++_challenge.exe res
```

### Tests

Build with:
```bash
cmake --preset windows-msvc-debug
cmake --build --preset windows-msvc-debug
```

You can run the test executable directly:
```bash
C:\projects\the_modern_cpp_challenge> .\out\build\windows-msvc-debug\test\Debug\the_modern_c++_challenge_test.exe res
```

Or execute the tests via `ctest`:
```bash
C:\projects\the_modern_cpp_challenge> cd out\build\windows-msvc-debug
C:\projects\the_modern_cpp_challenge\out\build\windows-msvc-debug> ctest -C Debug --output-on-failure
```

Alternatively, if you want a less verbose ouptut:
```bash
C:\projects\the_modern_cpp_challenge> .\out\build\windows-msvc-debug\test\Debug\the_modern_c++_challenge_test.exe res --gtest_brief=1
```

Or:
```bash
C:\projects\the_modern_cpp_challenge> cd out\build\windows-msvc-debug
C:\projects\the_modern_cpp_challenge\out\build\windows-msvc-debug> ctest -C Debug --output-on-failure --progress
```

### Benchmarks

Build with:
```bash
C:\projects\the_modern_cpp_challenge> cmake --preset windows-msvc-release
C:\projects\the_modern_cpp_challenge> cmake --build --preset windows-msvc-release
```

And run with:
```bash
C:\projects\the_modern_cpp_challenge> .\out\build\windows-msvc-release\benchmark\Release\the_modern_c++_challenge_benchmark.exe
```

## Dependencies

The Boost libraries have to be downloaded by the user before building the project:

- [boost](www.boost.org/): Boost libraries.

The following libraries are used in this project, but are automatically downloaded and made available via CMake's `FetchContent`:

- [asio](github.com/chriskohlhoff/asio.git): standalone version of the Boost Asio library, used here for networking.
- [benchmark](github.com/google/benchmark.git): Google benchmarking.
- [fmt](github.com/fmtlib/fmt): formatting library with more features than C++ iostreams.
- [googletest](github.com/google/googletest.git): GoogleTest and GoogleMock.
- [nlohmann/json](github.com/nlohmann/json): JSON support.
- [range-v3](github.com/ericniebler/range-v3): range library with many more features than what have been added to C++20.
- [rtc](github.com/rturrado/rtc): some utilities I use in different C++ projects.
- [SQLite3](github.com/algoritnl/sqlite-amalgamation.git): CMake support for the SQLite amalgamation.
- [SQLite Modern CPP](github.com/SqliteModernCpp/sqlite_modern_cpp.git): modern C++ wrapper around SQLite C API.

The same happens with the list below. I'm showing them apart because they are forks of my own. You can check their README files to see how I adapted the original libraries to use them in this project.

- [Crypto++ CMake](github.com/rturrado/cryptopp-cmake.git): C++ library of cryptographic schemes.
- [curlcpp](github.com/rturrado/curlcpp.git): C++ wrapper for curl.
- [FreeImage](github.com/mlomb/FreeImage.git): open source library project for developers who would like to support popular graphics image formats like PNG, BMP, JPEG, TIFF and others.
- [PDF-Writer](github.com/rturrado/PDF-Writer.git): creation, parsing and manipulation of PDF files and streams.
- [perceptualdiff](github.com/rturrado/perceptualdiff.git): program that compares two images using a perceptually based image metric. Used in the tests to compare PNG files. It makes use of the FreeImage library.
- [PNGwriter](github.com/rturrado/pngwriter.git): C+ wrapper for libpng.
- [pugixml](github.com/rturrado/pugixml.git): XML processing.
- [ZipLib](github.com/rturrado/ZipLib.git): ZIP archives support.

Finally, this group of libraries is automatically managed via `vcpkg`:

- [cURL](curl.se): command line tool and library for transferring data with URLs.
- [FreeType](freetype.org): software font engine.
- [libpng](libpng.org): official PNG reference library.
- [zlib](github.com/madler/zlib): general purpose data compression library.


## Notes

- Windows builds with address sanitizer enabled have started to crash since updating to MSVC 14.33.31629.
