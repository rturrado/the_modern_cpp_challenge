#include "chapter_04_streams_and_filesystems/problem_037_regex_find_files_in_a_directory.h"
#include "env.h"

#include "rtc/filesystem.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <filesystem>
#include <regex>  // regex_error
#include <sstream>  // ostringstream

using namespace rtc::filesystem;
using namespace tmcppc::problem_37;


TEST(get_directory_entries_matching, DISABLED_in_dir_path_does_not_exist) {
    EXPECT_THROW(get_directory_entries_matching("this_directory_does_not_exist.txt", ".*"),
        file_path_does_not_exist_error);
}
TEST(get_directory_entries_matching, DISABLED_in_dir_path_is_not_a_directory) {
    const auto resource_folder_path{ tmcppc::env::get_instance().get_resource_folder_path() };
    const auto in_file_path{ resource_folder_path / "sample_file.txt" };
    EXPECT_THROW((void) get_directory_entries_matching(in_file_path, ".*"),
        not_a_directory_error);
}
TEST(get_directory_entries_matching, DISABLED_invalid_regex) {
    const auto resource_folder_path{ tmcppc::env::get_instance().get_resource_folder_path() };
    const auto in_file_path{ resource_folder_path / "sample_folder" };
    EXPECT_THROW( get_directory_entries_matching(in_file_path, "("), std::regex_error);
}
TEST(get_directory_entries_matching, DISABLED_valid_in_dir_path) {
    const auto resource_folder_path{ tmcppc::env::get_instance().get_resource_folder_path() };
    const auto in_file_path{ resource_folder_path / "sample_folder" };
    auto result{ get_directory_entries_matching(in_file_path, R"(.*\.jpg$)") };
    EXPECT_EQ(result.size(), 3);
    EXPECT_THAT(result[0].path().generic_string(), ::testing::ContainsRegex(".*res/sample_folder/dilbert.jpg"));
    EXPECT_THAT(result[1].path().generic_string(), ::testing::ContainsRegex(".*res/sample_folder/guinness.jpg"));
    EXPECT_THAT(result[2].path().generic_string(), ::testing::ContainsRegex(".*res/sample_folder/john_mccarthy.jpg"));
}

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
        "Searching .*res/sample_subfolder for entries matching pattern .*:\n\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::Not(::testing::EndsWith("\n\n\n")));
}
