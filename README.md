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
- _Static analysis_ (CLion's Inspect Code).
- _Memory error detection_ (address sanitizer).
- _Continuous integration_ (GitHub actions).
- _Code coverage_ (gcov).
- _Compiler caching_ (sccache).

## Branch status

- The `main` branch only builds on Windows/msvc.
- The `unixlike-builds` branch only builds on Unix-like systems.
- `main` release `v2.0.0` and `unixlike-builds` release `v1.0.0` provide the same functionality.

Since the `unixlike-builds` branch uses gcc, which doesn't have support yet for all the C++20 features (especially the `<format>` library), a few problems are implemented differently in that branch. Basically, the date and time problems use Howard Hinnant's `<date>` library instead of the `<format>` library. This should be the only difference between `main` release `v2.0.0` `unixlike-builds` release `v1.0.0`.

Once gcc will have support for all the C++20 features, the `main` branch should be suitable to be used in Unix-like systems, and the `unixlike-builds` branch should be dropped.

The instructions below refer to Windows/msvc.

## Installation

### Requirements

- **Boost libraries**: this project has been tested with version 1.78.0. 
- **Microsoft Visual C++ (MSVC) compiler toolset**.
- **CMake**: required minimum version is 3.22.
- **git**.
- **sccache**: only if you are going to use a *\*ccache* or *\*github* build preset.

Most of the required software can be installed from the [Visual Studio 2022 Installer](https://visualstudio.microsoft.com/thank-you-downloading-visual-studio/?sku=Community&channel=Release&version=VS2022&source=VSLandingPage&cid=2030&passive=false).

- **Microsoft Visual C++ (MSVC) compiler toolset**: *Workloads* tab, *Desktop development with C++* item.
- **CMake**: *Individual components* tab, *Compilers, build tools, and runtimes* section, *C++ CMake tools for Windows* item.
- **git**: *Individual components* tab, *Code tools* section, *Git for Windows* item.

You can download the current version of the **Boost libraries** from https://www.boost.org/users/download/.
- Notice it's not necessary to build them, since the code only uses headers.
- Create a `BOOST_ROOT` environment variable, and set it to Boost libraries's root directory (e.g. C:\libraries\boost_1_78_0).

Should you want to make use of **sccache** (https://github.com/mozilla/sccache), you could install it via *scoop*.

From a `PowerShell` terminal, as non-administrator:
```bash
PS C:\> Set-ExecutionPolicy RemoteSigned -Scope CurrentUser
PS C:\> irm get.scoop.sh | iex
PS C:\> scoop install sccache
```

### Clone

From a `cmd`:
```bash
C:\projects> git config core.symlinks true
C:\projects> git clone --recurse-submodules https://github.com/rturrado/the_modern_cpp_challenge
```

### Config

There are several options to run CMake from Visual Studio.
- CMake should start automatically when choosing a *Configuration* and a *Build Preset* (e.g. `msvc Debug (tests)` and `Build windows-msvc-debug (tests)`) in the tool bar.
- CMake can be started manually from the *Configure Cache* option in the *Project* menu.
- Finally, CMake can also be started manually from a *Developer Command Prompt* (*Tools* menu, *Command Line* option):
```bash
C:\projects\the_modern_cpp_challenge> cmake --preset windows-msvc-debug-tests
```

### Build

From Visual Studio, once CMake finishes, type CTRL+B or build from *Build > Build All* menu.

Or, from the command line:
```bash
C:\projects\the_modern_cpp_challenge> cmake --build --preset windows-msvc-debug-tests
```

#### Build presets

The following build presets are available (the configuration presets have the same name):
- Debug:
  - **windows-msvc-debug-tests**: *tests* enabled.
  - **windows-msvc-debug-github**: *tests* and *ccache* enabled. This is the Debug preset used in GitHub Actions.
- Release:
  - **windows-msvc-release-benchmarks**: *benchmarks* enabled.
  - **windows-msvc-release-tests**: *tests* enabled.
  - **windows-msvc-release-github**: *benchmarks* and *ccache* enabled. This is the Release preset used in GitHub Actions.

#### Output binaries

All successful builds will generate:
- `the_modern_c++_challenge.exe`: the main binary, a console application that interacts with the user to execute the different problems from the book.
- `the_modern_c++_challenge-<MAJOR_VERSION>_<MINOR_VERSION>.lib`: a static library, used, for example, by the test and benchmark binaries.

Builds with the option `-DTHE_MODERN_C++_CHALLENGE_BUILD_TESTS=ON` (*debug* build presets) will also generate:
- `the_modern_c++_challenge_test.exe`: a console application to test the code.

Builds with the option `-DTHE_MODERN_C++_CHALLENGE_BUILD_BENCHMARKS=ON` (*release-benchmarks* and *release-github* build presets) will also generate:
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
C:\projects\the_modern_cpp_challenge> .\out\build\windows-msvc-debug-tests\src\Debug\the_modern_c++_challenge.exe res
```

### Tests

Build with:
```bash
C:\projects\the_modern_cpp_challenge> cmake --preset windows-msvc-debug-tests
C:\projects\the_modern_cpp_challenge> cmake --build --preset windows-msvc-debug-tests
```

You can run the test executable directly:
```bash
C:\projects\the_modern_cpp_challenge> .\out\build\windows-msvc-debug-tests\test\Debug\the_modern_c++_challenge_test.exe res
```

Or execute the tests via `ctest`:
```bash
C:\projects\the_modern_cpp_challenge\out\build\windows-msvc-debug-tests> ctest -C Debug --output-on-failure
```

Alternatively, if you want a less verbose ouptut:
```bash
C:\projects\the_modern_cpp_challenge> .\out\build\windows-msvc-debug-tests\test\Debug\the_modern_c++_challenge_test.exe res --gtest_brief=1
```

Or:
```bash
C:\projects\the_modern_cpp_challenge\out\build\windows-msvc-debug-tests> ctest -C Debug --output-on-failure --progress
```

### Benchmarks

Build with:
```bash
C:\projects\the_modern_cpp_challenge> cmake --preset windows-msvc-release-benchmarks
C:\projects\the_modern_cpp_challenge> cmake --build --preset windows-msvc-release-benchmarks
```

And run with:
```bash
C:\projects\the_modern_cpp_challenge> .\out\build\windows-msvc-release-benchmarks\benchmark\Release\the_modern_c++_challenge_benchmark.exe
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
- `res\sample_folder\sample_subfolder` is a symbolic link to the `res\sample_subfolder` directory. If you experience failures in some tests that access `sample_subfolder`, it may happen that the symbolic link wasn't correctly created after a `git` operation. In that case, you may need to tell `git` to enable the use of symbolic links, and then update your local checkout. You can do that by running the commands below:

  ```bash
  C:\projects\the_modern_cpp_challenge> git config core.symlinks true
  C:\projects\the_modern_cpp_challenge> git reset --hard
  ```
