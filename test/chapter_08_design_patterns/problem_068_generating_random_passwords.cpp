#include "chapter_08_design_patterns/problem_068_generating_random_passwords.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_68_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_68_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "blah"
    ));
}

