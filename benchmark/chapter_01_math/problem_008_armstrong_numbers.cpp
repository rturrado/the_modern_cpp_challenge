#include "chapter_01_math/problem_008_armstrong_numbers.h"

#include "rtc/timer.h"  // function_timer

#include <benchmark/benchmark.h>  // google benchmark
#include <cassert>  // assert
#include <chrono>  // duration, milli
#include <fmt/chrono.h>
#include <fmt/ranges.h>


// Custom benchmark
//
void cb_armstrong_numbers_up_to_a_limit() {
    using namespace rtc::timer;

    fmt::print("[armstrong_numbers_up_to_a_limit custom benchmark]\n\n");
    fmt::print("Calling armstrong_numbers_up_to_a_limit(1000):\n");
    auto t1 = function_timer<>::duration(
        []() {
            for (int i{ 0 }; i < 10'000; ++i) {
                auto ret{ armstrong_numbers_up_to_a_limit_v1(1000) };
                assert(ret.size() == 6);
            }
        });
    fmt::print("\tv1: {}\n", std::chrono::duration<double, std::milli>(t1));

    auto t2 = function_timer<>::duration(
        []() {
            for (int i{ 0 }; i < 10'000; ++i) {
                auto ret{ armstrong_numbers_up_to_a_limit_v2(1000) };
                assert(ret.size() == 6);
            }
        });
    fmt::print("\tv2: {}\n", std::chrono::duration<double, std::milli>(t2));

    auto t3 = function_timer<>::duration(
        []() {
            for (int i{ 0 }; i < 10'000; ++i) {
                auto ret{ armstrong_numbers_up_to_a_limit_v3(1000) };
                assert(ret.size() == 6);
            }
        });
    fmt::print("\tv3: {}\n\n", std::chrono::duration<double, std::milli>(t3));
}


// Google benchmark
//
static void gb_armstrong_numbers_up_to_a_limit_v1(benchmark::State& state) {
    while (state.KeepRunning()) {
        auto ret{ armstrong_numbers_up_to_a_limit_v1(1000) };
        assert(ret.size() == 6);
    }
}

static void gb_armstrong_numbers_up_to_a_limit_v2(benchmark::State& state) {
    while (state.KeepRunning()) {
        auto ret{ armstrong_numbers_up_to_a_limit_v2(1000) };
        assert(ret.size() == 6);
    }
}

static void gb_armstrong_numbers_up_to_a_limit_v3(benchmark::State& state) {
    while (state.KeepRunning()) {
        auto ret{ armstrong_numbers_up_to_a_limit_v3(1000) };
        assert(ret.size() == 6);
    }
}

BENCHMARK(gb_armstrong_numbers_up_to_a_limit_v1);
BENCHMARK(gb_armstrong_numbers_up_to_a_limit_v2);
BENCHMARK(gb_armstrong_numbers_up_to_a_limit_v3);
