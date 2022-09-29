#include "chapter_06_algorithms_and_data_structures/problem_052_generating_all_the_permutations_of_a_string.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace tmcppc::problem_52;


TEST(all_permutations, empty_string) { EXPECT_TRUE(all_permutations("").empty()); }
TEST(all_permutations, one_character_string) { EXPECT_THAT(all_permutations("n"), ::testing::ElementsAre("n")); }
TEST(all_permutations, two_character_string) { EXPECT_THAT(all_permutations("ab"), ::testing::UnorderedElementsAre(
    "ab", "ba"));
}
TEST(all_permutations, four_character_string) { EXPECT_THAT(all_permutations("andy"), ::testing::UnorderedElementsAre(
        "adny", "dany", "dnay", "dnya", "andy", "nady", "nday", "ndya", "anyd", "nayd", "nyad", "nyda",
        "adyn", "dayn", "dyan", "dyna", "aydn", "yadn", "ydan", "ydna", "aynd", "yand", "ynad", "ynda"
    ));
}


TEST(all_permutations_rec, empty_string) { EXPECT_TRUE(all_permutations_rec("").empty()); }
TEST(all_permutations_rec, one_character_string) { EXPECT_THAT(all_permutations_rec("n"), ::testing::ElementsAre("n")); }
TEST(all_permutations_rec, two_character_string) { EXPECT_THAT(all_permutations_rec("ab"), ::testing::UnorderedElementsAre(
        "ab", "ba"));
}
TEST(all_permutations_rec, four_character_string) { EXPECT_THAT(all_permutations_rec("andy"), ::testing::UnorderedElementsAre(
        "adny", "dany", "dnay", "dnya", "andy", "nady", "nday", "ndya", "anyd", "nayd", "nyad", "nyda",
        "adyn", "dayn", "dyan", "dyna", "aydn", "yadn", "ydan", "ydna", "aynd", "yand", "ynad", "ynda"
    ));
}


TEST(problem_52_main, output) {
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
        "\t\t[adny, dany, dnay, dnya, andy, nady, nday, ndya, anyd, nayd, nyad, nyda, "
        "adyn, dayn, dyan, dyna, aydn, yadn, ydan, ydna, aynd, yand, ynad, ynda]\n"
        "\t2) Not using recursion:\n"
        "\t\t[adny, adyn, andy, anyd, aydn, aynd, dany, dayn, dnay, dnya, dyan, dyna, "
        "nady, nayd, nday, ndya, nyad, nyda, yadn, yand, ydan, ydna, ynad, ynda]\n\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::Not(::testing::EndsWith("\n\n\n")));
}
