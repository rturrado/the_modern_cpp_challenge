cmake_minimum_required(VERSION 3.20)

project("the_modern_c++_challenge"
    VERSION 1.0.1
    DESCRIPTION "My solutions to the 100 problems of The Modern C++ Challenge, a book by Marius Bancila's (published by Packt)."
    HOMEPAGE_URL https://github.com/rturrado/the_modern_cpp_challenge.git
    LANGUAGES CXX
)

add_subdirectory(src)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()