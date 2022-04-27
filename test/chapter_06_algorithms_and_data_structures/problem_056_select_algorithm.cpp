#include "chapter_06_algorithms_and_data_structures/problem_056_select_algorithm.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_56_main, output) {
    std::ostringstream oss{};
    problem_56_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "List of books:\n"
        "\t[(id = 101, title = The C++ Programming Language, author = Bjarne Stroustrup),\n"
        "\t(id = 203, title = Effective Modern C++, author = Scott Meyers),\n"
        "\t(id = 404, title = The Modern C++ Programming Cookbook, author = Marius Bancila)]\n"
        "\n"
        "Selecting IDs:\n"
        "\t[101, 203, 404]\n"
        "\n"
        "Selecting titles:\n"
        "\t[\"The C++ Programming Language\", \"Effective Modern C++\", \"The Modern C++ Programming Cookbook\"]\n"
        "\n"
        "Selecting authors:\n"
        "\t[\"Bjarne Stroustrup\", \"Scott Meyers\", \"Marius Bancila\"]\n"
    ));
}
