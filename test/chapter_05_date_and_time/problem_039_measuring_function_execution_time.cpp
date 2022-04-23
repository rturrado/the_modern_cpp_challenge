#include "chapter_05_date_and_time/problem_039_measuring_function_execution_time.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_39_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_39_main(oss);
    EXPECT_THAT(oss.str(), ::testing::ContainsRegex(
        "Measuring times...\n"
        "\tsort_iota_vector\\(num_elems = 1000000, num_reps = 1\\): .*\n"
        "\tsort_shuffle_vector\\(num_elems = 1000000, num_reps = 1\\): .*\n"
        "\n"
        "\tsort_iota_vector\\(num_elems = 1000, num_reps = 1000\\): .*\n"
        "\tsort_shuffle_vector\\(num_elems = 1000, num_reps = 1000\\): .*\n"
    ));
}
