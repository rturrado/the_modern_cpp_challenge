#include "chapter_01_math/problem_003_least_common_multiple.h"
#include "rtc/console_read.h"  // read_list_of_positive_numbers
#include "rtc/print.h"

#include <algorithm>  // all_of, sort
#include <iostream>  // cout
#include <vector>

using namespace rtc::print;


long lcm(const std::vector<int>& v)
{
    auto bigger_number = v[v.size() - 1];
    for (auto i{1}; ; ++i) {
        long possible_lcm{ bigger_number * i };
        if (std::all_of(std::cbegin(v), std::prev(cend(v)), [&possible_lcm](int n) {
                return possible_lcm % n == 0; })) {
            return possible_lcm;
        }
    }
    return -1;
};


// Least common multiple
//
// Write a program that will, given two or more positive integers, calculate and print the least common multiple of them all
void problem_3_main()
{
    // Read a list of positive numbers
    auto v{ rtc::console::read_list_of_positive_numbers(2, 0) };

    // Sort list
    std::sort(v.begin(), v.end());

    // Calculate the least common multiple
    //
    // I sort the input numbers, and take the bigger one
    // Then, I find the number that is 1, 2... i times bigger than the bigger one,
    // such that it is multiple of all the other numbers in the list
    std::cout << "The least common multiple of " << v << " is: " << lcm(v) << "\n\n";
}
