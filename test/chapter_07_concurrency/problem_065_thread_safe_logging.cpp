#include "chapter_07_concurrency/problem_065_thread_safe_logging.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_65_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_65_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "blah"
    ));
}
