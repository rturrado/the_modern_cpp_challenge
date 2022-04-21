#include "chapter_07_concurrency/problem_064_parallel_sort_algorithm.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_64_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_64_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "blah"
    ));
}
