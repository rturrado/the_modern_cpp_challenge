#include "chapter_06_algorithms_and_data_structures/problem_050_filtering_a_list_of_phone_numbers.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_50_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_50_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "blah"
    ));
}

