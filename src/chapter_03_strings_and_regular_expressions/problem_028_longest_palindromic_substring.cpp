#include "chapter_03_strings_and_regular_expressions/problem_028_longest_palindromic_substring.h"

#include <fmt/ostream.h>
#include <iostream>  // cout
#include <span>
#include <string_view>
#include <vector>


namespace tmcppc::problem_28 {
    bool is_palindrome(std::string_view s) {
        return s.substr(0, s.size() / 2) == std::string{ crbegin(s), crbegin(s) + std::ssize(s) / 2 };
    }


    std::string_view get_longest_palindromic_substring(std::string_view s) {
        if (s.size() == 0) {
            return std::string_view{};
        }

        std::string_view ret{ s.cbegin(), s.cbegin() + 1 };

        for (size_t begin_pos{ 0 }; begin_pos + ret.size() < s.size(); begin_pos++) {
            for (size_t end_pos{ s.size() - 1 }; ; --end_pos) {
                // Search s[begin_pos] from the back
                end_pos = s.rfind(s[begin_pos], end_pos);

                // Break if the new possible palindrome's size is less than or equal to the current longest palindrome's size
                if (end_pos + 1 - begin_pos <= ret.size()) {
                    break;
                }

                // Otherwise go and check if we got a new longer palindrome
                std::string_view p{ s.substr(begin_pos, end_pos + 1 - begin_pos) };
                if (is_palindrome(p)) {
                    ret = p;
                }
            }
        }

        return ret;
    }
}  // namespace tmcppc::problem_28


void problem_28_main(std::ostream& os) {
    using namespace tmcppc::problem_28;

    for (auto&& s : std::vector<std::string_view>{ "", "s", "level", "sahararahnide", "123aba3218888888888c" }) {
        fmt::print(os, "Longest palindromic substring in \"{}\" is: \"{}\"\n" , s, get_longest_palindromic_substring(s));
    }
    fmt::print(os, "\n");
}


// Longest palindromic substring
//
// Write a function that, given an input string, locates and returns the longest sequence
// in the string that is a palindrome.
// If multiple palindromes of the same length exist, the first one should be returned
void problem_28_main() {
    problem_28_main(std::cout);
}
