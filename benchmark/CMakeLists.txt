# Packages
include(FetchContent)
set(BENCHMARK_ENABLE_TESTING NO)
FetchContent_Declare(googlebenchmark
    GIT_REPOSITORY https://github.com/google/benchmark.git
    GIT_TAG "60b16f11a30146ac825b7d99be0b9887c24b254a"
)
FetchContent_MakeAvailable(
    googlebenchmark
)
find_package(Threads REQUIRED)


# Subdirectories
add_subdirectory(chapter_01_math)
add_subdirectory(chapter_07_concurrency)


# Benchmark sources
set(benchmark_sources
    ${chapter_01_benchmark_sources}
    ${chapter_07_benchmark_sources}
)


# Benchmark executable
add_executable(${PROJECT_NAME}_benchmark main.cpp benchmark.h ${benchmark_sources})
target_compile_features(${PROJECT_NAME}_benchmark PRIVATE cxx_std_23)
target_link_libraries(${PROJECT_NAME}_benchmark lib_${PROJECT_NAME} benchmark::benchmark Threads::Threads)
if(MSVC)
    target_compile_options(${PROJECT_NAME}_benchmark PRIVATE
        /W3 /WX /w34996
        /D_CONSOLE /DCONSOLE
        /D_UNICODE /DUNICODE
        /diagnostics:column /EHsc /FC /fp:precise /Gd /GS /MP /sdl /utf-8 /Zc:inline
    )
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    target_compile_options(${PROJECT_NAME}_benchmark PRIVATE
        -pedantic-errors -Werror -Wall -Wextra
        -Wl,-z,defs
        -Wno-deprecated
        # -Wconversion -Wsign-conversion -Wno-sign-conversion  # do not sort flags; order matters
    )
endif()
