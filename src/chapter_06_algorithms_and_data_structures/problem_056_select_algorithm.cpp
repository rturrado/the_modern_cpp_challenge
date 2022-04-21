#include "Chapter6_AlgorithmsAndDataStructures.h"
#include "RtcPrint.h"

#include <algorithm>  // transform
#include <format>
#include <iostream>  // cout
#include <iterator>  // back_inserter
#include <ostream>
#include <string>
#include <type_traits>  // invoke_result_t
#include <utility>  // forward
#include <vector>

struct book {
    int id;
    std::string title;
    std::string author;
};

std::ostream& operator<<(std::ostream& os, const book& b)
{
    return os << std::format("[ id = {}, title = {}, author = {} ]", b.id, b.title, b.author);
}

template <typename T, typename F>
requires requires (const T& t, F f) { f(t); }
auto select(const std::vector<T>& v, F&& f)
{
    std::vector<std::invoke_result_t<F, const T&>> ret{};
    std::transform(cbegin(v), cend(v), std::back_inserter(ret), std::forward<F>(f));
    return ret;
}

// Select algorithm
//
// Write a function that, given a range of values and a projection function, transforms each value into a new one
// and returns a new range with the selected values.
// For instance, if you have a type book that has an id, title, and author, and have a range of such book values,
// it should be possible for the function to select only the title of the books.
//
// Here is an example of how the function should be used:
//
//     struct book {
//         int id;
//         std::string title;
//         std::string author;
//     };
//
//     std::vector<book> books {
//         { 101, "The C++ Programming Language", "Bjarne Stroustrup" },
//         { 203, "Effective Modern C++", "Scott Meyers" },
//         { 404, "The Modern C++ Programming Cookbook", "Marius Bancila" }
//     };
//
//     auto titles = select(books, [](const book& b) { return b.title; });
void problem_56_main()
{
    const std::vector<book> books {
        { 101, "The C++ Programming Language", "Bjarne Stroustrup" },
        { 203, "Effective Modern C++", "Scott Meyers" },
        { 404, "The Modern C++ Programming Cookbook", "Marius Bancila" }
    };
    std::cout << "List of books:\n";
    std::cout << "\t" << books << "\n\n";

    auto ids = select(books, [](const book& b) { return b.id; });
    std::cout << "Selecting IDs:\n";
    std::cout << "\t" << ids << "\n\n";

    auto titles = select(books, [](const book& b) { return b.title; });
    std::cout << "Selecting titles:\n";
    std::cout << "\t" << titles << "\n\n";

    auto authors = select(books, [](const book& b) { return b.author; });
    std::cout << "Selecting authors:\n";
    std::cout << "\t" << authors << "\n\n";
}
