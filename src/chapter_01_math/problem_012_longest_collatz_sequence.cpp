#include "chapter_01_math/problem_012_longest_collatz_sequence.h"
#include "rtc/timer.h"  // function_timer

#include <fmt/ostream.h>
#include <fmt/ranges.h>
#include <iostream>  // cout
#include <map>
#include <ostream>
#include <utility>  // pair
#include <vector>


size_t get_collatz_sequence_size(size_t n)
{
    static std::map<size_t, size_t> collatz_sequence_sizes{};

    if (n == 0) {  // safety check
        return 0;
    }
    if (collatz_sequence_sizes.contains(n)) {  // stop case 1: we know the sequence size for n
        return collatz_sequence_sizes[n];
    }
    if (n == 1) {  // stop case 2: last number of the sequence
        collatz_sequence_sizes[n] = 1;
        return 1;
    }
    if (n % 2 == 0) {  // n is even
        size_t s = 1 + get_collatz_sequence_size(n / 2);
        collatz_sequence_sizes[n] = s;
        return s;
    }
    // n is odd
    size_t s = 1 + get_collatz_sequence_size(n * 3 + 1);
    collatz_sequence_sizes[n] = s;
    return s;
}


std::vector<size_t> get_collatz_sequence(size_t n)
{
    if (n == 0) {
        return {};
    }

    std::vector<size_t> ret{ n };
    while (n > 1) {
        if (n % 2 == 0) {
            n /= 2;
        }
        else {
            n = n * 3 + 1;
        }
        ret.push_back(n);
    }
    return ret;
}


// v1: my version
//
// It's slower because it makes use of a get_collatz_sequence_size function that:
// it is recursive, and it caches values over the limit
std::pair<size_t, size_t> get_longest_collatz_sequence_v1(size_t limit)
{
    std::size_t n{ 0 };
    std::size_t n_size{ 0 };

    for (size_t i{ 1 }; i <= limit; ++i) {
        size_t i_size{ get_collatz_sequence_size(i) };

        if (i_size > n_size) {
            n = i;
            n_size = i_size;
        }
    }

    return std::make_pair(n, n_size);
}


// v2: book's version
std::pair<size_t, size_t> get_longest_collatz_sequence_v2(size_t limit)
{
    size_t number{ 0 };
    size_t length{ 0 };

    std::vector<size_t> cache(limit + 1, 1);

    for (size_t i{ 2 }; i <= limit; ++i) {
        auto n{ i };
        long steps{ 0 };
        while (n != 1 and n >= i) {
            if ((n % 2) == 0) {
                n = n / 2;
            }
            else {
                n = n * 3 + 1;
            }
            steps++;
        }
        cache[i] = steps + cache[n];

        if (cache[i] > length) {
            number = i;
            length = cache[i];
        }
    }

    return std::make_pair(number, length);
}


void problem_12_main(std::ostream& os)
{
    constexpr size_t limit{ 1'000'000 };

    // Determine n and Collatz sequence size for n
    // n being the number up to limit with longest Collatz sequence
    size_t n{ 1 };
    size_t n_collatz_sequence_size{ 1 };
    auto result = get_longest_collatz_sequence_v1(limit);

    // Print results
    fmt::print(os, "Number between 1 and {0} with longest Collatz sequence ({2} elements) is: {1}\n",
        limit, result.first, result.second);
}


// Largest Collatz sequence
//
// Write a program that determines and prints which number up to 1 million
// produces the longest Collatz sequence and what length is
void problem_12_main()
{
    problem_12_main(std::cout);
}
