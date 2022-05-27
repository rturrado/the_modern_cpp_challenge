#pragma once

#include <algorithm>  // max, max_element, min, min_element
#include <iosfwd>
#include <iterator>  // distance, iterator_traits
#include <semaphore>  // counting_semaphore
#include <thread>
#include <vector>


namespace tmcppc::algorithm::thread {
    static const size_t THREAD_POOL_SIZE_DEFAULT{ std::thread::hardware_concurrency() };
    static const size_t THREAD_POOL_SIZE_MAX{ static_cast<size_t>(std::thread::hardware_concurrency()) * 2 };
    static const size_t BLOCK_SIZE_DEFAULT{ 10'000 };
    static const size_t BLOCK_SIZE_MIN{ 100 };


    template <typename ForwardIt, typename BinaryOperation>
    auto parallel_binary_operation(ForwardIt first, ForwardIt last, BinaryOperation&& binary_op,
        size_t thread_pool_size = THREAD_POOL_SIZE_DEFAULT, size_t block_size = BLOCK_SIZE_DEFAULT) {

        using T = typename std::iterator_traits<ForwardIt>::value_type;

        size_t size{ static_cast<size_t>(std::distance(first, last)) };
        thread_pool_size = std::min(thread_pool_size, THREAD_POOL_SIZE_MAX);
        block_size = std::max(block_size, BLOCK_SIZE_MIN);

        std::counting_semaphore task_slots(thread_pool_size);
        size_t num_blocks{ (size < block_size) ? 1 : (size / block_size) + (size % block_size ? 1 : 0) };
        auto threads{ std::vector<std::thread>(num_blocks) };
        auto block_results{ std::vector<T>(num_blocks) };

        // Launch one task per block
        // We can run thread_pool_size tasks in parallel
        // If all task slots are busy, we have to wait for a task to finish
        for (size_t i{ 0 }; i < num_blocks; ++i) {
            auto cbegin_it{ first + i * block_size };
            auto cend_it{ first + std::min(size, (i + 1) * block_size) };

            // Wait for a task slot to be free
            task_slots.acquire();

            threads[i] = std::thread(
                [&binary_op, cbegin_it, cend_it, &block_result = block_results[i], &task_slots]() {
                    // Execute task, and set the result for the block
                    block_result = binary_op(cbegin_it, cend_it);

                    // Release the task slot
                    task_slots.release();
                }
            );
        }

        // Wait for all the tasks to finish
        for (auto& thread : threads) {
            thread.join();
        }

        // Apply the binary operation to the container with the block results
        return binary_op(std::begin(block_results), std::end(block_results));
    }


    template <typename ForwardIt>
    auto parallel_min(ForwardIt first, ForwardIt last,
        size_t thread_pool_size = THREAD_POOL_SIZE_DEFAULT, size_t block_size = BLOCK_SIZE_DEFAULT) {

        return parallel_binary_operation(first, last,
            [](auto first, auto last) { return *std::min_element(first, last); },
            thread_pool_size, block_size);
    }


    template <typename ForwardIt>
    auto parallel_max(ForwardIt first, ForwardIt last,
        size_t thread_pool_size = THREAD_POOL_SIZE_DEFAULT, size_t block_size = BLOCK_SIZE_DEFAULT) {

        return parallel_binary_operation(first, last,
            [](auto first, auto last) { return *std::max_element(first, last); },
            thread_pool_size, block_size);
    }
}  // namespace tmcppc::algorithm::thread


void problem_62_main(std::ostream& os);
void problem_62_main();
