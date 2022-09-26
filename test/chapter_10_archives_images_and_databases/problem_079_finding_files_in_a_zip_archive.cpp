#include "chapter_10_archives_images_and_databases/problem_079_finding_files_in_a_zip_archive.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <sstream>  // ostringstream


TEST(problem_79_main, output) {
    std::ostringstream oss{};
    problem_79_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "Searching for '^.*\\.jpg$' files in "
    ));
    EXPECT_THAT(oss.str(), ::testing::ContainsRegex(
        "'.*/res/sample_folder.zip'...\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "\tsample_folder/dilbert.jpg\n"
        "\tsample_folder/guinness.jpg\n"
        "\tsample_folder/john_mccarthy.jpg\n"
        "\tsample_folder/sample_subfolder/use_your_illussion_ii.jpg\n\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::Not(::testing::EndsWith("\n\n\n")));
}
