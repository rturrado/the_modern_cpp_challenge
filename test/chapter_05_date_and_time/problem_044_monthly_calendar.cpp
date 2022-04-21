#include "chapter_05_date_and_time/problem_044_monthly_calendar.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_44_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_44_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "blah"
    ));
}

