#include "chapter_06_algorithms_and_data_structures/problem_060_game_of_life.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_60_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_60_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "blah"
    ));
}

