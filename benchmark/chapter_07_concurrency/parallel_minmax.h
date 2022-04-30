#pragma once

#include "rtc/timer.h"

#include <algorithm>  // max_element, min_element, shuffle
#include <benchmark/benchmark.h>
#include <cassert>  // assert
#include <chrono>
#include <cstdint>  // int64_t
#include <execution>  // par
#include <fmt/core.h>
#include <numeric>  // iota
#include <ostream>
#include <random>  // mt19937, random_device
#include <string_view>
#include <vector>


// Custom benchmark
//
template <typename T, typename F, typename G, typename H>
void cb_parallel_binary_operation(F&& f, G&& g, H&& h, std::vector<std::string_view>&& string_literals) {
    using namespace rtc::timer;

    assert("Error: wrong number of string literals, " and string_literals.size() == 4);
    auto operation{ string_literals[0] };
    auto type_name{ string_literals[1] };
    auto f_name{ string_literals[2] };
    auto g_name{ string_literals[2] };
    auto h_name{ string_literals[3] };

    const size_t size{ 10'000'000 };
    std::vector<T> v(size);
    std::iota(std::begin(v), std::end(v), -5'000'000);
    std::ranges::shuffle(v, std::mt19937{ std::random_device{}() });

    fmt::print("{} of a std::vector<{}>({}):\n", operation, type_name, size);
    // STL algorithm
    T f_ret{};
    T g_ret{};
    T h_ret{};
    {
        auto t{ function_timer<>::duration(
            [&f, &v, &f_ret]() {
                f_ret = f(std::cbegin(v), std::cend(v));
            }
        ) };
        fmt::print("\t{}, output = {}: {} ms\n", f_name, f_ret, std::chrono::duration<double, std::milli>(t).count());
    }
    // Parallel STL algorithm
    {
        auto t{ function_timer<>::duration(
            [&g, &v, &g_ret]() {
                g_ret = g(std::cbegin(v), std::cend(v));
            }
        ) };
        assert(f_ret == g_ret);
        fmt::print("\t{}(ex::par), output = {}: {} ms\n", g_name, g_ret, std::chrono::duration<double, std::milli>(t).count());
    }
    // Custom parallel function
    fmt::print("\t{}:\n", h_name);
    for (size_t thread_pool_size : { 4, 8, 16 }) {
        for (size_t block_size : { 1'000, 10'000, 100'000 }) {
            auto t{ function_timer<>::duration(
                [&h, &v, thread_pool_size, block_size, &h_ret]() {
                    h_ret = h(std::cbegin(v), std::cend(v), thread_pool_size, block_size);
                }
            ) };
            assert(f_ret == h_ret);
            fmt::print("\t\tthread_pool_size = {:2}, block_size = {:6}, output = {}: {} ms\n",
                thread_pool_size, block_size, h_ret, std::chrono::duration<double, std::milli>(t).count());
        }
    }
    fmt::print("\n");
}


template <typename ParallelMinFunction, typename ParallelMaxFunction>
void cb_parallel_minmax(ParallelMinFunction&& parallel_min, ParallelMaxFunction&& parallel_max) {
    // Min, T = int
    cb_parallel_binary_operation<int>(
        [](auto first, auto last) { return *std::min_element(first, last); },
        [](auto first, auto last) { return *std::min_element(std::execution::par, first, last); },
        [&parallel_min](auto first, auto last, auto thread_pool_size, auto block_size) {
            return parallel_min(first, last, thread_pool_size, block_size); },
        std::vector<std::string_view>{ "min", "int", "std::min_element", "parallel_min" });

    // Max, T = int
    cb_parallel_binary_operation<int>(
        [](auto first, auto last) { return *std::max_element(first, last); },
        [](auto first, auto last) { return *std::max_element(std::execution::par, first, last); },
        [&parallel_max](auto first, auto last, auto thread_pool_size, auto block_size) {
            return parallel_max(first, last, thread_pool_size, block_size); },
        std::vector<std::string_view>{ "max", "int", "std::max_element", "parallel_max" });

    // Min, T = int64_t
    cb_parallel_binary_operation<int64_t>(
        [](auto first, auto last) { return *std::min_element(first, last); },
        [](auto first, auto last) { return *std::min_element(std::execution::par, first, last); },
        [&parallel_min](auto first, auto last, auto thread_pool_size, auto block_size) {
            return parallel_min(first, last, thread_pool_size, block_size); },
        std::vector<std::string_view>{ "min", "int64_t", "std::min_element", "parallel_min" });

    // Max, T = int64_t
    cb_parallel_binary_operation<int64_t>(
        [](auto first, auto last) { return *std::max_element(first, last); },
        [](auto first, auto last) { return *std::max_element(std::execution::par, first, last); },
        [&parallel_max](auto first, auto last, auto thread_pool_size, auto block_size) {
            return parallel_max(first, last, thread_pool_size, block_size); },
        std::vector<std::string_view>{ "max", "int64_t", "std::max_element", "parallel_max" });
}


// Google benchmark
//
inline static void gb_std_minmax_int(benchmark::State& state, auto minmax_algorithm) {
    const size_t size{ 500'000 };
    std::vector<int> v(size);
    std::iota(std::begin(v), std::end(v), -250'000);
    std::ranges::shuffle(v, std::mt19937{ std::random_device{}() });

    while (state.KeepRunning()) {
        benchmark::DoNotOptimize(minmax_algorithm(std::begin(v), std::end(v)));
    }
}

inline static void gb_std_minmax_int64_t(benchmark::State& state, auto minmax_algorithm) {
    const size_t size{ 500'000 };
    std::vector<int64_t> v(size);
    std::iota(std::begin(v), std::end(v), -250'000);
    std::ranges::shuffle(v, std::mt19937{ std::random_device{}() });

    while (state.KeepRunning()) {
        benchmark::DoNotOptimize(minmax_algorithm(std::begin(v), std::end(v)));
    }
}

inline static void gb_parallel_minmax_int(benchmark::State& state, auto minmax_algorithm) {
    const size_t size{ 500'000 };
    std::vector<int> v(size);
    std::iota(std::begin(v), std::end(v), -250'000);
    size_t thread_pool_size{ static_cast<size_t>(state.range(0)) };
    size_t block_size{ static_cast<size_t>(state.range(1)) };
    std::ranges::shuffle(v, std::mt19937{ std::random_device{}() });

    while (state.KeepRunning()) {
        benchmark::DoNotOptimize(minmax_algorithm(std::begin(v), std::end(v), thread_pool_size, block_size));
    }
}

inline static void gb_parallel_minmax_int64_t(benchmark::State& state, auto minmax_algorithm) {
    const size_t size{ 500'000 };
    std::vector<int64_t> v(size);
    std::iota(std::begin(v), std::end(v), -250'000);
    size_t thread_pool_size{ static_cast<size_t>(state.range(0)) };
    size_t block_size{ static_cast<size_t>(state.range(1)) };
    std::ranges::shuffle(v, std::mt19937{ std::random_device{}() });

    while (state.KeepRunning()) {
        benchmark::DoNotOptimize(minmax_algorithm(std::begin(v), std::end(v), thread_pool_size, block_size));
    }
}
