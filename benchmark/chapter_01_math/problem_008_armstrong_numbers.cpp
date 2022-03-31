#include "chapter_01_math/problem_008_armstrong_numbers.h"
#include "rtc/timer.h"  // function_timer

#include <benchmark/benchmark.h>
#include <chrono>  // duration, milli
#include <fmt/ranges.h>


// Custom benchmark
//
void print_armstrong_numbers_up_to_a_limit_custom_benchmark()
{
    using namespace rtc::timer;

    fmt::print("print_armstrong_numbers_up_to_a_limit_custom_benchmark():\n---\n");
    fmt::print("Calling print_armstrong_numbers_up_to_a_limit(1000):\n");
    auto t1 = function_timer<>::duration(
        []() {
            for (int i = 0; i < 10000; ++i) {
                print_armstrong_numbers_up_to_a_limit_v1(1000, false);
            }
        });
    fmt::print("\tv1: {} ms\n", std::chrono::duration<double, std::milli>(t1).count());

    auto t2 = function_timer<>::duration(
        []() {
            for (int i = 0; i < 10000; ++i) {
                print_armstrong_numbers_up_to_a_limit_v2(1000, false);
            }
        });
    fmt::print("\tv2: {} ms\n", std::chrono::duration<double, std::milli>(t2).count());

    auto t3 = function_timer<>::duration(
        []() {
            for (int i = 0; i < 10000; ++i) {
                print_armstrong_numbers_up_to_a_limit_v3(1000, false);
            }
        });
    fmt::print("\tv3: {} ms\n\n", std::chrono::duration<double, std::milli>(t3).count());
}


// Google benchmark
//
static void bm_print_armstrong_numbers_up_to_a_limit_v1(benchmark::State& state) {
    for (auto _ : state) {
        print_armstrong_numbers_up_to_a_limit_v1(1000, false);
    }
}

static void bm_print_armstrong_numbers_up_to_a_limit_v2(benchmark::State& state) {
    for (auto _ : state) {
        print_armstrong_numbers_up_to_a_limit_v2(1000, false);
    }
}

static void bm_print_armstrong_numbers_up_to_a_limit_v3(benchmark::State& state) {
    for (auto _ : state) {
        print_armstrong_numbers_up_to_a_limit_v3(1000, false);
    }
}

BENCHMARK(bm_print_armstrong_numbers_up_to_a_limit_v1);
BENCHMARK(bm_print_armstrong_numbers_up_to_a_limit_v2);
BENCHMARK(bm_print_armstrong_numbers_up_to_a_limit_v3);

void print_armstrong_numbers_up_to_a_limit_google_benchmark()
{
    fmt::print("print_armstrong_numbers_up_to_a_limit_google_benchmark():\n---\n");
    ::benchmark::RunSpecifiedBenchmarks();
}
