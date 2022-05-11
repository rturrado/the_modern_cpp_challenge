#include "chapter_11_cryptography/problem_093_aes_encryption.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_93_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_93_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "blah"
    ));
}
