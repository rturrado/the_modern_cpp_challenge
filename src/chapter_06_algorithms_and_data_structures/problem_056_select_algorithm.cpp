#include "chapter_06_algorithms_and_data_structures/problem_056_select_algorithm.h"

#include <fmt/ostream.h>
#include <fmt/ranges.h>
#include <iostream>
#include <vector>


void problem_56_main(std::ostream& os) {
    const std::vector<book> books{
        { 101, "The C++ Programming Language", "Bjarne Stroustrup" },
        { 203, "Effective Modern C++", "Scott Meyers" },
        { 404, "The Modern C++ Programming Cookbook", "Marius Bancila" }
    };
    fmt::print(os, "List of books:\n");
    fmt::print(os, "\t[{}]\n\n", fmt::join(books, ",\n\t"));

    const auto ids = select(books, [](const book& b) { return b.id; });
    fmt::print(os, "Selecting IDs:\n");
    fmt::print(os, "\t{}\n\n", ids);

    const auto titles = select(books, [](const book& b) { return b.title; });
    fmt::print(os, "Selecting titles:\n");
    fmt::print(os, "\t{}\n\n", titles);

    const auto authors = select(books, [](const book& b) { return b.author; });
    fmt::print(os, "Selecting authors:\n");
    fmt::print(os, "\t{}\n\n", authors);
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
void problem_56_main() {
    problem_56_main(std::cout);
}
