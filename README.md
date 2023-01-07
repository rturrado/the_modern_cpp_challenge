[![main CI](https://github.com/rturrado/the_modern_cpp_challenge/actions/workflows/main_ci.yml/badge.svg)](https://github.com/rturrado/the_modern_cpp_challenge/actions/workflows/main_ci.yml)
[![unixlike-builds CI](https://github.com/rturrado/the_modern_cpp_challenge/actions/workflows/unixlike-builds_ci.yml/badge.svg)](https://github.com/rturrado/the_modern_cpp_challenge/actions/workflows/unixlike-builds_ci.yml)
[![codecov](https://codecov.io/github/rturrado/the_modern_cpp_challenge/branch/unixlike-builds/graph/badge.svg?token=GAF6OX0ZVE)](https://codecov.io/github/rturrado/the_modern_cpp_challenge)

# The Modern C++ Challenge

My solutions to the 100 problems of The Modern C++ Challenge, a book by Marius Bancila (published by Packt).

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
- _Compiler caching_ (ccache).

## Branch status

- The `main` branch only builds on Windows/msvc.
- The `unixlike-builds` branch only builds on Unix-like systems.
- `main` release `v2.0.0` and `unixlike-builds` release `v1.0.0` provide the same functionality.

Since the `unixlike-builds` branch uses gcc, which doesn't have support yet for all the C++20 features (especially the `<format>` library), a few problems are implemented differently in that branch. Basically, the date and time problems use Howard Hinnant's `<date>` library instead of the `<format>` library. This should be the only difference between `main` release `v2.0.0` `unixlike-builds` release `v1.0.0`.

Once gcc will have support for all the C++20 features, the `main` branch should be suitable to be used in Unix-like systems, and the `unixlike-builds` branch should be dropped.

The instructions below refer to Unix-like/gcc.

## Installation

### Requirements

- **Boost libraries**: this project has been tested with version 1.78.0.
- **CMake**: required minimum version is 3.22.
- **ninja**.
- **ccache**.
- **gcc**: this project has been tested with version 12.
- **git**.
- **pkg-config**.
- **curl**.
- **tar**.
- **zip**.
- **unzip**.
- **wget**.

From a `terminal`, as administrator:
```bash
$> sudo apt-get -qq update
$> sudo apt-get -qq upgrade
$> sudo apt-get -qq -y install \
       ccache \
       cmake \
       curl \
       g++-12 \
       gcc-12 \
       git \
       ninja-build \
       pkg-config \
       tar \
       unzip \
       wget \
       zip
$> sudo update-alternatives \
       --install /usr/bin/gcc gcc /usr/bin/gcc-12 100 \
       --slave /usr/bin/g++ g++ /usr/bin/g++-12 \
       --slave /usr/bin/gcov gcov /usr/bin/gcov-12
```

You can download the current version of the **Boost libraries** from https://www.boost.org/users/download/.
- Notice it's not necessary to build them, since the code only uses headers.
- Create a `BOOST_ROOT` environment variable, and set it to Boost libraries's root directory (e.g. /libraries/boost_1_78_0).

From a `terminal`:
```bash
$> mkdir /libraries
$> cd /libraries
$> wget https://boostorg.jfrog.io/artifactory/main/release/1.78.0/source/boost_1_78_0.tar.gz
$> tar -xvzf boost_1_78_0.tar.gz
$> rm -fr boost_1_78_0.tar.gz
$> export BOOST_ROOT=/libraries/boost_1_78_0
```

### Clone

From a `terminal`:
```bash
~/projects> git config core.symlinks true
~/projects> git clone --recurse-submodules https://github.com/rturrado/the_modern_cpp_challenge
```

### Config

From a `terminal`:
```bash
~/projects/the_modern_cpp_challenge> cmake --preset unixlike-gcc-debug-tests
```

### Build

From a `terminal`:
```bash
~/projects/the_modern_cpp_challenge> cmake --build --preset unixlike-gcc-debug-tests
```

#### Build presets

The following build presets are available (the configuration presets have the same name):
- Debug:
    - **unixlike-gcc-debug-tests**: *tests* enabled.
    - **unixlike-gcc-debug-github**: *tests*, *ccache*, and *code coverage* enabled. This is the Debug preset used in GitHub Actions.
- Release:
    - **unixlike-gcc-release-benchmarks**: *benchmarks* enabled.
    - **unixlike-gcc-release-tests**: *tests* enabled.
    - **unixlike-gcc-release-github**: *benchmarks* and *ccache* enabled. This is the Release preset used in GitHub Actions.

#### Output binaries

All successful builds will generate:
- `the_modern_c++_challenge`: the main binary, a console application that interacts with the user to execute the different problems from the book.
- `the_modern_c++_challenge-<MAJOR_VERSION>_<MINOR_VERSION>.lib`: a static library, used, for example, by the test and benchmark binaries.

Builds with the option `-DTHE_MODERN_C++_CHALLENGE_BUILD_TESTS=ON` (*debug* build presets) will also generate:
- `the_modern_c++_challenge_test`: a console application to test the code.

Builds with the option `-DTHE_MODERN_C++_CHALLENGE_BUILD_BENCHMARKS=ON` (*release-benchmarks* and *release-github* build presets) will also generate:
- `the_modern_c++_challenge_benchmark`: a console application to benchmark the code.

### Run

From a `terminal`:
```bash
~/projects/the_modern_cpp_challenge> ./out/build/unixlike-gcc-debug-tests/src/Debug/the_modern_c++_challenge res
```

### Tests

Build with:
```bash
~/projects/the_modern_cpp_challenge> cmake --preset unixlike-gcc-debug-tests
~/projects/the_modern_cpp_challenge> cmake --build --preset unixlike-gcc-debug-tests
```

You can run the test executable directly:
```bash
~/projects/the_modern_cpp_challenge> ./out/build/unixlike-gcc-debug-tests/test/Debug/the_modern_c++_challenge_test res
```

Or execute the tests via `ctest`:
```bash
~/projects/the_modern_cpp_challenge/out/build/unixlike-gcc-debug-tests> ctest -C Debug --output-on-failure
```

Alternatively, if you want a less verbose ouptut:
```bash
~/projects/the_modern_cpp_challenge> ./out/build/unixlike-gcc-debug-tests/test/Debug/the_modern_c++_challenge_test res --gtest_brief=1
```

Or:
```bash
~/projects/the_modern_cpp_challenge/out/build/unixlike-gcc-debug-tests> ctest -C Debug --output-on-failure --progress
```

### Benchmarks

Build with:
```bash
~/projects/the_modern_cpp_challenge> cmake --preset unixlike-gcc-release-benchmarks
~/projects/the_modern_cpp_challenge> cmake --build --preset unixlike-gcc-release-benchmarks
```

And run with:
```bash
~/projects/the_modern_cpp_challenge> ./out/build/unixlike-gcc-release-benchmarks/benchmark/Release/the_modern_c++_challenge_benchmark
```

## Docker

There is a `rturrado/tmcppc-binaries` docker, based on an `ubuntu-22.04` image, with the following content:
- `/tmcppc` folder.
  - Dockerfile: the Dockerfile that was used when building the docker.
  - `res` folder: the resource directory.
  - `the_modern_c++_challenge`: the main executable.
  - `the_modern_c++_challenge_test`: the test executable.
  - `the_modern_c++_challenge_benchmark`: the benchmark executable.
  - `libFreeImage.so`: a shared library needed by the test executable.

All of the binaries are release builds.

A new version of the docker is pushed for every new `unixlike-builds-v<VERSION>` tag.

### Requirements

- **dockerhub account**: https://hub.docker.com/.
- **docker**.

From a `terminal`, as administrator:
```bash
$> sudo apt-get -qq update
$> sudo apt-get -qq upgrade
$> sudo apt-get -qq -y install docker
```

### Run

From a `terminal`:

```bash
$> docker login
# Enter username and password
$> docker pull rturrado/tmcppc-binaries
# To download the latest version of the docker
# Otherwise, indicate a version. For example: docker pull rturrado/tmcppc-binaries:unixlike-builds-v1.2.0 
$> docker run -it rturrado/tmcppc-binaries
# To create a container and run it
docker $ /tmcppc> ./the_modern_c++_challenge res
# To run the main executable
```

## Dependencies

The Boost libraries have to be downloaded by the user before building the project:

- [boost](www.boost.org/): Boost libraries.

The following libraries are used in this project, but are automatically downloaded and made available via CMake's `FetchContent`:

- [asio](github.com/chriskohlhoff/asio.git): standalone version of the Boost Asio library, used here for networking.
- [benchmark](github.com/google/benchmark.git): Google benchmarking.
- [date](github.com/HowardHinnant/date.git): a date and time library based on the C++11/14/17 <chrono> header.
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

- `res/sample_folder/sample_subfolder` is a symbolic link to the `res/sample_subfolder` directory. If you experience failures in some tests that access `sample_subfolder`, it may happen that the symbolic link wasn't correctly created after a `git` operation. In that case, you may need to tell `git` to enable the use of symbolic links, and then update your local checkout. You can do that by running the commands below:

  ```bash
  ~/projects/the_modern_cpp_challenge> git config core.symlinks true
  ~/projects/the_modern_cpp_challenge> git reset --hard
  ```
