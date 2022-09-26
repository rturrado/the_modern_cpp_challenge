#include "chapter_02_language_features/problem_018_variadic_minimum_function.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <functional>
#include <sstream>  // ostringstream

using namespace tmcppc::problem_18;


TEST(more_than, equal) { EXPECT_FALSE(more_than(5, 5)); }
TEST(more_than, less_than) { EXPECT_FALSE(more_than(1, 5)); }
TEST(more_than, more_than) { EXPECT_TRUE(more_than(10, 5)); }

TEST(to_string, one_element) { EXPECT_EQ(to_string(", ", 1), "1"); }
TEST(to_string, many_elements) { EXPECT_EQ(to_string(", ", 1, 2, 3), "1, 2, 3"); }
TEST(to_string, one_char) { EXPECT_EQ(to_string(", ", '1'), "1"); }
TEST(to_string, many_chars) { EXPECT_EQ(to_string(", ", '1', '2', '3'), "1, 2, 3"); }

TEST(minimum, l5_r5) { EXPECT_EQ(minimum(5, 5), 5); }
TEST(minimum, l5_r10) { EXPECT_EQ(minimum(5, 10), 5); }
TEST(minimum, l10_r5) { EXPECT_EQ(minimum(10, 5), 5); }
TEST(minimum, many_elements) { EXPECT_EQ(minimum(-100, -10, 0, 10, 100), -100); }

TEST(minimum, string_literals) {
    static const char* l1{ "Ricky Rubio" };
    static const char* l2{ "Jason Williams" };
    static const char* l3{ "Allen Iverson" };
    EXPECT_EQ(minimum(l3, l3), l3);
    EXPECT_EQ(minimum(l3, l1), l3);
    EXPECT_EQ(minimum(l1, l3), l3);
    EXPECT_EQ(minimum(l1, l2, l3), l3);
}

TEST(compare_with, l5_r5) { EXPECT_EQ(compare_with(std::greater{}, 5, 5), 5); }
TEST(compare_with, l5_r10) { EXPECT_EQ(compare_with(std::greater{}, 5, 10), 10); }
TEST(compare_with, l10_r5) { EXPECT_EQ(compare_with(std::greater{}, 10, 5), 10); }
TEST(compare_with, many_elements) { EXPECT_EQ(compare_with(std::greater{}, -100, -10, 0, 10, 100), 100); }

TEST(problem_18_main, output) {
    std::ostringstream oss{};
    problem_18_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "minimum(1, 7, -3, 42) = -3\n"
        "minimum(un, lugar, de, la, Mancha) = Mancha\n"
        "minimum(un, lugar, de, la, Mancha) = Mancha\n"
        "\n"
        "compare_with(more_than, 1, 7, -3, 42) = 42\n"
        "compare_with(std::greater, un, lugar, de, la, Mancha) = un\n\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::Not(::testing::EndsWith("\n\n\n")));
}
