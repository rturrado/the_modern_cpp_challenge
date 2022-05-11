#include "chapter_07_concurrency/problem_062_parallel_minmax_with_threads.h"
#include "parallel_minmax.h"

#include <benchmark/benchmark.h>
#include <cstdint>  // int64_t
#include <execution>
#include <fmt/chrono.h>
#include <fmt/core.h>


// Custom benchmark
//
void cb_parallel_minmax_with_threads() {
    fmt::print("[parallel_minmax_with_threads custom benchmark]\n\n");

    cb_parallel_minmax(
        [](auto first, auto last, auto thread_pool_size, auto block_size) {
            return tmcppc::algorithm::thread::parallel_min(first, last, thread_pool_size, block_size);
        },
        [](auto first, auto last, auto thread_pool_size, auto block_size) {
            return tmcppc::algorithm::thread::parallel_max(first, last, thread_pool_size, block_size);
        }
    );
}


// Google benchmark
//
BENCHMARK_CAPTURE(gb_std_minmax_int, std_min_element,
    [](auto first, auto last) { return *std::min_element(first, last); });
BENCHMARK_CAPTURE(gb_std_minmax_int, std_min_element_parallel,
    [](auto first, auto last) { return *std::min_element(std::execution::par, first, last); });
BENCHMARK_CAPTURE(gb_std_minmax_int64_t, std_min_element,
    [](auto first, auto last) { return *std::min_element(first, last); });
BENCHMARK_CAPTURE(gb_std_minmax_int64_t, std_min_element_parallel,
    [](auto first, auto last) { return *std::min_element(std::execution::par, first, last); });
BENCHMARK_CAPTURE(gb_parallel_minmax_int, parallel_min_with_threads_int,
    [](auto first, auto last, auto thread_pool_size, auto block_size) {
        return tmcppc::algorithm::thread::parallel_min(first, last, thread_pool_size, block_size);
    }
)->ArgsProduct({ {4, 8, 16}, {1'000, 10'000, 100'000} });
BENCHMARK_CAPTURE(gb_parallel_minmax_int64_t, parallel_min_with_threads_int64_t,
    [](auto first, auto last, auto thread_pool_size, auto block_size) {
        return tmcppc::algorithm::thread::parallel_min(first, last, thread_pool_size, block_size);
    }
)->ArgsProduct({ { 4, 8, 16 }, { 1'000, 10'000, 100'000 } });
