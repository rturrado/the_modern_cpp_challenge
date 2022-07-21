cmake_minimum_required(VERSION 3.21)


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
    #,undefined -fno-omit-frame-pointer
    )
    #set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}" -fsanitize=address,undefined)
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
