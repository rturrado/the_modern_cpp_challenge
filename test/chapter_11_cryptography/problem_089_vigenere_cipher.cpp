#include "chapter_11_cryptography/problem_089_vigenere_cipher.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_89_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_89_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "blah"
    ));
}
