#include "chapter_06_algorithms_and_data_structures/problem_060_game_of_life.h"

#include <chrono>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_60_main, DISABLED_output) {
    using namespace std::chrono_literals;

    std::ostringstream oss{};
    problem_60_main(oss, 1s);
    EXPECT_THAT(oss.str(), ::testing::ContainsRegex("\\s+"));
    EXPECT_THAT(oss.str(), ::testing::ContainsRegex("\\*+"));
    EXPECT_THAT(oss.str(), ::testing::ContainsRegex("\n+"));
}
