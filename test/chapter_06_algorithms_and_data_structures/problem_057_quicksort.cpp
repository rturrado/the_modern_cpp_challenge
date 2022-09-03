#include "chapter_06_algorithms_and_data_structures/problem_057_quicksort.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_57_main, output) {
    std::ostringstream oss{};
    problem_57_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "Quicksorting [z, A, 9, !, m, o, N, 9]: [!, 9, 9, A, N, m, o, z]\n"
        "Quicksorting [10, 15, 20, 25, 30, 35, 40]: [40, 30, 20, 10, 35, 25, 15]\n\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::Not(::testing::EndsWith("\n\n\n")));
}
