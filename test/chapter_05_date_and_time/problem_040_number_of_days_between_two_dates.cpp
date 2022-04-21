#include "chapter_05_date_and_time/problem_040_number_of_days_between_two_dates.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_40_main, output) {
    std::ostringstream oss{};
    problem_40_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "First day: 2012-01-24\n"
        "Second day: 2013-01-08\n"
        "Difference (in days): 350\n"
        "\n"
        "First day: 2013-01-08\n"
        "Second day: 2012-01-24\n"
        "Difference (in days): -350\n"
        "\n"
        "First day: 1977-05-23\n"
        "Second day: 2021-09-23\n"
        "Difference (in days): 16194\n"
        "\n"
        "First day: 2021-09-23\n"
        "Second day: 1977-05-23\n"
        "Difference (in days): -16194\n"
    ));
}
