#include "chapter_06_algorithms_and_data_structures/problem_054_pairwise_algorithm.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_54_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_54_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "Zipping [1, 1, 2, 3, 5, 8] with next: [(1, 1), (2, 3), (5, 8)]\n"
        "Zipping [1, 1, 2, 3, 5, 8, 13] with next: [(1, 1), (2, 3), (5, 8)]\n"
    ));
}
