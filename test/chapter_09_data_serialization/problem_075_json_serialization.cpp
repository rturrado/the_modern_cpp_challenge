#include "chapter_09_data_serialization/problem_075_json_serialization.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_75_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_75_main(oss);
    EXPECT_THAT(oss.str(), ::testing::ContainsRegex(
        "Writing JSON out to: .*/list_of_movies.json\n"
        "Reading JSON in from: .*/list_of_movies.json\n"
        "\n"
        "Checking if serializing and deserializing the JSON object created the same object... OK\n\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::Not(::testing::EndsWith("\n\n\n")));
}
