#include "chapter_04_streams_and_filesystems/problem_032_pascal_triangle.h"

#include <exception>
#include <fmt/ostream.h>
#include <fmt/ranges.h>
#include <functional>  // plus
#include <iostream>  // cout
#include <numeric>  // adjacent_difference
#include <ostream>
#include <stdexcept>  // out_of_range
#include <string>  // to_string
#include <vector>


std::vector<std::vector<uint32_t>> pascal_triangle(const size_t n) {
    if (n > 30) {
        throw std::out_of_range{ std::string{"calling pascal_triangle with n > 30, n = "} + std::to_string(n) };
    }

    std::vector<std::vector<uint32_t>> ret{};

    if (n == 0) {
        return ret;
    }

    ret.push_back({ 1 });
    if (n == 1) {
        return ret;
    }

    ret.push_back({ 1, 1 });
    if (n == 2) {
        return ret;
    }

    for (size_t i{ 2 }; i < n; ++i) {  // n > 2
        std::vector<uint32_t> row(i + 1, 1);
        std::adjacent_difference(cbegin(ret[i - 1]), cend(ret[i - 1]), begin(row), std::plus<>{});
        ret.push_back(row);
    }
    return ret;
}


void problem_32_main(std::ostream& os) {
    for (size_t n : { 0, 1, 2, 10, 40 }) {
        try {
            fmt::print(os, "Pascal triangle for n = {}:\n", n);
            auto ret{ pascal_triangle(n) };
            fmt::print(os, "\t{}\n", ret.empty() ? "[]" : fmt::format("{}", fmt::join(ret, "\n\t")));
        } catch (const std::exception& err) {
            fmt::print(os, "\tError: {}\n", err.what());
        }
    }
    fmt::print(os, "\n");
}


// Pascal's triangle
//
// Write a function that prints up to 10 rows of Pascal's triangle to the console
void problem_32_main() {
    problem_32_main(std::cout);
}
