#include "chapter_06_algorithms_and_data_structures/problem_059_weasel_program.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_59_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_59_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "blah"
    ));
}

