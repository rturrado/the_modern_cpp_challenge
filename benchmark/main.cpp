#include "benchmark.h"  // custom benchmark

#include <benchmark/benchmark.h>  // google benchmark
#include <fmt/core.h>


void run_custom_benchmarks()
{
    cb_armstrong_numbers_up_to_a_limit();  // problem 8
    cb_to_roman();  // problem 11
    cb_get_longest_collatz_sequence();  // problem 12
    cb_parallel_transform();  // problem 61
    cb_parallel_minmax_with_threads();  // problem 62
    cb_parallel_minmax_with_async();  // problem 63
    cb_sort_algorithm();  // problem 64
}


void run_google_benchmarks()
{
    fmt::print("[google benchmark]\n\n");
    ::benchmark::RunSpecifiedBenchmarks();
}


int main()
{
    run_custom_benchmarks();
    fmt::print("\n");
    run_google_benchmarks();
}
