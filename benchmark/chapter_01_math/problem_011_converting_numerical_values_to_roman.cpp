#include "chapter_01_math/problem_011_converting_numerical_values_to_roman.h"
#include "chapter_01_math/roman.h"
#include "rtc/timer.h"  // function_timer

#include <benchmark/benchmark.h>  // google benchmark
#include <chrono>  // duration, milli
#include <fmt/ranges.h>


// Custom benchmark
//
void to_roman_custom_benchmark()
{
    using namespace rtc::timer;
    using namespace rtc::date;

    fmt::print("[to_roman custom benchmark]\n\n");
    fmt::print("Calling to_roman() from 0 to 9999:\n");
    auto t1 = function_timer<>::duration(
        []() {
            for (int i{ 0 }; i < 10'000; ++i) {
                for (size_t j : { 99, 999, 1999 }) {
                    to_roman_v1(j);
                }
            }
        });
    fmt::print("\tv1: {} ms\n", std::chrono::duration<double, std::milli>(t1).count());

    auto t2 = function_timer<>::duration(
        []() {
            for (int i{ 0 }; i < 10'000; ++i) {
                for (size_t j : { 99, 999, 1999 }) {
                    to_roman_v2(j);
                }
            }
        });
    fmt::print("\tv2: {} ms\n", std::chrono::duration<double, std::milli>(t2).count());

    auto t3 = function_timer<>::duration(
        []() {
            for (int i{ 0 }; i < 10'000; ++i) {
                for (size_t j : { 99, 999, 1999 }) {
                    to_roman_v3(j);
                }
            }
        });
    fmt::print("\tv3: {} ms\n", std::chrono::duration<double, std::milli>(t3).count());

    auto t4 = function_timer<>::duration(
        []() {
            for (int i{ 0 }; i < 10000; ++i) {
                for (size_t j : { 99, 999, 1999 }) {
                    to_roman_v4(j);
                }
            }
        });
    fmt::print("\tv4: {} ms\n", std::chrono::duration<double, std::milli>(t4).count());
}


// Google benchmark
//
static void bm_to_roman_v1(benchmark::State& state) {
    for (auto _ : state) {
        rtc::date::to_roman_v1(1000);
    }
}

static void bm_to_roman_v2(benchmark::State& state) {
    for (auto _ : state) {
        rtc::date::to_roman_v2(1000);
    }
}

static void bm_to_roman_v3(benchmark::State& state) {
    for (auto _ : state) {
        rtc::date::to_roman_v3(1000);
    }
}

static void bm_to_roman_v4(benchmark::State& state) {
    for (auto _ : state) {
        rtc::date::to_roman_v4(1000);
    }
}

BENCHMARK(bm_to_roman_v1);
BENCHMARK(bm_to_roman_v2);
BENCHMARK(bm_to_roman_v3);
BENCHMARK(bm_to_roman_v4);
