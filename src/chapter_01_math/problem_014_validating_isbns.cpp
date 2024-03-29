#include "chapter_01_math/problem_014_validating_isbns.h"
#include "console.h"

#include <algorithm>  // count_if, erase_if
#include <fmt/ostream.h>
#include <numeric>  // accumulate
#include <string>  // getline

#undef NDEBUG
#include <cassert>  // assert

using namespace tmcppc::system;


namespace tmcppc::problem_14 {
    std::string read_n_digit_isbn(std::istream& is, std::ostream& os, const console& console, size_t n) {
        std::string ret{};

        const std::string separators{ "- " };  // hyphens or spaces

        bool valid_input{ false };
        while (not valid_input) {
            fmt::print(os, "Please enter a {}-digit ISBN (may include hyphens and/or spaces): ", n);

            std::getline(is, ret);

            auto number_of_digits{ std::ranges::count_if(ret, [](auto& n) {
                return std::isdigit(n) != 0;
            }) };
            auto number_of_separators{ std::ranges::count_if(ret, [&separators](char c) {
                return separators.find(c) != std::string::npos;
            }) };

            valid_input = (n == static_cast<size_t>(number_of_digits) and
                (ret.size() == static_cast<size_t>(number_of_digits + number_of_separators)));

            if (not valid_input) {
                fmt::print(os, "\tError: invalid input.\n");
                console.clear_istream(is);
            }
        }
        std::erase_if(ret, [&separators](char c) {
            return separators.find(c) != std::string::npos;
        });

        return ret;
    }


    bool validate_10_digit_isbn(const std::string& str) {
        constexpr size_t number_of_digits{ 10 };
        assert(str.size() == number_of_digits);

        auto sum = std::accumulate(str.begin(), str.end(), static_cast<size_t>(0),
            [i = number_of_digits](size_t sum, size_t c) mutable { return sum + (c - '0') * i--; });

        return !(sum % 11);
    }


    bool validate_13_digit_isbn(const std::string& str) {
        constexpr size_t number_of_digits{ 13 };
        assert(str.size() == number_of_digits);

        auto sum = std::accumulate(str.begin(), str.end(), static_cast<size_t>(0),
            [i = static_cast<size_t>(3)](size_t sum, size_t c) mutable { i = (i == 1 ? 3 : 1); return sum + (c - '0') * i; });

        return !(sum % 10);
    }
}  // namespace tmcppc::problem_14


// Validating ISBNs
// Write a program that validates that 10-digit values entered by the user,
// as a string, represent valid ISBN-10 numbers
void problem_14_main(std::istream& is, std::ostream& os, const console& console) {
    using namespace tmcppc::problem_14;

    auto str = read_n_digit_isbn(is, os, console, 10);
    auto valid = validate_10_digit_isbn(str);
    fmt::print(os, "\t{} {} a valid 10-digit ISBN\n\n", str, (valid ? "is" : "is NOT"));

    str = read_n_digit_isbn(is, os, console, 13);
    valid = validate_13_digit_isbn(str);
    fmt::print(os, "\t{} {} a valid 13-digit ISBN\n\n", str, (valid ? "is" : "is NOT"));
}
