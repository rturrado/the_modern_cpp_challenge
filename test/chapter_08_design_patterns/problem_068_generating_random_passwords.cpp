#include "chapter_08_design_patterns/problem_068_generating_random_passwords.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_68_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_68_main(oss);
    EXPECT_THAT(oss.str(), ::testing::ContainsRegex(
        "Creating a password with 2 symbols, 2 digits, 2 lowercase letters, and 2 uppercase letters: ........\n"
    ));
}
