#include "chapter_04_streams_and_filesystems/problem_034_removing_empty_lines_from_a_text_file.h"
#include "env.h"

#include "rtc/filesystem.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream

using namespace rtc::filesystem;
using namespace tmcppc::problem_34;


TEST(remove_empty_lines, DISABLED_in_file_path_does_not_exist) {
    std::ostringstream oss{};
    EXPECT_THROW((void) remove_empty_lines(oss, "this_file_does_not_exist.txt"), file_path_does_not_exist_error);
}
TEST(remove_empty_lines, DISABLED_in_file_path_is_not_a_regular_file) {
    const auto resource_folder_path{ tmcppc::env::get_instance().get_resource_folder_path() };
    std::ostringstream oss{};
    EXPECT_THROW((void) remove_empty_lines(oss, resource_folder_path), file_is_not_regular_error);
}
TEST(remove_empty_lines, DISABLED_valid_in_file_path) {
    const auto resource_folder_path{ tmcppc::env::get_instance().get_resource_folder_path() };
    const auto in_file_path{ resource_folder_path / "problem_034_input.txt" };
    const auto out_file_path{ resource_folder_path / "problem_034_output.txt" };
    std::ostringstream oss{};
    auto ret_file_path{ remove_empty_lines(oss, in_file_path) };
    EXPECT_TRUE(get_text_file_content(ret_file_path) == get_text_file_content(out_file_path));
}


TEST(problem_34_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_34_main(oss);
    EXPECT_THAT(oss.str(), ::testing::ContainsRegex(
        "Removing empty lines from input file '.*res/problem_034_input.txt'\n"
        "And writing the result to output file '.*/problem_034_input.txt'\n\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::Not(::testing::EndsWith("\n\n\n")));
}
