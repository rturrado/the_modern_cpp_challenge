#include "chapter_05_date_and_time/problem_041_day_of_the_week.h"

#include "rtc/chrono.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <chrono>
#include <sstream>  // ostringstream

namespace ch = std::chrono;
using namespace std::chrono_literals;
using namespace tmcppc::problem_41;


TEST(date_to_weekday, DISABLED_invalid_date) { EXPECT_THROW(date_to_weekday(2022y / 20 / 50), rtc::chrono::invalid_date_error); }
TEST(date_to_weekday, DISABLED_monday) { EXPECT_EQ(date_to_weekday(2022y / 06 / 20), ch::Monday); }
TEST(date_to_weekday, DISABLED_tuesday) { EXPECT_EQ(date_to_weekday(2022y / 06 / 21), ch::Tuesday); }
TEST(date_to_weekday, DISABLED_wednesday) { EXPECT_EQ(date_to_weekday(2022y / 06 / 22), ch::Wednesday); }
TEST(date_to_weekday, DISABLED_thursday) { EXPECT_EQ(date_to_weekday(2022y / 06 / 23), ch::Thursday); }
TEST(date_to_weekday, DISABLED_friday) { EXPECT_EQ(date_to_weekday(2022y / 06 / 24), ch::Friday); }
TEST(date_to_weekday, DISABLED_saturday) { EXPECT_EQ(date_to_weekday(2022y / 06 / 25), ch::Saturday); }
TEST(date_to_weekday, DISABLED_sunday) { EXPECT_EQ(date_to_weekday(2022y / 06 / 26), ch::Sunday); }

TEST(weekday_to_number, DISABLED_monday) { EXPECT_EQ(weekday_to_number(ch::Monday), 1); }
TEST(weekday_to_number, DISABLED_tuesday) { EXPECT_EQ(weekday_to_number(ch::Tuesday), 2); }
TEST(weekday_to_number, DISABLED_wednesday) { EXPECT_EQ(weekday_to_number(ch::Wednesday), 3); }
TEST(weekday_to_number, DISABLED_thursday) { EXPECT_EQ(weekday_to_number(ch::Thursday), 4); }
TEST(weekday_to_number, DISABLED_friday) { EXPECT_EQ(weekday_to_number(ch::Friday), 5); }
TEST(weekday_to_number, DISABLED_saturday) { EXPECT_EQ(weekday_to_number(ch::Saturday), 6); }
TEST(weekday_to_number, DISABLED_sunday) { EXPECT_EQ(weekday_to_number(ch::Sunday), 7); }

TEST(problem_41_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_41_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "1946-08-11 was: 7 (Sun)\n"
        "1952-04-24 was: 4 (Thu)\n"
        "1972-07-09 was: 7 (Sun)\n"
        "1977-05-23 was: 1 (Mon)\n\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::Not(::testing::EndsWith("\n\n\n")));
}
