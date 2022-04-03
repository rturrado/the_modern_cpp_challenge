#include "benchmark.h"  // custom benchmark

#include <benchmark/benchmark.h>  // google benchmark
#include <fmt/core.h>


void run_custom_benchmark()
{
    cb_armstrong_numbers_up_to_a_limit();
    cb_to_roman();
    cb_get_longest_collatz_sequence();
}


void run_google_benchmark()
{
    fmt::print("[google benchmark]\n\n");
    ::benchmark::RunSpecifiedBenchmarks();
}


int main()
{
    run_custom_benchmark();
    fmt::print("\n");
    run_google_benchmark();
}
