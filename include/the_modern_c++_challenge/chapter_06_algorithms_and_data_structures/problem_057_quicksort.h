#pragma once

#include <algorithm>  // iter_swap
#include <functional>  // less
#include <iterator>  // distance
#include <ostream>
#include <vector>


template <typename InputIt, typename Compare>
InputIt partition(InputIt begin, InputIt end, Compare compare) {
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


template <typename InputIt, typename Compare>
void quicksort(InputIt begin, InputIt end, Compare compare) {
    if (begin < end) {
        auto pivot{ ::partition(begin, end, compare) };
        quicksort(begin, pivot, compare);
        quicksort(pivot + 1, end, compare);
    }
}


template <typename InputIt>
void quicksort(InputIt begin, InputIt end) {
    quicksort(begin, end, std::less<>{});
}


void problem_57_main(std::ostream& os);
void problem_57_main();
