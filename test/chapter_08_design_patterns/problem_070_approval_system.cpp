#include "chapter_08_design_patterns/problem_070_approval_system.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_70_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_70_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "Before calling set_direct_manager...\n"
        "\tExpense \"Breakfast\" of value 25.00 approved by Avril Haines.\n"
        "\tExpense \"Glasses\" of value 250.00 approved by Avril Haines.\n"
        "\tExpense \"Laptop\" of value 2500.00 wasn't approved.\n"
        "\tExpense \"Car\" of value 25000.00 wasn't approved.\n"
        "\tExpense \"Boat\" of value 250000.00 wasn't approved.\n"
        "\tExpense \"House\" of value 2500000.00 wasn't approved.\n"
        "\n"
        "After calling set_direct_manager...\n"
        "\tExpense \"Breakfast\" of value 25.00 approved by Joe Biden.\n"
        "\tExpense \"Glasses\" of value 250.00 approved by Joe Biden.\n"
        "\tExpense \"Laptop\" of value 2500.00 approved by Joe Biden.\n"
        "\tExpense \"Car\" of value 25000.00 approved by Joe Biden.\n"
        "\tExpense \"Boat\" of value 250000.00 approved by Joe Biden.\n"
        "\tExpense \"House\" of value 2500000.00 approved by Joe Biden.\n"
    ));
}
