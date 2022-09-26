#pragma once

#include "fmt/ostream.h"
#include "fmt/ranges.h"

#include <algorithm>  // max_element, min_element, shuffle
#include <execution>
#include <numeric>  // iota
#include <ostream>
#include <random>  // default_random_engine, random_device
#include <ranges>
#include <vector>


template <typename ParallelMinFunction, typename ParallelMaxFunction>
void parallel_minmax(std::ostream& os, ParallelMinFunction&& parallel_min, ParallelMaxFunction&& parallel_max) {
    std::vector<int> v(20);
    std::iota(std::begin(v), std::end(v), -10);
    std::ranges::shuffle(v, std::default_random_engine{ std::random_device{}() });

    fmt::print(os, "v = {}\n\n", v);

    fmt::print(os, "std::min_element(v) = {}\n",
        *std::ranges::min_element(v));
    fmt::print(os, "std::min_element(std::execution::par, v) = {}\n",
        *std::min_element(std::execution::par, std::cbegin(v), std::cend(v)));
    fmt::print(os, "parallel_min (using threads) = {}\n\n",
        *parallel_min(v));

    fmt::print(os, "std::max_element(v) = {}\n",
        *std::ranges::max_element(v));
    fmt::print(os, "std::max_element(std::execution::par, v) = {}\n",
        *std::max_element(std::execution::par, std::cbegin(v), std::cend(v)));
    fmt::print(os, "parallel_max (using threads) = {}\n\n",
        *parallel_max(v));
}
