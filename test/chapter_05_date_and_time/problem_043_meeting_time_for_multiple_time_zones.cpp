#include "chapter_05_date_and_time/problem_043_meeting_time_for_multiple_time_zones.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_43_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_43_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "blah"
    ));
}

