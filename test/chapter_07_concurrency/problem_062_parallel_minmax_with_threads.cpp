#include "chapter_07_concurrency/problem_062_parallel_minmax_with_threads.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <numeric>  // iota
#include <ranges>  // views::iota
#include <vector>

using tmcppc::algorithm::thread::parallel_min;
using tmcppc::algorithm::thread::parallel_max;


TEST(thread_parallel_min, empty_input_range) {
    std::vector<int> v{};
    EXPECT_EQ(parallel_min(v), v.end());
}
TEST(thread_parallel_min, zero_thread_pool_size) {
    std::vector<int> v(1000);
    std::iota(v.begin(), v.end(), -500);
    EXPECT_EQ(*parallel_min(v, 0), -500);
}
TEST(thread_parallel_min, zero_block_size) {
    std::vector<int> v(1000);
    std::iota(v.begin(), v.end(), -500);
    EXPECT_EQ(*parallel_min(v, 4, 0), -500);
}
TEST(thread_parallel_min, rvalue_range) {
    EXPECT_EQ(*parallel_min(std::vector<int>{ -5, -2, 1, 4 }), -5);
}
TEST(thread_parallel_min, view) {
    EXPECT_EQ(*parallel_min(std::views::iota(-500, 500)), -500);
}


TEST(thread_parallel_max, empty_input_range) {
    std::vector<int> v{};
    EXPECT_EQ(parallel_max(v), v.end());
}
TEST(thread_parallel_max, zero_thread_pool_size) {
    std::vector<int> v(1000);
    std::iota(v.begin(), v.end(), -500);
    EXPECT_EQ(*parallel_max(v, 0), 499);
}
TEST(thread_parallel_max, zero_block_size) {
    std::vector<int> v(1000);
    std::iota(v.begin(), v.end(), -500);
    EXPECT_EQ(*parallel_max(v, 4, 0), 499);
}
TEST(thread_parallel_max, rvalue_range) {
    EXPECT_EQ(*parallel_max(std::vector<int>{ -5, -2, 1, 4 }), 4);
}
TEST(thread_parallel_max, view) {
    EXPECT_EQ(*parallel_max(std::views::iota(-500, 500)), 499);
}


TEST(problem_62_main, output) {
    std::ostringstream oss{};
    problem_62_main(oss);
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
