#include "chapter_11_cryptography/problem_094_file_signing.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_94_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_94_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "blah"
    ));
}
