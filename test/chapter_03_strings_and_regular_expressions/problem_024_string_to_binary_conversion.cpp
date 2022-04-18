#include "chapter_03_strings_and_regular_expressions/problem_024_string_to_binary_conversion.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_24_main, output) {
    std::ostringstream oss{};
    problem_24_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "Converting string \"BAADf00d\" to vector [0xba, 0xad, 0xf0, 0xd]\n"
        "Converting string \"010203040506\" to vector [0x1, 0x2, 0x3, 0x4, 0x5, 0x6]\n"
        "Converting string \"53CC1\" to vector [0x5, 0x3c, 0xc1]\n"
        "Converting string \"00,FF,23,45\" to vector [0x0, 0xff, 0x23, 0x45]\n"
        "Converting string \"1##dd##87\" to vector [0x1, 0xdd, 0x87]\n"
        "Error: parsing string \"1##dd##87\"."
    ));
}
