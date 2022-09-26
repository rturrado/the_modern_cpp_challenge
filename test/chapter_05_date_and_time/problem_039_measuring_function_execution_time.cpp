#include "chapter_05_date_and_time/problem_039_measuring_function_execution_time.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <chrono>
#include <sstream>  // ostringstream
#include <thread>  // sleep_for

namespace ch = std::chrono;
using namespace std::chrono_literals;
using namespace tmcppc::problem_39;


TEST(measure_time, f_no_args) {
    auto duration{
        measure_time<ch::milliseconds>(
            []() { std::this_thread::sleep_for(10ms); }
        )
    };
    EXPECT_GT(duration, 5ms);
}
TEST(measure_time, f_args) {
    auto duration{
        measure_time<ch::milliseconds>(
            [](const auto& duration) { std::this_thread::sleep_for(duration); },
            10ms
        )
    };
    EXPECT_GT(duration, 5ms);
}


TEST(problem_39_main, output) {
    std::ostringstream oss{};
    problem_39_main(oss);
    EXPECT_THAT(oss.str(), ::testing::ContainsRegex(
        "Measuring times...\n"
        "\tsort_iota_vector\\(num_elems = 1000000, num_reps = 1\\): .*\n"
        "\tsort_shuffle_vector\\(num_elems = 1000000, num_reps = 1\\): .*\n"
        "\n"
        "\tsort_iota_vector\\(num_elems = 1000, num_reps = 1000\\): .*\n"
        "\tsort_shuffle_vector\\(num_elems = 1000, num_reps = 1000\\): .*\n\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::Not(::testing::EndsWith("\n\n\n")));
}
