#include "chapter_05_date_and_time/problem_040_number_of_days_between_two_dates.h"


#include <date/date.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <rtc/chrono.h>
#include <sstream>  // ostringstream

using namespace date::literals;  // 2012_y
using namespace tmcppc::problem_40;


TEST(difference_in_days, invalid_start_date) {
    EXPECT_THROW(difference_in_days(2012_y / 20 / 50, 2012_y / 6 / 22), rtc::chrono::invalid_date_error);
}
TEST(difference_in_days, invalid_end_date) {
    EXPECT_THROW(difference_in_days(2012_y / 6 / 22, 2012_y / 20 / 50), rtc::chrono::invalid_date_error);
}
TEST(difference_in_days, end_date_is_earlier_than_start_date) {
    EXPECT_EQ(difference_in_days(2012_y / 6 / 29, 2012_y / 6 / 22), -7);
}
TEST(difference_in_days, end_date_is_later_than_start_date) {
    EXPECT_EQ(difference_in_days(2012_y / 6 / 22, 2012_y / 6 / 29), 7);
}
TEST(difference_in_days, same_day) {
    EXPECT_EQ(difference_in_days(2012_y / 6 / 22, 2012_y / 6 / 22), 0);
}
TEST(difference_in_days, leap_year) {
    EXPECT_EQ(difference_in_days(2020_y / 2 / 28, 2020_y / 3 / 1), 2);
}


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
        "Difference (in days): -16194\n\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::Not(::testing::EndsWith("\n\n\n")));
}
