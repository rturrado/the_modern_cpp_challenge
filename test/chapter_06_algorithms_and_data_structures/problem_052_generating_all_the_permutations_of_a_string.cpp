#include "chapter_06_algorithms_and_data_structures/problem_052_generating_all_the_permutations_of_a_string.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_52_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_52_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "All permutations of string: ''\n"
        "\t1) Using recursion:\n"
        "\t\t[]\n"
        "\t2) Not using recursion:\n"
        "\t\t[]\n"
        "\n"
        "All permutations of string: 'n'\n"
        "\t1) Using recursion:\n"
        "\t\t[n]\n"
        "\t2) Not using recursion:\n"
        "\t\t[n]\n"
        "\n"
        "All permutations of string: 'ab'\n"
        "\t1) Using recursion:\n"
        "\t\t[ab, ba]\n"
        "\t2) Not using recursion:\n"
        "\t\t[ab, ba]\n"
        "\n"
        "All permutations of string: 'andy'\n"
        "\t1) Using recursion:\n"
        "\t\t[adny, dany, dnay, dnya, andy, nady, nday, ndya, anyd, nayd, nyad, nyda, adyn, dayn, dyan, dyna, aydn, yadn, ydan, ydna, aynd, yand, ynad, ynda]\n"
        "\t2) Not using recursion:\n"
        "\t\t[adny, adyn, andy, anyd, aydn, aynd, dany, dayn, dnay, dnya, dyan, dyna, nady, nayd, nday, ndya, nyad, nyda, yadn, yand, ydan, ydna, ynad, ynda]\n"
    ));
}
