#include "chapter_06_algorithms_and_data_structures/problem_056_select_algorithm.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <functional>  // identity
#include <sstream>  // ostringstream
#include <tuple>
#include <vector>

using namespace tmcppc::problem_56;


TEST(select, empty_range) {
    EXPECT_TRUE(select(std::vector<int>{}, std::identity{}).empty());
}
TEST(select, identity) {
    EXPECT_THAT(select(std::vector<int>{ 1, 2, 3 }, std::identity{}), ::testing::ElementsAre(1, 2, 3));
}
TEST(select, square) {
    EXPECT_THAT(select(std::vector<int>{ 1, 2, 3 }, [](int i) { return i * i; }), ::testing::ElementsAre(1, 4, 9));
}
TEST(select, tuple_get_0) {
    EXPECT_THAT(select(std::vector<std::tuple<int, char>>{ { 1, 'a' }, { 2, 'b' } }, [](const auto& t) { return std::get<0>(t); }),
        ::testing::ElementsAre(1, 2));
}


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
        "\t[\"Bjarne Stroustrup\", \"Scott Meyers\", \"Marius Bancila\"]\n\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::Not(::testing::EndsWith("\n\n\n")));
}
