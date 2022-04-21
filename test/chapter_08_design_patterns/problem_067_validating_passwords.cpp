#include "chapter_08_design_patterns/problem_067_validating_passwords.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_67_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_67_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "blah"
    ));
}

