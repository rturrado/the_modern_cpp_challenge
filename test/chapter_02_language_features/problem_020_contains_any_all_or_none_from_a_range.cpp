#include "chapter_02_language_features/problem_020_contains_any_all_or_none_from_a_range.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <ranges>
#include <sstream>  // ostringstream

using namespace tmcppc::problem_20;


TEST(contains_any, DISABLED_empty_container) { EXPECT_FALSE(contains_any(std::vector<int>{}, 1, 3, 5)); }
TEST(contains_all, DISABLED_empty_container) { EXPECT_FALSE(contains_all(std::vector<int>{}, 1, 3, 5)); }
TEST(contains_none, DISABLED_empty_container) { EXPECT_TRUE(contains_none(std::vector<int>{}, 1, 3, 5)); }

TEST(contains_any, DISABLED_non_empty_container) {
    EXPECT_TRUE(contains_any(std::vector<int>{ 1, 1, 2, 3, 5, 8 }, 1, 3, 5));
}
TEST(contains_all, DISABLED_non_empty_container) {
    EXPECT_TRUE(contains_all(std::vector<int>{ 1, 1, 2, 3, 5, 8 }, 1, 3, 5));
}
TEST(contains_none, DISABLED_non_empty_container) {
    EXPECT_FALSE(contains_none(std::vector<int>{ 1, 1, 2, 3, 5, 8 }, 1, 3, 5));
}

TEST(contains_any, DISABLED_view_of_even_numbers) {
    auto even_numbers{ std::views::iota(0) | std::views::filter([](int i) { return i % 2 == 0; }) };
    auto even_numbers_up_to_5{ even_numbers | std::views::take_while([](auto i) { return i <= 5; }) };
    EXPECT_FALSE(contains_any(even_numbers_up_to_5, 1, 3, 5));
    EXPECT_TRUE(contains_all(even_numbers, 2, 4, 6));
    EXPECT_FALSE(contains_none(even_numbers_up_to_5, 1, 2, 3));
}

TEST(problem_20_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_20_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "Checking std::vector<int> v{1, 2, 3, 4, 5, 6} contains_any of (0, 3, 30)\n"
        "Checking std::array<int, 6> a{1, 2, 3, 4, 5, 6} contains_all of (1, 3, 5, 6)\n"
        "Checking std::list<int> l{1, 2, 3, 4, 5, 6} not contains_none of (0, 6)\n\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::Not(::testing::EndsWith("\n\n\n")));
}
