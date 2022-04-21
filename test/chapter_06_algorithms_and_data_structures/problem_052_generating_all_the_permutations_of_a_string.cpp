#include "chapter_06_algorithms_and_data_structures/problem_052_generating_all_the_permutations_of_a_string.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_52_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_52_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "blah"
    ));
}

