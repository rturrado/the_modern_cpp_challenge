#include "chapter_10_archives_images_and_databases/problem_084_ean_13_barcode_generator.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_84_main, output) {
    std::ostringstream oss{};
    problem_84_main(oss);
    EXPECT_THAT(oss.str(), ::testing::ContainsRegex(
        "Creating .*/2407014001944.png...\n\n"
        "Creating .*/9781123123456.png...\n\n"
        "Creating .*/5012345678900.png...\n\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::Not(::testing::EndsWith("\n\n\n")));
}
