cmake_minimum_required(VERSION 3.22)


# CMake policies
if (POLICY CMP0102)
    cmake_policy(SET CMP0102 NEW)
endif()
if (POLICY CMP0126)
    cmake_policy(SET CMP0126 NEW)
endif()
cmake_policy(SET CMP0128 NEW)
cmake_policy(SET CMP0135 NEW)


set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
    CACHE STRING "Vcpkg toolchain file"
)


project("the_modern_c++_challenge"
    VERSION 1.1
    DESCRIPTION "My solutions to the 100 problems of The Modern C++ Challenge, a book by Marius Bancila's (published by Packt)."
    HOMEPAGE_URL https://github.com/rturrado/the_modern_cpp_challenge.git
    LANGUAGES C CXX
)


# Address sanitizer
if(ASAN_ENABLED)
    string(REGEX REPLACE "/RTC(su|[1su])" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    message(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}\n")
    add_compile_options(-fsanitize=address
        # This may be gcc-only
        #-fsanitize=address,undefined -fno-omit-frame-pointer
    )
    # This may be gcc-only
    #add_link_options(-fsanitize=address
        #-fsanitize=address,undefined
    #)
endif()


# Subdirectories
# src, test, and benchmark
add_subdirectory(src)

if(THE_MODERN_C++_CHALLENGE_BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()

if(THE_MODERN_C++_CHALLENGE_BUILD_BENCHMARKS)
    add_subdirectory(benchmark)
endif()
