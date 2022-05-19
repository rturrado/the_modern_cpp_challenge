#include "chapter_10_archives_images_and_databases/problem_082_national_flag_png.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_82_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_82_main(oss);
    EXPECT_THAT(oss.str(), ::testing::ContainsRegex("Creating .*/romania_flag.png..."));
}
