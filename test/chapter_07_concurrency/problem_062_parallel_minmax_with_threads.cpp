#include "chapter_07_concurrency/problem_062_parallel_minmax_with_threads.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_62_main, DISABLED_output) {
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
        "parallel_max (using threads) = 9\n"
    ));
}
