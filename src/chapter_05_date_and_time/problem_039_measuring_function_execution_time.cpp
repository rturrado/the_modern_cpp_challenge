#include "Chapter5_DateAndTime.h"

#include <algorithm>  // shuffle, sort
#include <cassert>  // assert
#include <chrono>
#include <iostream>  // cout
#include <format>
#include <functional>  // invoke
#include <numeric>  // iota
#include <random>  // mt19937, random_device
#include <utility>  // forward, pair
#include <vector>

template <typename Duration, typename F, typename... Args>
Duration measure_time(F&& f, Args&&... args)
{
    namespace ch = std::chrono;

    ch::steady_clock::time_point start{ ch::steady_clock::now() };
    std::invoke(std::forward<F>(f), std::forward<Args>(args)...);
    ch::steady_clock::time_point end{ ch::steady_clock::now() };

    return ch::duration_cast<Duration>(end - start);
}

void sort_iota_vector(size_t num_elems, size_t num_reps)
{
    assert(num_elems > 0);
    std::vector<int> v(num_elems);
    std::iota(begin(v), end(v), 1);
    auto sort_v = [v]() mutable { std::sort(begin(v), end(v)); assert(v[0] == 1); };
    while (num_reps-- != 0)
    {
        sort_v();
    }
}

void sort_shuffle_vector(size_t num_elems, size_t num_reps)
{
    assert(num_elems > 0);
    std::vector<int> v(num_elems);
    std::iota(begin(v), end(v), 1);
    std::shuffle(begin(v), end(v), std::mt19937{ std::random_device{}() });
    auto sort_v = [v]() mutable { std::sort(begin(v), end(v)); assert(v[0] == 1); };
    while (num_reps-- != 0)
    {
        sort_v();
    }
}

// Measuring function execution time
//
// Write a function that can measure the execution time of a function (with any number of arguments)
// in any required duration (such as seconds, milliseconds, microseconds, and so on).
void problem_39_main()
{
    namespace ch = std::chrono;

    std::cout << "Measuring times...\n";
    using vector_of_elems_and_reps = std::vector<std::pair<size_t, size_t>>;
    for (const auto& [num_elems, num_reps] : vector_of_elems_and_reps{ {1'000'000, 1}, {1000, 1000} })
    {
        auto duration_1{ measure_time<ch::milliseconds>(sort_iota_vector, num_elems, num_reps) };
        auto duration_2{ measure_time<ch::milliseconds>(sort_shuffle_vector, num_elems, num_reps) };

        std::cout << std::format("\tsort_iota_vector({}, {}): {}\n", num_elems, num_reps, duration_1);
        std::cout << std::format("\tsort_shuffle_vector({}, {}): {}\n", num_elems, num_reps, duration_2);

        std::cout << "\n";
    }
}
