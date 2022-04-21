#include "chapter_06_algorithms_and_data_structures/problem_057_quicksort.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_57_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_57_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "blah"
    ));
}

