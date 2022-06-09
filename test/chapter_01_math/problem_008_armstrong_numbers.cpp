#include "chapter_01_math/problem_008_armstrong_numbers.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream

using namespace tmcppc::problem_8;


TEST(armstrong_numbers_up_to_a_limit_v1, DISABLED_n_0) {
    EXPECT_THAT(armstrong_numbers_up_to_a_limit_v1(0), ::testing::ElementsAre(0));
}
TEST(armstrong_numbers_up_to_a_limit_v1, DISABLED_n_1) {
    EXPECT_THAT(armstrong_numbers_up_to_a_limit_v1(1), ::testing::ElementsAre(0, 1));
}
TEST(armstrong_numbers_up_to_a_limit_v1, DISABLED_n_1000) {
    EXPECT_THAT(armstrong_numbers_up_to_a_limit_v1(1000), ::testing::ElementsAre(
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 153, 370, 371, 407));
}
TEST(armstrong_numbers_up_to_a_limit_v1, DISABLED_n_5000) {
    EXPECT_THAT(armstrong_numbers_up_to_a_limit_v1(5000), ::testing::ElementsAre(
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 153, 370, 371, 407, 1634));
}


TEST(armstrong_numbers_up_to_a_limit_v2, DISABLED_n_0) {
    EXPECT_THAT(armstrong_numbers_up_to_a_limit_v2(0), ::testing::ElementsAre(0));
}
TEST(armstrong_numbers_up_to_a_limit_v2, DISABLED_n_1) {
    EXPECT_THAT(armstrong_numbers_up_to_a_limit_v2(1), ::testing::ElementsAre(0, 1));
}
TEST(armstrong_numbers_up_to_a_limit_v2, DISABLED_n_1000) {
    EXPECT_THAT(armstrong_numbers_up_to_a_limit_v2(1000), ::testing::ElementsAre(
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 153, 370, 371, 407));
}
TEST(armstrong_numbers_up_to_a_limit_v2, DISABLED_n_5000) {
    EXPECT_THAT(armstrong_numbers_up_to_a_limit_v2(5000), ::testing::ElementsAre(
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 153, 370, 371, 407, 1634));
}


TEST(armstrong_numbers_up_to_a_limit_v3, DISABLED_n_0) {
    EXPECT_THAT(armstrong_numbers_up_to_a_limit_v3(0), ::testing::ElementsAre(0));
}
TEST(armstrong_numbers_up_to_a_limit_v3, DISABLED_n_1) {
    EXPECT_THAT(armstrong_numbers_up_to_a_limit_v3(1), ::testing::ElementsAre(0, 1));
}
TEST(armstrong_numbers_up_to_a_limit_v3, DISABLED_n_1000) {
    EXPECT_THAT(armstrong_numbers_up_to_a_limit_v3(1000), ::testing::ElementsAre(
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 153, 370, 371, 407));
}
TEST(armstrong_numbers_up_to_a_limit_v3, DISABLED_n_5000) {
    EXPECT_THAT(armstrong_numbers_up_to_a_limit_v3(5000), ::testing::ElementsAre(
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 153, 370, 371, 407, 1634));
}


TEST(armstrong_numbers_with_three_digits, DISABLED_n_1000) {
    EXPECT_THAT(armstrong_numbers_with_three_digits(), ::testing::ElementsAre(153, 370, 371, 407));
}

TEST(problem_8_main, DISABLED_n_1000) {
    std::ostringstream oss{};
    problem_8_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "Armstrong numbers with three digits:\n"
        "\t153\n"
        "\t370\n"
        "\t371\n"
        "\t407\n"
    ));
}
