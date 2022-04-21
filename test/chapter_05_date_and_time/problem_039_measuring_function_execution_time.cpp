#include "chapter_05_date_and_time/problem_039_measuring_function_execution_time.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_39_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_39_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "blah"
    ));
}

