include(FetchContent)
set(BENCHMARK_ENABLE_TESTING NO)
FetchContent_Declare(googlebenchmark
    GIT_REPOSITORY https://github.com/google/benchmark.git
    GIT_TAG "60b16f11a30146ac825b7d99be0b9887c24b254a"
)
FetchContent_MakeAvailable(googlebenchmark)

add_subdirectory(chapter_01_math)

add_executable(${PROJECT_NAME}_benchmark main.cpp benchmark.h ${chapter_01_benchmark_sources})
target_compile_features(${PROJECT_NAME}_benchmark PRIVATE cxx_std_23)
target_link_libraries(${PROJECT_NAME}_benchmark lib_${PROJECT_NAME} benchmark::benchmark ${CMAKE_THREAD_LIBS_INIT})