#include "chapter_05_date_and_time/problem_042_day_and_week_of_the_year.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_42_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_42_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "blah"
    ));
}

