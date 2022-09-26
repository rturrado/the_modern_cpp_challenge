#include "chapter_05_date_and_time/problem_042_day_and_week_of_the_year.h"

#include "rtc/chrono.h"

#include "date/date.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <sstream>  // ostringstream

using namespace date::literals;  // 2022_y
using namespace tmcppc::problem_42;


TEST(daynum, invalid_date) { EXPECT_THROW(daynum(2022_y / 20 / 40), rtc::chrono::invalid_date_error); }
TEST(daynum, january_1_2022) { EXPECT_EQ(daynum(2022_y / 1 / 1), 1); }
TEST(daynum, december_31_2022) { EXPECT_EQ(daynum(2022_y / 12 / 31), 365); }

TEST(weeknum, invalid_date) { EXPECT_THROW(weeknum(2022_y / 20 / 40), rtc::chrono::invalid_date_error); }
TEST(weeknum, january_1_2022) { EXPECT_EQ(weeknum(2022_y / 1 / 1), 1); }
TEST(weeknum, december_31_2022) { EXPECT_EQ(weeknum(2022_y / 12 / 31), 53); }

TEST(problem_42_main, output) {
    std::ostringstream oss{};
    problem_42_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "Date\t\tDay number\tWeek number\n"
        "2020-12-31\t366\t\t53\n"
        "2021-12-31\t365\t\t53\n"
        "2022-01-07\t7\t\t2\n"
        "2022-01-08\t8\t\t2\n"
        "2014-09-28\t271\t\t39\n"
        "2012-04-05\t96\t\t15\n"
        "\n"
        "2012-02-24\t55\t\t9\n"
        "2012-02-25\t56\t\t9\n"
        "2012-02-26\t57\t\t9\n"
        "2012-02-27\t58\t\t10\n"
        "2012-02-28\t59\t\t10\n"
        "2012-02-29\t60\t\t10\n"
        "2012-03-01\t61\t\t10\n"
        "2012-03-02\t62\t\t10\n"
        "2012-03-03\t63\t\t10\n"
        "2012-03-04\t64\t\t10\n"
        "2012-03-05\t65\t\t11\n\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::Not(::testing::EndsWith("\n\n\n")));
}
