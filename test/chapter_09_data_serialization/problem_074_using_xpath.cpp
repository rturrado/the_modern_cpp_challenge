#include "chapter_09_data_serialization/problem_074_using_xpath.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_74_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_74_main(oss);
    EXPECT_THAT(oss.str(), ::testing::ContainsRegex(
        "Writing XML out to: .*/list_of_movies.xml\n"
        "Reading XML in from: .*/list_of_movies.xml\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "Checking if serializing and deserializing the XML object created the same object... OK\n"
        "\n"
        "Movies released after year: 1992\n"
        "\tThe Matrix: 1999\n"
        "\tForrest Gump: 1994\n"
        "Movies released after year: 1996\n"
        "\tThe Matrix: 1999\n"
        "Movies released after year: 2000\n"
        "\n"
        "Last actor in the casting list for every movie:\n"
        "\tThe Matrix: Hugo Weaving\n"
        "\tForrest Gump: Mykelti Williamson\n"
    ));
}
