#include "chapter_07_concurrency/problem_063_parallel_minmax_with_async.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_63_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_63_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "blah"
    ));
}
