#include "chapter_09_data_serialization/problem_073_xml_serialization.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <sstream>  // ostringstream


TEST(problem_73_main, output) {
    std::ostringstream oss{};
    problem_73_main(oss);
    EXPECT_THAT(oss.str(), ::testing::ContainsRegex(
        "Writing XML out to: .*/list_of_movies.xml\n"
        "Reading XML in from: .*/list_of_movies.xml\n"
        "\n"
        "Checking if serializing and deserializing the XML object created the same object... OK\n\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::Not(::testing::EndsWith("\n\n\n")));
}
