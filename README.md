[![main CI](https://github.com/rturrado/the_modern_cpp_challenge/actions/workflows/main_ci.yml/badge.svg)](https://github.com/rturrado/the_modern_cpp_challenge/actions/workflows/main_ci.yml)

# The Modern C++ Challenge

My solutions to the 100 problems of The Modern C++ Challenge, a book by Marius Bancila's (published by Packt).

These exercises were initially implemented as a project within a bigger Visual Studio solution, [Catching up with modern C++](https://github.com/rturrado/CatchingUpWithModernCpp), as a way of practicing _modern C++ (11/14/17/20)_. However, anyone downloading that project would need to:
- Make sure they have installed all the libraries used in the code.
- And update the Visual Studio project properties containing absolute paths to those libraries (e.g., _C/C++ > General > Additional Include Directories, and Linker > Input > Additional Dependencies_).

The goal behind The Modern C++ Challenge project is twofold. On one hand, let users download, build, and execute the code with a minimal effort (ideally without needing to install any library). On the personal side, get some hands-on experience with _CMake_ and other tools of the C++ ecosystem. I've also taken the chance to improve the original code with:
  - _Tests_ (google tests).
  - _Benchmarks_ (google benchmarks).
  - _Continuous integration_ (GitHub actions).

And I plan to better it further by using clang-tidy and sanitizers. Note though that the `main` branch only builds on Windows/msvc. I'm working at the moment on the `unixlike-builds` branch to extend the use of the project to Unix-like systems and clang/gcc compilers. Once that's possible, I should be able to provide a docker with the project and all the software needed to build it and run it.

## Installation

### Requirements

- **Boost libraries**: this project has been tested with version 1.78.0. 
- **Microsoft Visual C++ (MSVC) compiler toolset**.
- **CMake**: required minimum version is 3.14.
- **git**.

Most of the required software can be installed from the [Visual Studio 2022 Installer](https://visualstudio.microsoft.com/thank-you-downloading-visual-studio/?sku=Community&channel=Release&version=VS2022&source=VSLandingPage&cid=2030&passive=false).

- **Microsoft Visual C++ (MSVC) compiler toolset**: *Workloads* tab, *Desktop development with C++* item.
- **CMake**: *Individual components* tab, *Compilers, build tools, and runtimes* section, *C++ CMake tools for Windows* item.
- **git**: *Individual components* tab, *Code tools* section, *Git for Windows* item.

You can download the current version of the **Boost libraries** from https://www.boost.org/users/download/. Notice it's not necessary to build them, since the code only uses headers.

### Clone

From [GitHub](github.com/rturrado/the_modern_cpp_challenge), click the green *Code* button, then *Open with Visual Studio*, choose a destination folder, and *Clone*.

Or, from the command line:
```bash
git clone https://github.com/rturrado/the_modern_cpp_challenge
```

### Build

Create a `BOOST_ROOT` environment variable, and set it to Boost libraries's root directory (e.g. C:\libraries\boost_1_78_0).

From Visual Studio, choose the *Configuration* and the *Build Preset* (e.g. `no-test` and `x64-Release-no-test`). This should start running CMake. If that weren't the case, you can also run CMake from the *Project > Configure Cache* menu. Once CMake finishes, build from *Build > Build All* menu.

Or, from the command line:
```bash
cmake --preset no-test
cmake --build --preset x64-Release-no-test
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

From Visual Studio: the main binary receives a `res` folder as an argument (a resource directory used by some of the problems). The way to set this parameter from within Visual Studio is via the `.vs\launch.vs.json`, which is not in the repository since it is a user file. The example below shows a possible `launch.vs.json` file. Notice `args` only contains the path of the `res` folder. Notice also that you should provide one configuration entry per output binary.

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
./build/NinjaMultiConfig/test/src/Release/the_modern_c++_challenge.exe res
```

### Tests

Build with:
```bash
cmake --preset test
cmake --build --preset x64-Release-test
```

You can run the test executable directly:
```bash
./build/NinjaMultiConfig/test/test/Release/the_modern_c++_challenge_test.exe res
```

Or execute the tests via `ctest`:
```bash
cd build/NinjaMultiConfig/test
ctest -C Release --output-on-failure
```

Alternatively, if you want a less verbose ouptut:
```bash
./build/NinjaMultiConfig/test/test/Release/the_modern_c++_challenge_test.exe res --gtest_brief=1
```

Or:
```bash
cd build/NinjaMultiConfig/test
ctest -C Release --output-on-failure --progress
```

### Benchmarks

Build with:
```bash
cmake --preset benchmark
cmake --build --preset x64-Release-benchmark
```

And run with:
```bash
./build/NinjaMultiConfig/benchmark/benchmark/Release/the_modern_c++_challenge_benchmark.exe res
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
- [SQLite](sqlite.org/2022/sqlite-amalgamation-3380500.zip): an in-process relational database management library. The link points to the SQLite amalgamation, a compact version containing only two files.
- [SQLite Modern CPP](github.com/SqliteModernCpp/sqlite_modern_cpp.git): C++ wrapper for SQLite.

The same happens with the list below. I'm showing them apart because they are forks of my own. You can check their README files to see how I adapted the original libraries to use them in this project.

- [Crypto++](github.com/rturrado/cryptopp-cmake.git): cryptographic functionalities.
- [curlcpp](github.com/rturrado/curlcpp.git): C++ wrapper for curl.
- [PerceptualDiff](github.com/rturrado/perceptualdiff.git): used in the tests to compare PNG files.
- [PDF writer](github.com/rturrado/PDF-Writer.git): creating, parsing and manipulating PDF files and streams.
- [PNG writer](github.com/rturrado/pngwriter.git): C+ wrapper for libpng.
- [pugixml](github.com/rturrado/pugixml.git): XML processing.
- [ZipLib](github.com/rturrado/ZipLib.git): working with ZIP archives.

Finally, this group of libraries is automatically managed via `vcpkg`:

- [curl](curl.se): transferring data over a network.
- [freetype](freetype.org): rendering of fonts.
- [libpng](libpng.org): working with PNG files.
- [zlib](github.com/madler/zlib): general purpose data compression library.


## Notes

- Windows builds with address sanitizer enabled have started to crash since updating to MSVC 14.33.31629.
