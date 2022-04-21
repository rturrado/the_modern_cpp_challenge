#include "Chapter7_Concurrency.h"
#include "RtcTimer.h"

#include <algorithm>  // generate_n, iter_swap, sort
#include <future>  // async
#include <iostream>  // cout
#include <random>  // default_random_engine, random_device
#include <vector>

template <typename RandomIt>
RandomIt partition(RandomIt begin, RandomIt end)
{
    auto pivot{ begin };
    auto i{ begin };

    for (auto j{ std::next(begin) }; j < end; ++j)
    {
        if (*j <= *pivot)
        {
            i++;
            std::iter_swap(i, j);
        }
    }
    std::iter_swap(i, pivot);

    return i;
}

template <typename RandomIt>
void quicksort(RandomIt begin, RandomIt end)
{
    if (begin < end)
    {
        auto pivot{ ::partition(begin, end) };
        quicksort(begin, pivot);
        quicksort(pivot + 1, end);
    }
}

template <typename RandomIt>
void parallel_quicksort(RandomIt begin, RandomIt end)
{
    constexpr size_t MINIMUM_PARTITION_SIZE_FOR_PARALLELISING{ 100'000 };
    
    if (begin < end)
    {
        auto pivot{ ::partition(begin, end) };

        if (end - begin <= MINIMUM_PARTITION_SIZE_FOR_PARALLELISING)
        {
            parallel_quicksort(begin, pivot);
            parallel_quicksort(pivot + 1, end);
        }
        else
        {
            auto future1 = std::async(std::launch::async, [&begin, &pivot]() { parallel_quicksort(begin, pivot); });
            auto future2 = std::async(std::launch::async, [&pivot, &end]() { parallel_quicksort(pivot + 1, end); });

            future1.wait();
            future2.wait();
        }
    }
}

// Parallel sort algorithm
//
// Write a parallel version of the sort algorithm
// as defined for problem "57. Sort Algorithm", in "Chapter 6, Algorithms and Data Structures",
// which, given a pair of random access iterators to define its lower and upper bounds,
// sorts the elements of the range using the quicksort algorithm.
// The function should use the comparison operators for comparing the elements of the range.
// The level of parallelism and the way to achieve it is an implementation detail.
void problem_64_main()
{
    std::cout << "Times:\n";
    for (size_t size : { 100'000, 250'000, 500'000 })
    {
        std::cout << "\tVecSize: " << size << "\n";

        std::vector<int> v(size);
        std::generate_n(std::begin(v), size, std::default_random_engine{ std::random_device{}() });

        {
            auto w{ v };
            auto t{ function_timer<>::duration([&w]() { std::sort(std::begin(w), std::end(w)); }) };
            std::cout << "\t\tstd::sort: " << t << "\n";
        }
        {
            auto w{ v };
            auto t{ function_timer<>::duration([&w]() { quicksort(std::begin(w), std::end(w)); }) };
            std::cout << "\t\tquicksort: " << t << "\n";
        }
        {
            auto w{ v };
            auto t{ function_timer<>::duration([&w]() { parallel_quicksort(std::begin(w), std::end(w)); }) };
            std::cout << "\t\tparallel_quicksort: " << t << "\n";
        }
    }
    std::cout << "\n";
}
