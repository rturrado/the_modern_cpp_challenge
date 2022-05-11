#include "chapter_10_archives_images_and_databases/problem_079_finding_files_in_a_zip_archive.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_79_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_79_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "blah"
    ));
}
