#include "chapter_08_design_patterns/problem_069_generating_social_security_numbers.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_69_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_69_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "blah"
    ));
}

