#include "chapter_04_streams_and_filesystems/problem_035_computing_the_size_of_a_directory.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_35_main, output) {
    std::ostringstream oss{};
    problem_35_main(oss);
    EXPECT_THAT(oss.str(), ::testing::ContainsRegex(
        ".*res/sample_folder: 365.40 KB\n"
        ".*res/sample_folder \\(following symlinks\\): 621.08 KB\n"
        ".*res/sample_subfolder: 255.68 KB\n"
        ".*res/sample_subfolder \\(following symlinks\\): 255.68 KB\n"
    ));
}


