#include "chapter_10_archives_images_and_databases/problem_080_zip_compression.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_80_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_80_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "blah"
    ));
}
