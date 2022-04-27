#include "chapter_06_algorithms_and_data_structures/problem_053_average_rating_of_movies.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_53_main, output) {
    std::ostringstream oss{};
    problem_53_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "Average rating of movies:\n"
        "\tThe Godfather: 8.3\n"
        "\tThe Godfather II: 7.7\n"
        "\tThe Godfather III: 7.4\n"));
}
