#include "chapter_05_date_and_time/problem_044_monthly_calendar.h"

#include <date/date.h>  // 2022_y
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <rtc/chrono.h>
#include <sstream>  // ostringstream

using namespace date::literals;
using namespace tmcppc::problem_44;


TEST(print_calendar_month, invalid_month) {
    std::ostringstream oss{};
    EXPECT_THROW(print_calendar_month(oss, 2022_y, date::month{ 20 }), rtc::chrono::invalid_month_error);
}


TEST(print_calendar_month, january_1970) {
    std::ostringstream oss{};
    print_calendar_month(oss, 1970_y, date::month{ 1 });
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "1970/Jan\n"
        " Mon Tue Wed Thu Fri Sat Sun\n"
        "               1   2   3   4\n"
        "   5   6   7   8   9  10  11\n"
        "  12  13  14  15  16  17  18\n"
        "  19  20  21  22  23  24  25\n"
        "  26  27  28  29  30  31"
    ));
}


TEST(problem_44_main, output) {
    std::ostringstream oss{};
    problem_44_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "1970/Jan\n"
        " Mon Tue Wed Thu Fri Sat Sun\n"
        "               1   2   3   4\n"
        "   5   6   7   8   9  10  11\n"
        "  12  13  14  15  16  17  18\n"
        "  19  20  21  22  23  24  25\n"
        "  26  27  28  29  30  31\n"
        "\n"
        "1977/May\n"
        " Mon Tue Wed Thu Fri Sat Sun\n"
        "                           1\n"
        "   2   3   4   5   6   7   8\n"
        "   9  10  11  12  13  14  15\n"
        "  16  17  18  19  20  21  22\n"
        "  23  24  25  26  27  28  29\n"
        "  30  31\n"
        "\n"
        "2012/Feb\n"
        " Mon Tue Wed Thu Fri Sat Sun\n"
        "           1   2   3   4   5\n"
        "   6   7   8   9  10  11  12\n"
        "  13  14  15  16  17  18  19\n"
        "  20  21  22  23  24  25  26\n"
        "  27  28  29\n\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::Not(::testing::EndsWith("\n\n\n")));
}
