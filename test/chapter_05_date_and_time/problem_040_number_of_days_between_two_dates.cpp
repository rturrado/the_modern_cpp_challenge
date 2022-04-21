#include "chapter_05_date_and_time/problem_040_number_of_days_between_two_dates.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_40_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_40_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "blah"
    ));
}

