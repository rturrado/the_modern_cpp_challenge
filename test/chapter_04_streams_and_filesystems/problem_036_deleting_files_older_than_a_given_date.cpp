#include "chapter_04_streams_and_filesystems/problem_036_deleting_files_older_than_a_given_date.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_36_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_36_main(oss);
    EXPECT_THAT(oss.str(), ::testing::ContainsRegex(
        "\\(Not\\) deleting entries older than .* in '.*res/sample_folder':\n"
        "\\(Not\\) deleting entries older than .* in '.*res/sample_folder':\n"
        "\t'.*res/sample_folder/dilbert.jpg'\n"
        "\t'.*res/sample_folder/guinness.jpg'\n"
        "\t'.*res/sample_folder/john_mccarthy.jpg'\n"
        "\t'.*res/sample_folder/multi_page_2.pdf'\n"
        "\t'.*res/sample_folder/multi_page_3.docx'\n"
        "\t'.*res/sample_folder/sample_subfolder/use_your_illussion_ii.jpg'\n"
        "\\(Not\\) deleting entries older than .* in '.*res/sample_subfolder':\n"
        "\\(Not\\) deleting entries older than .* in '.*res/sample_subfolder':\n"
        "\t'.*res/sample_subfolder/use_your_illussion_ii.jpg'\n"
    ));
}
