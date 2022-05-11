#include "chapter_11_cryptography/problem_091_validating_user_credentials.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_91_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_91_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "blah"
    ));
}
