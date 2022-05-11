#include "chapter_10_archives_images_and_databases/problem_081_zip_compression_with_password.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_81_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_81_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "blah"
    ));
}
