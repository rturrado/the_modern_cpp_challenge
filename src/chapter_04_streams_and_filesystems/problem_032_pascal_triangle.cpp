#include "chapter_04_streams_and_filesystems/problem_032_pascal_triangle.h"
#include "rtc/print.h"

#include <exception>
#include <iostream>  // cout
#include <functional>  // plus
#include <numeric>  // adjacent_difference
#include <stdexcept>  // out_of_range
#include <string>  // to_string
#include <vector>

using namespace rtc::print;


std::vector<std::vector<uint32_t>> pascal_triangle(const size_t n)
{
    if (n > 30)
    {
        throw std::out_of_range{ std::string{"calling pascal_triangle with n > 30, n = "} + std::to_string(n) };
    }

    std::vector<std::vector<uint32_t>> ret{};
    
    if (n == 0) { return ret; }  // n == 0
    
    ret.push_back({ 1 }); if (n == 1) { return ret; }  // n == 1

    ret.push_back({ 1, 1 }); if (n == 2) { return ret; }  // n == 2

    for (size_t i{ 2 }; i < n; ++i)  // n > 2
    {
        std::vector<uint32_t> row(i + 1, 1);
        std::adjacent_difference(cbegin(ret[i - 1]), cend(ret[i - 1]), begin(row), std::plus<>{});
        ret.push_back(row);
    }
    return ret;
}


// Pascal's triangle
//
// Write a function that prints up to 10 rows of Pascal's triangle to the console
void problem_32_main()
{
    for (size_t n : { 0, 1, 2, 10, 40 })
    {
        try
        {
            std::cout << "Pascal triangle for n=" << n << "\n";

            for (const auto& v : pascal_triangle(n))
            {
                std::cout << "\t" << v << "\n";
            }
        }
        catch (const std::exception& err)
        {
            std::cout << "\tError: " << err.what() << "\n";
        }
    }
    std::cout << "\n";
}
