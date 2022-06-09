#include "chapter_01_math/problem_010_gray_code.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream

using namespace tmcppc::problem_10;


TEST(binary_to_gray, DISABLED_n_0) { EXPECT_EQ(binary_to_gray(0), 0); }
TEST(binary_to_gray, DISABLED_n_10) { EXPECT_EQ(binary_to_gray(10), 15); }
TEST(binary_to_gray, DISABLED_n_20) { EXPECT_EQ(binary_to_gray(20), 30); }
TEST(binary_to_gray, DISABLED_n_31) { EXPECT_EQ(binary_to_gray(31), 16); }


TEST(gray_to_binary, DISABLED_n_0) { EXPECT_EQ(gray_to_binary(0), 0); }
TEST(gray_to_binary, DISABLED_n_10) { EXPECT_EQ(gray_to_binary(10), 12); }
TEST(gray_to_binary, DISABLED_n_20) { EXPECT_EQ(gray_to_binary(20), 24); }
TEST(gray_to_binary, DISABLED_n_31) { EXPECT_EQ(gray_to_binary(31), 21); }


TEST(problem_10_main, DISABLED_5_bit_numbers) {
    std::ostringstream oss{};
    problem_10_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "Number\tBinary\tGray code\tDecoded Gray code\n"
        "0\t00000\t00000\t\t0\n"
        "1\t00001\t00001\t\t1\n"
        "2\t00010\t00011\t\t2\n"
        "3\t00011\t00010\t\t3\n"
        "4\t00100\t00110\t\t4\n"
        "5\t00101\t00111\t\t5\n"
        "6\t00110\t00101\t\t6\n"
        "7\t00111\t00100\t\t7\n"
        "8\t01000\t01100\t\t8\n"
        "9\t01001\t01101\t\t9\n"
        "10\t01010\t01111\t\t10\n"
        "11\t01011\t01110\t\t11\n"
        "12\t01100\t01010\t\t12\n"
        "13\t01101\t01011\t\t13\n"
        "14\t01110\t01001\t\t14\n"
        "15\t01111\t01000\t\t15\n"
        "16\t10000\t11000\t\t16\n"
        "17\t10001\t11001\t\t17\n"
        "18\t10010\t11011\t\t18\n"
        "19\t10011\t11010\t\t19\n"
        "20\t10100\t11110\t\t20\n"
        "21\t10101\t11111\t\t21\n"
        "22\t10110\t11101\t\t22\n"
        "23\t10111\t11100\t\t23\n"
        "24\t11000\t10100\t\t24\n"
        "25\t11001\t10101\t\t25\n"
        "26\t11010\t10111\t\t26\n"
        "27\t11011\t10110\t\t27\n"
        "28\t11100\t10010\t\t28\n"
        "29\t11101\t10011\t\t29\n"
        "30\t11110\t10001\t\t30\n"
        "31\t11111\t10000\t\t31\n"
    ));
}
