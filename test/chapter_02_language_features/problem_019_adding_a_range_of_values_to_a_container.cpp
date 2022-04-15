#include "chapter_02_language_features/problem_019_adding_a_range_of_values_to_a_container.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_19_main, output) {
    std::ostringstream oss{};
    problem_19_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "Adding 10, 20, and 30 to an empty vector of ints: [10, 20, 30]\n"
        "Adding \"Hey\", \"Joe!\", and \"Voodoo\" to an empty vector of strings: [\"Hey\", \"Joe!\", \"Voodoo\"]\n"
        "Adding 3.14f, 0.99f, and -273.0f ot an empty list of floats: [3.14, 0.99, -273]\n"
    ));
}
