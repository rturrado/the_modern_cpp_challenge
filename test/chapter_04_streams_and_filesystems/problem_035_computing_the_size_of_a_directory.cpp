#include "chapter_04_streams_and_filesystems/problem_035_computing_the_size_of_a_directory.h"
#include "env.h"

#include "rtc/filesystem.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <sstream>  // ostringstream

using namespace rtc::filesystem;
using namespace tmcppc::problem_35;


TEST(directory_size_in_bytes, in_dir_path_does_not_exist) {
    EXPECT_THROW((void) directory_size_in_bytes("this_directory_does_not_exist.txt"), file_path_does_not_exist_error);
}
 TEST(directory_size_in_bytes, in_dir_path_is_not_a_directory) {
    const auto resource_folder_path{ tmcppc::env::get_instance().get_resource_folder_path() };
    const auto in_path{ resource_folder_path / "sample_file.txt" };
    EXPECT_THROW((void) directory_size_in_bytes(in_path), not_a_directory_error);
}
TEST(directory_size_in_bytes, valid_in_dir_path) {
    const auto resource_folder_path{ tmcppc::env::get_instance().get_resource_folder_path() };
    const auto d_path{ resource_folder_path / "sample_folder" };
    EXPECT_EQ(directory_size_in_bytes(d_path), 374'171);
}
TEST(directory_size_in_bytes, valid_in_dir_path_and_follow_symlinks) {
    const auto resource_folder_path{ tmcppc::env::get_instance().get_resource_folder_path() };
    const auto d_path{ resource_folder_path / "sample_folder" };
    EXPECT_EQ(directory_size_in_bytes(d_path, true), 635'986);
}

TEST(directory_size_in_bytes_to_string, n_0) {
    EXPECT_EQ(directory_size_in_bytes_to_string(0), "0 b");
}
TEST(directory_size_in_bytes_to_string, n_1023) {
    EXPECT_EQ(directory_size_in_bytes_to_string(1023), "1023 b");
}
TEST(directory_size_in_bytes_to_string, n_1024) {
    EXPECT_EQ(directory_size_in_bytes_to_string(1024), "1 KB");
}
TEST(directory_size_in_bytes_to_string, n_1_048_575) {
    EXPECT_EQ(directory_size_in_bytes_to_string(1'048'575), "1023 KB");
}
TEST(directory_size_in_bytes_to_string, n_1_048_576) {
    EXPECT_EQ(directory_size_in_bytes_to_string(1'048'576), "1 MB");
}
TEST(directory_size_in_bytes_to_string, n_1_073_741_823) {
    EXPECT_EQ(directory_size_in_bytes_to_string(1'073'741'823), "1023 MB");
}
TEST(directory_size_in_bytes_to_string, n_1_073_741_824) {
    EXPECT_EQ(directory_size_in_bytes_to_string(1'073'741'824), "1 GB");
}

TEST(problem_35_main, output) {
    std::ostringstream oss{};
    problem_35_main(oss);
    EXPECT_THAT(oss.str(), ::testing::ContainsRegex(
        ".*res/sample_folder: 365 KB\n"
        ".*res/sample_folder \\(following symlinks\\): 621 KB\n"
        ".*res/sample_subfolder: 255 KB\n"
        ".*res/sample_subfolder \\(following symlinks\\): 255 KB\n\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::Not(::testing::EndsWith("\n\n\n")));
}
