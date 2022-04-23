#include "chapter_07_concurrency/problem_063_parallel_minmax_with_async.h"
#include "rtc/timer.h"

#include <algorithm>  // max_element, min_element, shuffle, transform
#include <cassert>  // assert
#include <cstdint>  // int64_t
#include <execution>  // par
#include <format>
#include <future>  // async
#include <iostream>  // cout
#include <iterator>  // iterator_traits
#include <numeric>  // iota
#include <random>  // mt19937, random_device
#include <semaphore>  // counting_semaphore
#include <string_view>
#include <vector>

static const size_t THREAD_POOL_SIZE_DEFAULT{ std::thread::hardware_concurrency() };
static const size_t THREAD_POOL_SIZE_MAX{ static_cast<size_t>(std::thread::hardware_concurrency()) * 2 };
static const size_t BLOCK_SIZE_DEFAULT{ 10'000 };
static const size_t BLOCK_SIZE_MIN{ 100 };

template <typename ForwardIt, typename BinaryOperation>
auto parallel_binary_operation(ForwardIt first, ForwardIt last, BinaryOperation&& binary_op,
    size_t thread_pool_size = THREAD_POOL_SIZE_DEFAULT, size_t block_size = BLOCK_SIZE_DEFAULT)
{
    using T = typename std::iterator_traits<ForwardIt>::value_type;

    size_t size{ static_cast<size_t>(std::distance(first, last)) };
    thread_pool_size = std::min(thread_pool_size, THREAD_POOL_SIZE_MAX);
    block_size = std::max(block_size, BLOCK_SIZE_MIN);

    std::counting_semaphore task_slots(thread_pool_size);
    size_t num_blocks{ (size / block_size) + (size % block_size) };
    auto futures{ std::vector<std::future<void>>(num_blocks) };
    auto block_results{ std::vector<T>(num_blocks) };

    // Launch one task per block
    // We can run thread_pool_size tasks in parallel
    // If all task slots are busy, we have to wait for a task to finish
    for (size_t i{ 0 }; i < num_blocks; ++i)
    {
        auto cbegin_it{ first + i * block_size };
        auto cend_it{ first + std::min(size, (i + 1) * block_size) };

        // Wait for a task slot to be free
        task_slots.acquire();

        futures[i] = std::async(
            std::launch::async,
            [&binary_op, cbegin_it, cend_it, &block_result=block_results[i], &task_slots]() {
                // Execute task, and set the result for the block
                block_result = binary_op(cbegin_it, cend_it);

                // Release the task slot
                task_slots.release();
            }
        );
    }

    // Wait for all the tasks to finish
    for (auto& future : futures) { future.get(); };

    // Apply the binary operation to the container with the block results
    return binary_op(std::begin(block_results), std::end(block_results));
}

template <typename ForwardIt>
auto parallel_min(ForwardIt first, ForwardIt last,
    size_t thread_pool_size = THREAD_POOL_SIZE_DEFAULT, size_t block_size = BLOCK_SIZE_DEFAULT)
{
    return parallel_binary_operation(first, last,
        [](auto first, auto last) { return *std::min_element(first, last); },
        thread_pool_size, block_size);
}

template <typename ForwardIt>
auto parallel_max(ForwardIt first, ForwardIt last,
    size_t thread_pool_size = THREAD_POOL_SIZE_DEFAULT, size_t block_size = BLOCK_SIZE_DEFAULT)
{
    return parallel_binary_operation(first, last,
        [](auto first, auto last) { return *std::max_element(first, last); },
        thread_pool_size, block_size);
}

template <typename T, typename F, typename G, typename H>
void test_parallel_binary_operation(F&& f, G&& g, H&& h, std::vector<std::string_view>&& string_literals)
{
    assert("Error: wrong number of string literals, " and string_literals.size() == 3);
    auto test_title{ string_literals[0] };
    auto f_name{ string_literals[1] };
    auto g_name{ string_literals[1] };
    auto h_name{ string_literals[2] };

    std::vector<T> v(10'000'000);
    std::iota(std::begin(v), std::end(v), -5'000'000);
    std::shuffle(std::begin(v), std::end(v), std::mt19937{ std::random_device{}() });

    std::cout << test_title;
    // STL algorithm
    T m{};
    {
        auto t{ function_timer<>::duration(
            [&f, &v, &m]() { m = f(std::cbegin(v), std::cend(v)); }
        ) };
        std::cout << std::format("\n\t{}: {} ({})", f_name, m, t);
    }
    // Parallel STL algorithm
    {
        T m{};
        auto t{ function_timer<>::duration(
            [&g, &v, &m]() { m = g(std::cbegin(v), std::cend(v)); }
        ) };
        std::cout << std::format("\n\t{}(ex::par): {} ({})", g_name, m, t);
    }
    // Custom parallel function
    std::cout << std::format("\n\t{}:", h_name);
    for (size_t thread_pool_size : { 4, 8, 16 })
    {
        for (size_t block_size : { 1'000, 10'000, 100'000 })
        {
            T n{};
            auto t{ function_timer<>::duration(
                [&h, &v, thread_pool_size, block_size, &n]() { n = h(std::cbegin(v), std::cend(v), thread_pool_size, block_size); }
            ) };
            assert("Error: custom parallel function returns a different result, " and m == n);
            std::cout << std::format("\n\t\tthread_pool_size={}, block_size={}: {} ({})",
                thread_pool_size, block_size, n, t);
        }
    }
    std::cout << "\n";
}

// Parallel min and max element algorithms using asynchronous functions
//
// Implement general-purpose parallel algorithms that find the minimum value and, respectively, the maximum value in a given range.
// The parallelism should be implemented using asynchronous functions, although the number of concurrent funtions is an implementation detail.
void problem_63_main()
{
    using namespace std::literals;

    // Min, T = int
    test_parallel_binary_operation<int>(
        [](auto first, auto last) { return *std::min_element(first, last); },
        [](auto first, auto last) { return *std::min_element(std::execution::par, first, last); },
        [](auto first, auto last, auto thread_pool_size, auto block_size) { return parallel_min(first, last, thread_pool_size, block_size); },
        std::vector<std::string_view>{ "Min<int>:", "min_element", "parallel_min" });

    // Max, T = int
    test_parallel_binary_operation<int>(
        [](auto first, auto last) { return *std::max_element(first, last); },
        [](auto first, auto last) { return *std::max_element(std::execution::par, first, last); },
        [](auto first, auto last, auto thread_pool_size, auto block_size) { return parallel_max(first, last, thread_pool_size, block_size); },
        std::vector<std::string_view>{ "Max<int>:", "max_element", "parallel_max" });

    // Min, T = int64_t
    test_parallel_binary_operation<int64_t>(
        [](auto first, auto last) { return *std::min_element(first, last); },
        [](auto first, auto last) { return *std::min_element(std::execution::par, first, last); },
        [](auto first, auto last, auto thread_pool_size, auto block_size) { return parallel_min(first, last, thread_pool_size, block_size); },
        std::vector<std::string_view>{ "Min<int64_t>:", "min_element", "parallel_min" });

    // Max, T = int64_t
    test_parallel_binary_operation<int64_t>(
        [](auto first, auto last) { return *std::max_element(first, last); },
        [](auto first, auto last) { return *std::max_element(std::execution::par, first, last); },
        [](auto first, auto last, auto thread_pool_size, auto block_size) { return parallel_max(first, last, thread_pool_size, block_size); },
        std::vector<std::string_view>{ "Max<int64_t>:", "max_element", "parallel_max" });

    std::cout << "\n";
}
