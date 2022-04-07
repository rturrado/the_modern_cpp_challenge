#include "chapter_03_strings_and_regular_expressions/problem_028_longest_palindromic_substring.h"

#include <iostream>  // cout
#include <string>
#include <vector>


std::string get_longest_palindromic_substring(const std::string& s)
{
    if (s.size() == 0)
    {
        return std::string{ "" };
    }

    struct MySpan
    {
        size_t begin{ 0 };
        size_t size{ 1 };
    };
    MySpan ret{};

    auto is_palindrome = [](const std::string& s)
    {
        return std::string{ cbegin(s), cbegin(s) + s.size() / 2 } == std::string{ crbegin(s), crbegin(s) + s.size() / 2 };
    };

    for (size_t begin_pos{ 0 }; begin_pos + ret.size < s.size(); begin_pos++)
    {
        for (size_t end_pos{ s.size() - 1 }; ; --end_pos)
        {
            // Search s[begin_pos] from the back
            end_pos = s.rfind(s[begin_pos], end_pos);

            // Break if the new possible palindrome's size is less than or equal to the current longest palindrome's size
            if (end_pos + 1 - begin_pos <= ret.size)
            {
                break;
            }

            // Otherwise go and check if we got a new longer palindrome
            std::string p{ s.substr(begin_pos, end_pos + 1 - begin_pos) };

            if (is_palindrome(p))
            {
                ret.begin = begin_pos;
                ret.size = p.size();
            }
        }
    }

    return s.substr(ret.begin, ret.size);
}


void test_get_longest_palindromic_substring(const std::vector<std::string>& v)
{
    for (const auto& s : v)
    {
        std::cout << "Longest palindromic substring in \"" << s << "\" is: \"" << get_longest_palindromic_substring(s) << "\"\n";
    }
}


// Longest palindromic substring
//
// Write a function that, given an input string, locates and returns the longest sequence
// in the string that is a palindrome.
// If multiple palindromes of the same length exist, the first one should be returned
void problem_28_main()
{
    const std::vector<std::string> v{ "123aba3218888888888c", "", "level", "s", "sahararahnide" };

    test_get_longest_palindromic_substring(v);

    std::cout << "\n";
}
