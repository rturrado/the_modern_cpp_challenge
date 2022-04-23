#include "chapter_06_algorithms_and_data_structures/problem_057_quicksort.h"
#include "rtc/print.h"

#include <algorithm>  // iter_swap
#include <functional>  // less
#include <iostream>  // cout
#include <iterator>  // distance
#include <vector>

template <typename InputIt, typename Compare>
InputIt partition(InputIt begin, InputIt end, Compare compare)
{
    auto pivot{ begin };
    auto i{ begin };
    
    for (auto j{ next(begin) }; j < end; ++j)
    {
        if (not compare(*pivot, *j))  // !(*pivot < *j), i.e. *j <= *pivot
        {
            i++;
            std::iter_swap(i, j);
        }
    }
    std::iter_swap(i, pivot);

    return i;
}

template <typename InputIt, typename Compare>
void quicksort(InputIt begin, InputIt end, Compare compare)
{
    if (begin < end)
    {
        auto pivot{ ::partition(begin, end, compare) };
        quicksort(begin, pivot, compare);
        quicksort(pivot + 1, end, compare);
    }
}

template <typename InputIt>
void quicksort(InputIt begin, InputIt end)
{
    quicksort(begin, end, std::less<>{});
}

// Sort algorithm
//
// Write a function that, given a pair of random access InputItators to define its lower and upper bounds,
// sorts the elements of the range using the quicksort algorithm.
//
// There should be two overloads of the function:
// one that uses operator< to compare the elements of the range and put them in ascending order,
// and one that uses a user-defined binary comparison function for comparing the elements
void problem_57_main()
{
    std::vector<char> v_c{ 'z', 'A', '9', '!', 'm', 'o', 'N', '9' };
    std::cout << "Quicksorting " << v_c << ": ";
    quicksort(begin(v_c), end(v_c));
    std::cout << v_c << "\n";

    std::vector<int> v_i{ 10, 15, 20, 25, 30, 35, 40 };
    std::cout << "Quicksorting " << v_i << ": ";
    quicksort(begin(v_i), end(v_i), [](int i, int j) { return (i % 10 - i / 10) < (j % 10 - j / 10); });
    std::cout << v_i << "\n";

    std::cout << "\n";
}
