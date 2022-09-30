#include "chapter_04_streams_and_filesystems/problem_036_deleting_files_older_than_a_given_date.h"
#include "env.h"

#include <chrono>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <rtc/filesystem.h>
#include <sstream>  // ostringstream

namespace ch = std::chrono;
using namespace rtc::filesystem;
using namespace std::chrono_literals;
using namespace tmcppc::problem_36;


TEST(delete_directory_entries_older_than, in_dir_path_does_not_exist) {
    std::ostringstream oss{};
    const auto in_dir_path{ "this_directory_does_not_exist.txt" };
    EXPECT_THROW(delete_directory_entries_older_than(oss, in_dir_path, ch::file_clock::now()),
        file_path_does_not_exist_error);
}
TEST(delete_directory_entries_older_than, in_dir_path_is_not_a_directory) {
    std::ostringstream oss{};
    const auto resource_folder_path{ tmcppc::env::get_instance().get_resource_folder_path() };
    const auto in_dir_path{ resource_folder_path / "sample_file.txt" };
    EXPECT_THROW(delete_directory_entries_older_than(oss, in_dir_path, ch::file_clock::now()),
        not_a_directory_error);
}
TEST(delete_directory_entries_older_than, now) {
    std::ostringstream oss{};
    const auto resource_folder_path{ tmcppc::env::get_instance().get_resource_folder_path() };
    const auto in_dir_path{ resource_folder_path / "sample_folder" };
    delete_directory_entries_older_than(oss, in_dir_path, ch::file_clock::now());
    EXPECT_THAT(oss.str(), ::testing::ContainsRegex(
        "\t'.*res/sample_folder/dilbert.jpg'\n"
        "\t'.*res/sample_folder/guinness.jpg'\n"
        "\t'.*res/sample_folder/john_mccarthy.jpg'\n"
        "\t'.*res/sample_folder/multi_page_2.pdf'\n"
        "\t'.*res/sample_folder/multi_page_3.docx'\n"
        "\t'.*res/sample_folder/sample_subfolder/use_your_illussion_ii.jpg'\n"
    ));
}
TEST(delete_directory_entries_older_than, january_1_1970) {
    std::ostringstream oss{};
    const auto resource_folder_path{ tmcppc::env::get_instance().get_resource_folder_path() };
    const auto in_dir_path{ resource_folder_path / "sample_folder" };
    const auto tp_sc_1970_jan_01{ ch::sys_days{ 1970y / ch::January / 1 } };
    const auto tp_fc_1970_jan_01{ ch::clock_cast<ch::file_clock>(ch::round<ch::seconds>(tp_sc_1970_jan_01)) };
    delete_directory_entries_older_than(oss, in_dir_path, tp_fc_1970_jan_01);
    EXPECT_TRUE(oss.str().empty());
}

TEST(problem_36_main, output) {
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
        "\t'.*res/sample_subfolder/use_your_illussion_ii.jpg'\n\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::Not(::testing::EndsWith("\n\n\n")));
}
