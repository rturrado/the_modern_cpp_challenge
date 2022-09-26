#include "chapter_07_concurrency/quicksort.h"

#include "rtc/timer.h"  // function_timer

#include "benchmark/benchmark.h"  // google benchmark
#include "fmt/chrono.h"
#include "fmt/ranges.h"

#include <algorithm>  // shuffle, sort
#include <chrono>  // duration, milli
#include <numeric>  // iota
#include <random>  // default_random_engine, random_device
#include <vector>


// Custom benchmark
//
void cb_sort_algorithm() {
    using namespace rtc::timer;

    fmt::print("[sort_algorithm custom benchmark]\n\n");
    for (size_t size : { 100'000, 250'000, 500'000 }) {
        std::vector<int> v(size);
        std::iota(std::begin(v), std::end(v), 0);
        std::ranges::shuffle(v, std::default_random_engine{ std::random_device{}() });

        fmt::print("Vector size: {}\n", size);
        {
            auto w{ v };
            auto t{ function_timer<>::duration(
                [&w]() {
                    std::ranges::sort(w);
                })
            };
            fmt::print("\tstd::sort: {}\n", std::chrono::duration<double, std::milli>(t));
        }
        {
            auto w{ v };
            auto t{ function_timer<>::duration(
                [&w]() {
                    tmcppc::algorithm::quicksort(std::begin(w), std::end(w));
                })
            };
            fmt::print("\tquicksort: {}\n", std::chrono::duration<double, std::milli>(t));
        }
        {
            auto w{ v };
            auto t{ function_timer<>::duration(
                [&w]() {
                    tmcppc::algorithm::parallel_quicksort(std::begin(w), std::end(w));
                })
            };
            fmt::print("\tparallel_quicksort: {}\n", std::chrono::duration<double, std::milli>(t));
        }
    }
}


// Google benchmark
//
static void gb_sort_algorithm(benchmark::State& state, auto sort_algorithm) {
    std::vector<int> v(state.range(0));
    std::iota(std::begin(v), std::end(v), 0);
    std::ranges::shuffle(v, std::default_random_engine{ std::random_device{}() });

    while (state.KeepRunning()) {
        state.PauseTiming();
        auto w{ v };
        state.ResumeTiming();
        sort_algorithm(std::begin(w), std::end(w));
        benchmark::DoNotOptimize(w.size());
    }
}

BENCHMARK_CAPTURE(gb_sort_algorithm, std::sort, [](auto first, auto last) { std::sort(first, last); })
    ->Arg(100'000)
    ->Arg(250'000)
    ->Arg(500'000);
BENCHMARK_CAPTURE(gb_sort_algorithm, quicksort, [](auto first, auto last) { tmcppc::algorithm::quicksort(first, last); })
    ->Arg(100'000)
    ->Arg(250'000)
    ->Arg(500'000);
BENCHMARK_CAPTURE(gb_sort_algorithm, parallel_quicksort, [](auto first, auto last) { tmcppc::algorithm::parallel_quicksort(first, last); })
    ->Arg(100'000)
    ->Arg(250'000)
    ->Arg(500'000);
