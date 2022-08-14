#include "chapter_07_concurrency/problem_063_parallel_minmax_with_async.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <numeric>  // iota
#include <ranges>  // views::iota
#include <sstream>  // ostringstream
#include <vector>

using tmcppc::algorithm::async::parallel_min;
using tmcppc::algorithm::async::parallel_max;


TEST(async_parallel_min, DISABLED_empty_input_range) {
    std::vector<int> v{};
    EXPECT_EQ(parallel_min(v), v.end());
}
TEST(async_parallel_min, DISABLED_zero_thread_pool_size) {
    std::vector<int> v(1000);
    std::iota(v.begin(), v.end(), -500);
    EXPECT_EQ(*parallel_min(v, 0), -500);
}
TEST(async_parallel_min, DISABLED_zero_block_size) {
    std::vector<int> v(1000);
    std::iota(v.begin(), v.end(), -500);
    EXPECT_EQ(*parallel_min(v, 4, 0), -500);
}
TEST(async_parallel_min, DISABLED_rvalue_range) {
    EXPECT_EQ(*parallel_min(std::vector<int>{ -5, -2, 1, 4 }), -5);
}
TEST(async_parallel_min, DISABLED_view) {
    EXPECT_EQ(*parallel_min(std::views::iota(-500, 500)), -500);
}


TEST(async_parallel_max, DISABLED_empty_input_range) {
    std::vector<int> v{};
    EXPECT_EQ(parallel_max(v), v.end());
}
TEST(async_parallel_max, DISABLED_zero_thread_pool_size) {
    std::vector<int> v(1000);
    std::iota(v.begin(), v.end(), -500);
    EXPECT_EQ(*parallel_max(v, 0), 499);
}
TEST(async_parallel_max, DISABLED_zero_block_size) {
    std::vector<int> v(1000);
    std::iota(v.begin(), v.end(), -500);
    EXPECT_EQ(*parallel_max(v, 4, 0), 499);
}
TEST(async_parallel_max, DISABLED_rvalue_range) {
    EXPECT_EQ(*parallel_max(std::vector<int>{ -5, -2, 1, 4 }), 4);
}
TEST(async_parallel_max, DISABLED_view) {
    EXPECT_EQ(*parallel_max(std::views::iota(-500, 500)), 499);
}


TEST(problem_63_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_63_main(oss);
    EXPECT_THAT(oss.str(), ::testing::ContainsRegex("v = \\[.*\\]\n\n"));
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "std::min_element(v) = -10\n"
        "std::min_element(std::execution::par, v) = -10\n"
        "parallel_min (using threads) = -10\n"
        "\n"
        "std::max_element(v) = 9\n"
        "std::max_element(std::execution::par, v) = 9\n"
        "parallel_max (using threads) = 9\n\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::Not(::testing::EndsWith("\n\n\n")));
}
