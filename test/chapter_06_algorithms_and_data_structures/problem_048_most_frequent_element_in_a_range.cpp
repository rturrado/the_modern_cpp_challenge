#include "chapter_06_algorithms_and_data_structures/problem_048_most_frequent_element_in_a_range.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_48_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_48_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "blah"
    ));
}

