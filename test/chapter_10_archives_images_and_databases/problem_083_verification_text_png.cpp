#include "chapter_10_archives_images_and_databases/problem_083_verification_text_png.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_83_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_83_main(oss);
    EXPECT_THAT(oss.str(), ::testing::ContainsRegex("Creating .*/captcha.png...\n"));
}
