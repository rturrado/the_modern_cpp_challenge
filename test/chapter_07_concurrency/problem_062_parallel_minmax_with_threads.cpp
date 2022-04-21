#include "chapter_07_concurrency/problem_062_parallel_minmax_with_threads.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_62_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_62_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "blah"
    ));
}
