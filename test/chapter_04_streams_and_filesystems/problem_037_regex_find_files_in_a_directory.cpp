#include "chapter_04_streams_and_filesystems/problem_037_regex_find_files_in_a_directory.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_37_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_37_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "blah\n"
    ));
}
