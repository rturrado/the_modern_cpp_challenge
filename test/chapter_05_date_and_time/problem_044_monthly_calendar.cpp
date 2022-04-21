#include "chapter_05_date_and_time/problem_044_monthly_calendar.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


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
        "  27  28  29\n"
    ));
}
