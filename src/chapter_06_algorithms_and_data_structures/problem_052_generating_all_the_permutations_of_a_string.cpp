#include "Chapter6_AlgorithmsAndDataStructures.h"

#include <algorithm>  // for_each, next_permutation, sort
#include <iostream>  // cout
#include <string>
#include <vector>

using permutations = std::vector<std::string>;

permutations all_permutations_rec_impl(std::string str)
{
    permutations ret{};
    if (str.size() == 1) { ret.push_back(str); }
    else
    {
        for (const auto& s : all_permutations_rec_impl(str.substr(1)))
        {
            for (auto i{ 0 }; i <= s.size(); ++i)
            {
                ret.push_back(s.substr(0, i) + str[0] + s.substr(i));
            }
        }
    }
    return ret;
}

permutations all_permutations_rec(std::string str)
{
    if (str.empty()) { return {}; }

    std::sort(begin(str), end(str));
    return all_permutations_rec_impl(str);
}

permutations all_permutations(std::string str)
{
    if (str.empty()) { return {}; }

    permutations ret{};
    std::sort(begin(str), end(str));
    do { ret.push_back(str); } while (std::next_permutation(begin(str), end(str)));
    return ret;
}

// Generating all the permutations of a string
//
// Write a function that prints on the console all the possible permutations of a given string.
// You should provide two versions of this function: one that uses recursion, and one that does not.
void problem_52_main()
{
    for (const auto& str : { "", "n", "ab", "andy" })
    {
        std::cout << "All permutations of string: " << str << "\n";

        std::cout << "\t1) Using recursion:\n";
        permutations apr{ all_permutations_rec(str) };
        std::for_each(cbegin(apr), cend(apr), [first = true](const auto& s) mutable {
            std::cout << (first ? "\t\t" : ", ") << s; first = false;
        });
        std::cout << "\n";

        std::cout << "\t2) Not using recursion:\n";
        permutations ap{ all_permutations(str) };
        std::for_each(cbegin(ap), cend(ap), [first = true](const auto& s) mutable {
            std::cout << (first ? "\t\t" : ", ") << s; first = false;
        });
        std::cout << "\n\n";
    }
}
