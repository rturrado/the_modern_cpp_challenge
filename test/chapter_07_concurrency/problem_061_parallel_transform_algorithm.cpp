#include "chapter_07_concurrency/problem_061_parallel_transform_algorithm.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_61_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_61_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "blah"
    ));
}
