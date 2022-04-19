#include "chapter_04_streams_and_filesystems/problem_033_tabular_printing_of_a_list_of_processes.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_33_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_33_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "blah\n"
    ));
}
