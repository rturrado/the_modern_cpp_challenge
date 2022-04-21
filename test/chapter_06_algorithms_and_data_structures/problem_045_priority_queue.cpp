#include "chapter_06_algorithms_and_data_structures/problem_045_priority_queue.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_45_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_45_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "blah"
    ));
}
