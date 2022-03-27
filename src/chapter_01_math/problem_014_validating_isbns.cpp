#include "chapter_01_math/problem_014_validating_isbns.h"
#include "rtc/console_read.h"  // clear_istream

#include <algorithm>  // count_if, remove_if
#include <cassert>  // assert
#include <iostream>  // cin, cout
#include <istream>
#include <numeric>  // accumulate
#include <ostream>
#include <string>  // getline


std::string read_n_digit_isbn(size_t n)
{
    std::string ret{};

    const std::string separators{ "- " };  // hyphens or spaces

    bool valid_input{ false };
    while (!valid_input)
    {
        std::cout << "Please enter a " << n << " digit ISBN (may include hyphens and/or spaces): ";
        
        std::getline(std::cin, ret);
        
        auto number_of_digits{ std::count_if(ret.begin(), ret.end(), [](auto& n) { return std::isdigit(n) != 0; }) };
        auto number_of_separators{ std::count_if(ret.begin(), ret.end(),
            [&separators](char c) { return separators.find(c) != std::string::npos; }) };
        
        if (number_of_digits != n ||
            ret.size() != number_of_digits + number_of_separators)
        {
            std::cout << "\tError: invalid input\n";
        }
        else
        {
            valid_input = true;
        }
        if (!valid_input)
        {
            rtc::console::clear_istream(std::cin);
        }
    }
    // Erase-remove idiom
    ret.erase(
        std::remove_if(ret.begin(), ret.end(),
            [&separators](char c) { return separators.find(c) != std::string::npos; }),
        ret.end());

    return ret;
}


bool validate_10_digit_isbn(const std::string& str)
{
    constexpr size_t number_of_digits{ 10 };
    assert(str.size() == number_of_digits);

    auto sum = std::accumulate(str.begin(), str.end(), static_cast<size_t>(0),
        [i = number_of_digits](size_t sum, size_t c) mutable { return sum + (c - '0') * i--; });
    
    return !(sum % 11);
}


bool validate_13_digit_isbn(const std::string& str)
{
    constexpr size_t number_of_digits{ 13 };
    assert(str.size() == number_of_digits);

    auto sum = std::accumulate(str.begin(), str.end(), static_cast<size_t>(0),
        [i = 3](size_t sum, size_t c) mutable { i = (i == 1 ? 3 : 1); return sum + (c - '0') * i; });

    return !(sum % 10);
}


void problem_14_main(std::istream& is, std::ostream& os)
{
    // Read 10-digit ISBN
    auto str = read_n_digit_isbn(10);

    // Validate 10-digit ISBN
    auto valid = validate_10_digit_isbn(str);
    os << str << " is" << (valid ? " " : " NOT ") << "a valid ISBN\n";

    // Read 13-digit ISBN
    str = read_n_digit_isbn(13);

    // Validate 13-digit ISBN
    valid = validate_13_digit_isbn(str);
    os << str << " is" << (valid ? " " : " NOT ") << "a valid ISBN\n\n";
}


// Validating ISBNs
// Write a program that validates that 10-digit values entered by the user,
// as a string, represent valid ISBN-10 numbers
void problem_14_main()
{
    problem_14_main(std::cin, std::cout);
}
