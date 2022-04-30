#pragma once

#include <algorithm>  // iter_swap
#include <functional>  // less
#include <future>  // async
#include <iterator>  // distance


template <typename RandomIt, typename Compare>
RandomIt partition(RandomIt begin, RandomIt end, Compare compare) {
    auto pivot{ begin };
    auto i{ begin };

    for (auto j{ next(begin) }; j < end; ++j) {
        if (not compare(*pivot, *j)) {  // !(*pivot < *j), i.e. *j <= *pivot
            i++;
            std::iter_swap(i, j);
        }
    }
    std::iter_swap(i, pivot);

    return i;
}


template <typename RandomIt, typename Compare>
void quicksort(RandomIt begin, RandomIt end, Compare compare) {
    if (begin < end) {
        auto pivot{ ::partition(begin, end, compare) };
        quicksort(begin, pivot, compare);
        quicksort(pivot + 1, end, compare);
    }
}


template <typename RandomIt>
void quicksort(RandomIt begin, RandomIt end) {
    quicksort(begin, end, std::less<>{});
}


template <typename RandomIt, typename Compare>
void parallel_quicksort(RandomIt begin, RandomIt end, Compare compare) {
    constexpr size_t MINIMUM_PARTITION_SIZE_FOR_PARALLELISING{ 100'000 };

    if (begin < end) {
        auto pivot{ ::partition(begin, end, compare) };

        if (end - begin <= MINIMUM_PARTITION_SIZE_FOR_PARALLELISING) {
            parallel_quicksort(begin, pivot, compare);
            parallel_quicksort(pivot + 1, end, compare);
        }
        else {
            auto future1 = std::async(std::launch::async,
                [&begin, &pivot, &compare]() { parallel_quicksort(begin, pivot, compare); });
            auto future2 = std::async(std::launch::async,
                [&pivot, &end, &compare]() { parallel_quicksort(pivot + 1, end, compare); });

            future1.wait();
            future2.wait();
        }
    }
}


template <typename RandomIt>
void parallel_quicksort(RandomIt begin, RandomIt end) {
    parallel_quicksort(begin, end, std::less<>{});
}
