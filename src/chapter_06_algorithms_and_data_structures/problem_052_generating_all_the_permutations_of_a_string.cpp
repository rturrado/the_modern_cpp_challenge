#include "chapter_06_algorithms_and_data_structures/problem_052_generating_all_the_permutations_of_a_string.h"

#include <algorithm>  // for_each, next_permutation, sort
#include <fmt/ostream.h>
#include <fmt/ranges.h>
#include <iostream>  // cout
#include <string>


permutations all_permutations_rec_impl(std::string str) {
    permutations ret{};
    if (str.size() == 1) {
        ret.push_back(str);
    }
    else {
        for (const auto& s : all_permutations_rec_impl(str.substr(1))) {
            for (auto i{ 0 }; i <= s.size(); ++i) {
                ret.push_back(s.substr(0, i) + str[0] + s.substr(i));
            }
        }
    }
    return ret;
}


permutations all_permutations_rec(std::string str) {
    if (str.empty()) {
        return {};
    }

    std::sort(begin(str), end(str));
    return all_permutations_rec_impl(str);
}


permutations all_permutations(std::string str) {
    if (str.empty()) {
        return {};
    }

    permutations ret{};
    std::sort(begin(str), end(str));
    do {
        ret.push_back(str);
    }
    while (std::next_permutation(begin(str), end(str)));
    return ret;
}


void problem_52_main(std::ostream& os) {
    for (const auto& str : { "", "n", "ab", "andy" }) {
        fmt::print(os, "All permutations of string: '{}'\n", str);

        fmt::print(os, "\t1) Using recursion:\n");
        permutations apr{ all_permutations_rec(str) };
        fmt::print(os, "\t\t[{}]\n", fmt::join(apr, ", "));

        fmt::print(os, "\t2) Not using recursion:\n");
        permutations ap{ all_permutations(str) };
        fmt::print(os, "\t\t[{}]\n\n", fmt::join(ap, ", "));
    }
}


// Generating all the permutations of a string
//
// Write a function that prints on the console all the possible permutations of a given string.
// You should provide two versions of this function: one that uses recursion, and one that does not.
void problem_52_main() {
    problem_52_main(std::cout);
}
