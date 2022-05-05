#include "chapter_08_design_patterns/problem_069_generating_social_security_numbers.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_69_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_69_main(oss);
    EXPECT_THAT(oss.str(), ::testing::ContainsRegex(
        "SSNs for \\[Female, 1970/Jan/01\\]: Northerian = ..............., and Southerian = ..............\n"
        "SSNs for \\[Female, 1976/Feb/03\\]: Northerian = ..............., and Southerian = ..............\n"
        "SSNs for \\[Female, 1982/Mar/05\\]: Northerian = ..............., and Southerian = ..............\n"
        "SSNs for \\[Female, 1988/May/08\\]: Northerian = ..............., and Southerian = ..............\n"
        "SSNs for \\[Female, 1994/Jul/11\\]: Northerian = ..............., and Southerian = ..............\n"
        "SSNs for \\[  Male, 2000/Aug/14\\]: Northerian = ..............., and Southerian = ..............\n"
        "SSNs for \\[  Male, 2006/Sep/18\\]: Northerian = ..............., and Southerian = ..............\n"
        "SSNs for \\[  Male, 2012/Oct/22\\]: Northerian = ..............., and Southerian = ..............\n"
        "SSNs for \\[  Male, 2018/Nov/26\\]: Northerian = ..............., and Southerian = ..............\n"
        "SSNs for \\[  Male, 2021/Dec/31\\]: Northerian = ..............., and Southerian = ..............\n"
    ));
}
