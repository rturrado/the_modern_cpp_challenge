#include "chapter_07_concurrency/problem_064_parallel_sort_algorithm.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <sstream>  // ostringstream


TEST(problem_64_main, output) {
    std::ostringstream oss{};
    problem_64_main(oss);
    EXPECT_THAT(oss.str(), ::testing::ContainsRegex("v = \\[.*\\]\n\n"));
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "std::sort(v); v = [-10, -9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9]\n"
        "quicksort(v); v = [-10, -9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9]\n"
        "parallel_quicksort; v = [-10, -9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9]\n\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::Not(::testing::EndsWith("\n\n\n")));
}
