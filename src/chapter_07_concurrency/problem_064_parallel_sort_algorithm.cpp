#include "chapter_07_concurrency/problem_064_parallel_sort_algorithm.h"

#include <algorithm>  // shuffle, sort
#include <fmt/ostream.h>
#include <fmt/ranges.h>
#include <iostream>  // cout
#include <numeric>  // iota
#include <random>  // default_random_engine, random_device
#include <vector>


// Parallel sort algorithm
//
// Write a parallel version of the sort algorithm
// as defined for problem "57. Sort Algorithm", in "Chapter 6, Algorithms and Data Structures",
// which, given a pair of random access iterators to define its lower and upper bounds,
// sorts the elements of the range using the quicksort algorithm.
// The function should use the comparison operators for comparing the elements of the range.
// The level of parallelism and the way to achieve it is an implementation detail.
void problem_64_main(std::ostream& os) {
    std::vector<int> v(20);
    std::iota(std::begin(v), std::end(v), -10);
    std::ranges::shuffle(v, std::default_random_engine{ std::random_device{}() });

    fmt::print(os, "v = {}\n\n", v);
    {
        auto w{ v };
        std::ranges::sort(w);
        fmt::print(os, "std::sort(v); v = {}\n", w);
    }
    {
        auto w{ v };
        tmcppc::algorithm::quicksort(std::begin(w), std::end(w));
        fmt::print(os, "quicksort(v); v = {}\n", w);
    }
    {
        auto w{ v };
        tmcppc::algorithm::parallel_quicksort(std::begin(w), std::end(w));
        fmt::print(os, "parallel_quicksort; v = {}\n\n", w);
    }
}
