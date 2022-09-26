#include "chapter_07_concurrency/problem_061_parallel_transform_algorithm.h"

#include "rtc/timer.h"

#include "benchmark/benchmark.h"
#include "fmt/chrono.h"
#include "fmt/core.h"

#include <algorithm>  // transform
#include <chrono>
#include <execution>  // par
#include <numeric>  // iota
#include <vector>

#undef NDEBUG
#include <cassert>  // assert


auto square = [](int n) { return n * n; };


// Custom benchmark
//
void cb_parallel_transform() {
    using namespace rtc::timer;

    fmt::print("[parallel_transform custom benchmark]\n\n");

    const size_t size{ 10'000'000 };
    std::vector<int> v(size);
    std::iota(std::begin(v), std::end(v), 0);

    fmt::print("square of a std::vector<int>({}):\n", size);
    auto v1{ v };
    auto v2{ v };
    auto v3{ v };
    // std::transform
    {
        auto t{ function_timer<>::duration(
            [&v, &v1]() {
                std::ranges::transform(v, std::begin(v1), square);
            }
        ) };
        fmt::print("\tstd::transform: {}\n", std::chrono::duration<double, std::milli>(t));
    }
    // std::transform(std::execution::par)
    {
        auto t{ function_timer<>::duration(
            [&v, &v2]() {
                std::transform(std::execution::par, std::cbegin(v), std::cend(v), std::begin(v2), square);
            }
        ) };
        assert(v1 == v2);
        fmt::print("\tstd::transform(ex::par): {}\n", std::chrono::duration<double, std::milli>(t));
    }
    // Parallel transform with different thread pool and block sizes
    fmt::print("\tparallel_transform:\n");
    for (size_t thread_pool_size : { 4, 8, 16 }) {
        for (size_t block_size : { 1'000, 10'000, 100'000 }) {
            auto t{ function_timer<>::duration(
                [thread_pool_size, block_size, &v, &v3]() {
                    tmcppc::algorithm::parallel_transform(std::cbegin(v), std::cend(v), std::begin(v3),
                        square, thread_pool_size, block_size);
                }
            ) };
            assert(v1 == v3);
            fmt::print("\t\tthread_pool_size = {:2}, block_size = {:6}: {}\n",
                thread_pool_size, block_size, std::chrono::duration<double, std::milli>(t));
        }
    }

    fmt::print("\n");
}


// Google benchmark
//
static void gb_std_transform(benchmark::State& state, auto transform_algorithm) {
    const size_t size{ 10'000'000 };
    std::vector<int> v(size);
    std::iota(std::begin(v), std::end(v), 0);

    while (state.KeepRunning()) {
        transform_algorithm(std::begin(v), std::end(v), std::begin(v), square);
        benchmark::DoNotOptimize(v.size());
    }
}

static void gb_parallel_transform(benchmark::State& state) {
    const size_t size{ 10'000'000 };
    std::vector<int> v(size);
    std::iota(std::begin(v), std::end(v), 0);
    size_t thread_pool_size{ static_cast<size_t>(state.range(0)) };
    size_t block_size{ static_cast<size_t>(state.range(1)) };

    while (state.KeepRunning()) {
        tmcppc::algorithm::parallel_transform(std::begin(v), std::end(v), std::begin(v), square, thread_pool_size, block_size);
        benchmark::DoNotOptimize(v.size());
    }
}

BENCHMARK_CAPTURE(gb_std_transform, std_transform,
    [](auto input_first, auto input_last, auto output_first, auto unary_op) {
        return std::transform(input_first, input_last, output_first, unary_op);
    }
);
BENCHMARK_CAPTURE(gb_std_transform, std_transform_parallel,
    [](auto input_first, auto input_last, auto output_first, auto unary_op) {
        return std::transform(std::execution::par, input_first, input_last, output_first, unary_op);
    }
);
BENCHMARK(gb_parallel_transform)->ArgsProduct({ {4, 8, 16}, {1'000, 10'000, 100'000} });
