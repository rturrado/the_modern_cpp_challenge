#pragma once

#include <algorithm>  // max, min, transform
#include <future>  // async
#include <iostream>  // cout
#include <iterator>  // distance
#include <ostream>
#include <semaphore>  // counting_semaphore
#include <thread>  // hardware_concurrency
#include <vector>


namespace tmcppc::parallel_transform {
    static const size_t THREAD_POOL_SIZE_DEFAULT{ std::thread::hardware_concurrency() };
    static const size_t THREAD_POOL_SIZE_MAX{ static_cast<size_t>(std::thread::hardware_concurrency()) * 2 };
    static const size_t BLOCK_SIZE_DEFAULT{ 10'000 };
    static const size_t BLOCK_SIZE_MIN{ 100 };

    template <typename InputIt, typename OutputIt, typename UnaryOperation>
    void parallel_transform(InputIt first, InputIt last, OutputIt d_first, UnaryOperation&& f,
        size_t thread_pool_size = THREAD_POOL_SIZE_DEFAULT, size_t block_size = BLOCK_SIZE_DEFAULT) {

        size_t size{ static_cast<size_t>(std::distance(first, last)) };
        thread_pool_size = std::min(thread_pool_size, THREAD_POOL_SIZE_MAX);
        block_size = std::max(block_size, BLOCK_SIZE_MIN);

        std::counting_semaphore task_slots(thread_pool_size);
        size_t num_blocks{ (size < block_size) ? 1 : (size / block_size) + (size % block_size ? 1 : 0) };
        auto futures{ std::vector<std::future<void>>(num_blocks) };

        // Launch one task per block
        // We can run thread_pool_size tasks in parallel
        // If all task slots are busy, we have to wait for a task to finish
        for (size_t i{ 0 }; i < num_blocks; ++i) {
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
        for (auto& future : futures) {
            future.get();
        }
    }
}  // namespace tmcppc::parallel_transform


void problem_61_main(std::ostream& os);
void problem_61_main();
