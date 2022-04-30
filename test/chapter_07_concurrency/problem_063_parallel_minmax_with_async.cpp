#include "chapter_07_concurrency/problem_063_parallel_minmax_with_async.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


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
        "parallel_max (using threads) = 9\n"
    ));
}
