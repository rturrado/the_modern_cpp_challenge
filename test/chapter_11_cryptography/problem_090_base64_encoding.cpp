#include "chapter_11_cryptography/problem_090_base64_encoding.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_90_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_90_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "blah"
    ));
}
