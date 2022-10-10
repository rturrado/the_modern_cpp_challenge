#pragma once

#include <algorithm>  // max, max_element, min, min_element
#include <functional>  // identity, less
#include <future>  // async
#include <iosfwd>
#include <iterator>  // distance, iterator_traits
#include <ranges>
#include <semaphore>  // counting_semaphore
#include <thread>
#include <vector>


namespace tmcppc::algorithm::async {
    static const size_t THREAD_POOL_SIZE_DEFAULT{ std::thread::hardware_concurrency() };
    static const size_t THREAD_POOL_SIZE_MIN{ 1 };
    static const size_t THREAD_POOL_SIZE_MAX{ static_cast<size_t>(std::thread::hardware_concurrency()) * 2 };
    static const size_t BLOCK_SIZE_DEFAULT{ 10'000 };
    static const size_t BLOCK_SIZE_MIN{ 100 };


    template <typename Range, typename BinaryOperation>
    auto parallel_binary_operation(Range&& rng, BinaryOperation&& binary_op,
        size_t thread_pool_size = THREAD_POOL_SIZE_DEFAULT, size_t block_size = BLOCK_SIZE_DEFAULT) {

        using ForwardIt = std::ranges::iterator_t<Range>;

        size_t size{ rng.size() };
        thread_pool_size = std::min(thread_pool_size, THREAD_POOL_SIZE_MAX);
        thread_pool_size = std::max(thread_pool_size, THREAD_POOL_SIZE_MIN);
        block_size = std::max(block_size, BLOCK_SIZE_MIN);

        std::counting_semaphore task_slots(static_cast<std::ptrdiff_t>(thread_pool_size));
        size_t num_blocks{ (size < block_size) ? 1 : (size / block_size) + (size % block_size ? 1 : 0) };
        auto futures{ std::vector<std::future<void>>(num_blocks) };
        auto block_results{ std::vector<ForwardIt>(num_blocks) };

        // Launch one task per block
        // We can run thread_pool_size tasks in parallel
        // If all task slots are busy, we have to wait for a task to finish
        for (size_t i{ 0 }; i < num_blocks; ++i) {
            auto begin_it{ std::ranges::begin(rng) + i * block_size };
            auto end_it{ std::ranges::begin(rng) + std::min(size, (i + 1) * block_size) };

            // Wait for a task slot to be free
            task_slots.acquire();

            futures[i] = std::async(
                std::launch::async,
                [&binary_op, begin_it, end_it, &block_result = block_results[i], &task_slots]() {
                    // Execute task, and set the result for the block
                    block_result = binary_op(std::ranges::subrange{ begin_it, end_it }, std::ranges::less{}, std::identity{});

                    // Release the task slot
                    task_slots.release();
                }
            );
        }

        // Wait for all the tasks to finish
        for (auto& future : futures) {
            future.get();
        }

        // Apply the binary operation to the container with the block results
        return *binary_op(block_results, std::ranges::less{}, [](const auto& it) { return *it; });
    }


    template <typename Range>
    auto parallel_min(Range&& rng,
        size_t thread_pool_size = THREAD_POOL_SIZE_DEFAULT, size_t block_size = BLOCK_SIZE_DEFAULT) {

        return parallel_binary_operation(std::forward<Range>(rng),
            [](auto&& r, auto cmp, auto proj) { return std::ranges::min_element(r, cmp, proj); },
            thread_pool_size, block_size);
    }


    template <typename Range>
    auto parallel_max(Range&& rng,
        size_t thread_pool_size = THREAD_POOL_SIZE_DEFAULT, size_t block_size = BLOCK_SIZE_DEFAULT) {

        return parallel_binary_operation(std::forward<Range>(rng),
            [](auto&& r, auto cmp, auto proj) { return std::ranges::max_element(r, cmp, proj); },
            thread_pool_size, block_size);
    }
}  // namespace tmcppc::algorithm::async


void problem_63_main(std::ostream& os);
