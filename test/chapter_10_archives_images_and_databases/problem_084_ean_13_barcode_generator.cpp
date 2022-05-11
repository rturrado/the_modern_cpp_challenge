#include "chapter_10_archives_images_and_databases/problem_084_ean_13_barcode_generator.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_84_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_84_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "blah"
    ));
}
