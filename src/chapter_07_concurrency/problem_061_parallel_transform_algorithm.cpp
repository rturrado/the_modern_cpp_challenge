#include "Chapter7_Concurrency.h"
#include "RtcTimer.h"

#include <algorithm>  // max, min, transform
#include <cassert>  // assert
#include <execution>  // par
#include <format>
#include <future>  // async
#include <iostream>  // cout
#include <numeric>  // iota
#include <semaphore>  // counting_semaphore
#include <thread>  // hardware_concurrency
#include <vector>

static const size_t THREAD_POOL_SIZE_DEFAULT{ std::thread::hardware_concurrency() };
static const size_t THREAD_POOL_SIZE_MAX{ static_cast<size_t>(std::thread::hardware_concurrency()) * 2 };
static const size_t BLOCK_SIZE_DEFAULT{ 10'000 };
static const size_t BLOCK_SIZE_MIN{ 100 };

template <typename InputIt, typename OutputIt, typename UnaryOperation>
void parallel_transform(InputIt first, InputIt last, OutputIt d_first, UnaryOperation&& f,
    size_t thread_pool_size = THREAD_POOL_SIZE_DEFAULT, size_t block_size = BLOCK_SIZE_DEFAULT)
{
    size_t size{ static_cast<size_t>(std::distance(first, last)) };
    thread_pool_size = std::min(thread_pool_size, THREAD_POOL_SIZE_MAX);
    block_size = std::max(block_size, BLOCK_SIZE_MIN);

    std::counting_semaphore task_slots(thread_pool_size);
    size_t num_blocks{ (size / block_size) + (size % block_size) };
    auto futures{ std::vector<std::future<void>>(num_blocks) };
    
    // Launch one task per block
    // We can run thread_pool_size tasks in parallel
    // If all task slots are busy, we have to wait for a task to finish
    for (size_t i{ 0 }; i < num_blocks; ++i)
    {
        auto begin_it{ first + i * block_size };
        auto end_it{ first + std::min(size, (i + 1) * block_size) };
        auto d_begin_it{ d_first + i * block_size };

        // Wait for a task slot to be free
        task_slots.acquire();

        futures[i] = std::async(
            std::launch::async,
            [begin_it, end_it, d_begin_it, &f, &task_slots]() {
                // Execute task
                std::transform(
                    begin_it,
                    end_it,
                    d_begin_it,
                    std::forward<UnaryOperation>(f));

                // Release the task slot
                task_slots.release();
            }
        );
    }
    
    // Wait for all tasks to finish
    for (auto& ft: futures) { ft.get(); }
}

// Parallel transform algorithm
//
// Write a general-purpose algorithm that applies a given unary function to transform the elements of a range in parallel.
// The unary operation used to transform the range must not invalidate range iterators or modify the elements of the range.
// The level of parallelism, that is, the number of execution threads and the way it is achieved, is an implementation detail.
void problem_61_main()
{
    auto square = [](int n) { return n * n; };
    
    std::vector<int> v(10'000'000);
    std::iota(std::begin(v), std::end(v), 0);

    std::cout << "Times:";
    // std::transform
    auto w{ v };
    {
        auto t{ function_timer<>::duration(
            [&w, &square]() mutable {
                std::transform(std::cbegin(w), std::cend(w), std::begin(w), square);
            }
        ) };
        std::cout << std::format("\n\tstd::transform: {}", t);
    }
    // std::transform(std::execution::par)
    {
        auto w{ v };
        auto t{ function_timer<>::duration(
            [&w, &square]() mutable {
                std::transform(std::execution::par, std::cbegin(w), std::cend(w), std::begin(w), square);
            }
        ) };
        std::cout << std::format("\n\tstd::transform(ex::par): {}", t);
    }
    // Parallel transform with different thread pool and block sizes
    std::cout << std::format("\n\tparallel_transform:");
    for (size_t thread_pool_size : { 4, 8, 16 })
    {
        for (size_t block_size : { 1'000, 10'000, 100'000 })
        {
            auto x{ v };
            auto t{ function_timer<>::duration(
                [thread_pool_size, block_size, &x, &square]() mutable {
                    parallel_transform(std::cbegin(x), std::cend(x), std::begin(x), square, thread_pool_size, block_size);
                }
            ) };
            assert("Error: custom parallel transform returns a different result, " and w == x);
            std::cout << std::format("\n\t\tthread_pool_size={}, block_size={}: {}", thread_pool_size, block_size, t);
        }
    }

    std::cout << "\n\n";
}
