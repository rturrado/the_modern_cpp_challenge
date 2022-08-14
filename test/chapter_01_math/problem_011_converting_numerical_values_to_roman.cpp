#include "chapter_01_math/problem_011_converting_numerical_values_to_roman.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // istringstream, ostringstream


TEST(problem_11_main, DISABLED_n_2022) {
    std::istringstream iss{ "2022\n" };
    std::ostringstream oss{};
    problem_11_main(iss, oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "Number\tRoman numeral equivalent\n"
        "2022\tMMXXII\n\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::Not(::testing::EndsWith("\n\n\n")));
}
