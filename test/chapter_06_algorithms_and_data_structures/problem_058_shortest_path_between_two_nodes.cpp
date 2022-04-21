#include "chapter_06_algorithms_and_data_structures/problem_058_shortest_path_between_two_nodes.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_58_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_58_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "blah"
    ));
}

