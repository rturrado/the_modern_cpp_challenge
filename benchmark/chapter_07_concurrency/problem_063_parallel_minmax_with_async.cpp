#include "chapter_07_concurrency/problem_063_parallel_minmax_with_async.h"
#include "parallel_minmax.h"

#include <benchmark/benchmark.h>
#include <cstdint>  // int64_t
#include <execution>
#include <fmt/core.h>

using namespace tmcppc::parallel_minmax::async;


// Custom benchmark
//
void cb_parallel_minmax_with_async() {
    fmt::print("[parallel_minmax_with_async custom benchmark]\n\n");

    cb_parallel_minmax(
        [](auto first, auto last, auto thread_pool_size, auto block_size) {
            return parallel_min(first, last, thread_pool_size, block_size);
        },
        [](auto first, auto last, auto thread_pool_size, auto block_size) {
            return parallel_max(first, last, thread_pool_size, block_size);
        }
    );
}


// Google benchmark
//
BENCHMARK_CAPTURE(gb_parallel_minmax_int, parallel_min_with_async_int,
    [](auto first, auto last, auto thread_pool_size, auto block_size) {
        return parallel_min(first, last, thread_pool_size, block_size);
    }
)->ArgsProduct({ {4, 8, 16}, {1'000, 10'000, 100'000} });
BENCHMARK_CAPTURE(gb_parallel_minmax_int64_t, parallel_min_with_async_int64_t,
    [](auto first, auto last, auto thread_pool_size, auto block_size) {
        return parallel_min(first, last, thread_pool_size, block_size);
    }
)->ArgsProduct({ { 4, 8, 16 }, { 1'000, 10'000, 100'000 } });
