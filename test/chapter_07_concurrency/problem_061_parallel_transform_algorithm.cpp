#include "chapter_07_concurrency/problem_061_parallel_transform_algorithm.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_61_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_61_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "v = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]\n"
        "\n"
        "std::transform(v); v = [0, 1, 4, 9, 16, 25, 36, 49, 64, 81]\n"
        "std::transform(std::execution::par, v); v = [0, 1, 4, 9, 16, 25, 36, 49, 64, 81]\n"
        "parallel_transform(v); v = [0, 1, 4, 9, 16, 25, 36, 49, 64, 81]\n"
    ));
}
