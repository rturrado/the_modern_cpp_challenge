#include "chapter_05_date_and_time/problem_041_day_of_the_week.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_41_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_41_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "1946-08-11 was: 7 (Sun)\n"
        "1952-04-24 was: 4 (Thu)\n"
        "1972-07-09 was: 7 (Sun)\n"
        "1977-05-23 was: 1 (Mon)\n"
    ));
}
