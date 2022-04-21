#include "chapter_05_date_and_time/problem_042_day_and_week_of_the_year.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


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
        "2012-03-05\t65\t\t11\n"
    ));
}
