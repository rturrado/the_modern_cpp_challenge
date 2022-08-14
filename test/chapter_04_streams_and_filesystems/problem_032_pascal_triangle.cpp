#include "chapter_04_streams_and_filesystems/problem_032_pascal_triangle.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream
#include <stdexcept>  // out_of_range

using namespace tmcppc::problem_32;


TEST(pascal_triangle, DISABLED_zero) { EXPECT_TRUE(pascal_triangle(0).empty()); }
TEST(pascal_triangle, DISABLED_one) { EXPECT_EQ(pascal_triangle(1),
    pascal_triangle_t{
        { 1 }
    });
}
TEST(pascal_triangle, DISABLED_two) { EXPECT_EQ(pascal_triangle(2),
    (pascal_triangle_t{
        { 1 },
        { 1, 1 }
    }));
}
TEST(pascal_triangle, DISABLED_ten) { EXPECT_EQ(pascal_triangle(10),
    (pascal_triangle_t{
        { 1 },
        { 1, 1 },
        { 1, 2, 1 },
        { 1, 3, 3, 1 },
        { 1, 4, 6, 4, 1 },
        { 1, 5, 10, 10, 5, 1 },
        { 1, 6, 15, 20, 15, 6, 1 },
        { 1, 7, 21, 35, 35, 21, 7, 1 },
        { 1, 8, 28, 56, 70, 56, 28, 8, 1 },
        { 1, 9, 36, 84, 126, 126, 84, 36, 9, 1 },
    }));
}
TEST(pascal_triangle, DISABLED_forty) { EXPECT_THROW(pascal_triangle(40), std::out_of_range); }

TEST(problem_32_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_32_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "Pascal triangle for n = 0:\n"
        "\t[]\n"
        "Pascal triangle for n = 1:\n"
        "\t[1]\n"
        "Pascal triangle for n = 2:\n"
        "\t[1]\n"
        "\t[1, 1]\n"
        "Pascal triangle for n = 10:\n"
        "\t[1]\n"
        "\t[1, 1]\n"
        "\t[1, 2, 1]\n"
        "\t[1, 3, 3, 1]\n"
        "\t[1, 4, 6, 4, 1]\n"
        "\t[1, 5, 10, 10, 5, 1]\n"
        "\t[1, 6, 15, 20, 15, 6, 1]\n"
        "\t[1, 7, 21, 35, 35, 21, 7, 1]\n"
        "\t[1, 8, 28, 56, 70, 56, 28, 8, 1]\n"
        "\t[1, 9, 36, 84, 126, 126, 84, 36, 9, 1]\n"
        "Pascal triangle for n = 40:\n"
        "\tError: calling pascal_triangle with n > 30, n = 40\n\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::Not(::testing::EndsWith("\n\n\n")));
}
