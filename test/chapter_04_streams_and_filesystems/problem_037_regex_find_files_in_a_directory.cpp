#include "chapter_04_streams_and_filesystems/problem_037_regex_find_files_in_a_directory.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_37_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_37_main(oss);
    EXPECT_THAT(oss.str(), ::testing::ContainsRegex(
        "Searching .*res/sample_folder for entries matching pattern .*:\n"
        "\t'.*res/sample_folder/dilbert.jpg'\n"
        "\t'.*res/sample_folder/guinness.jpg'\n"
        "\t'.*res/sample_folder/john_mccarthy.jpg'\n"
        "Searching .*res/sample_folder for entries matching pattern .*:\n"
        "\t'.*res/sample_folder/john_mccarthy.jpg'\n"
        "\t'.*res/sample_folder/multi_page_2.pdf'\n"
        "\t'.*res/sample_folder/multi_page_3.docx'\n"
        "Searching .*res/sample_folder for entries matching pattern .*:\n"
        "\t'.*res/sample_folder/multi_page_2.pdf'\n"
        "\t'.*res/sample_folder/multi_page_3.docx'\n"
        "Searching .*res/sample_subfolder for entries matching pattern .*:\n"
        "\t'.*res/sample_subfolder/use_your_illussion_ii.jpg'\n"
        "Searching .*res/sample_subfolder for entries matching pattern .*:\n"
        "\t'.*res/sample_subfolder/use_your_illussion_ii.jpg'\n"
        "Searching .*res/sample_subfolder for entries matching pattern .*:\n"
    ));
}
