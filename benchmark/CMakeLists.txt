# Packages
find_package(Threads REQUIRED)

include(FetchContent)
set(BENCHMARK_ENABLE_TESTING NO)
FetchContent_Declare(googlebenchmark
    GIT_REPOSITORY https://github.com/google/benchmark.git
    GIT_TAG "60b16f11a30146ac825b7d99be0b9887c24b254a"
)
FetchContent_MakeAvailable(googlebenchmark)


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
