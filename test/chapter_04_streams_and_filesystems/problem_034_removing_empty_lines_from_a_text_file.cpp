#include "chapter_04_streams_and_filesystems/problem_034_removing_empty_lines_from_a_text_file.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_34_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_34_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "blah\n"
    ));
}
