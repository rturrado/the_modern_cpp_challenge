#include "chapter_01_math/problem_012_longest_collatz_sequence.h"

#include "rtc/timer.h"  // function_timer

#include <benchmark/benchmark.h>  // google benchmark
#include <chrono>  // duration, milli
#include <fmt/chrono.h>
#include <fmt/ranges.h>


constinit const size_t limit{ 1'000'000 };

// Custom benchmark
//
void cb_get_longest_collatz_sequence() {
    using namespace rtc::timer;

    fmt::print("[get_longest_collatz_sequence custom benchmark]\n\n");
    fmt::print("Calling get_longest_collatz_sequence({}):\n", limit);
    auto t1 = function_timer<>::duration(
        []() {
            get_longest_collatz_sequence_v1(limit);
        });
    fmt::print("\tv1: {}\n", std::chrono::duration<double, std::milli>(t1));

    auto t2 = function_timer<>::duration(
        []() {
            get_longest_collatz_sequence_v2(limit);
        });
    fmt::print("\tv2: {}\n\n", std::chrono::duration<double, std::milli>(t2));
}


// Google benchmark
//
static void gb_get_longest_collatz_sequence_v1(benchmark::State& state) {
    while (state.KeepRunning()) {
        get_longest_collatz_sequence_v1(limit);
    }
}

static void gb_get_longest_collatz_sequence_v2(benchmark::State& state) {
    while (state.KeepRunning()) {
        get_longest_collatz_sequence_v2(limit);
    }
}

BENCHMARK(gb_get_longest_collatz_sequence_v1);
BENCHMARK(gb_get_longest_collatz_sequence_v2);
