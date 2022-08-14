#include "chapter_09_data_serialization/problem_076_json_deserialization.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_76_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_76_main(oss);
    EXPECT_THAT(oss.str(), ::testing::ContainsRegex(
        "Writing JSON out to: .*/list_of_movies.json\n"
        "Reading JSON in from: .*/list_of_movies.json\n"
        "\n"
        "Checking if serializing and deserializing the JSON object created the same object... OK\n\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::Not(::testing::EndsWith("\n\n\n")));
}
