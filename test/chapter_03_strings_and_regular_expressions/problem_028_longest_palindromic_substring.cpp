#include "chapter_03_strings_and_regular_expressions/problem_028_longest_palindromic_substring.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream
#include <string_view>

using namespace tmcppc::problem_28;


TEST(is_palindrome, DISABLED_empty_string) { EXPECT_TRUE(is_palindrome("")); }
TEST(is_palindrome, DISABLED_one_character_string) { EXPECT_TRUE(is_palindrome("a")); }
TEST(is_palindrome, DISABLED_valid_palindrome) { EXPECT_TRUE(is_palindrome("1111aaa8bb8aaa1111")); }
TEST(is_palindrome, DISABLED_invalid_palindrome) { EXPECT_FALSE(is_palindrome("1111aaa8bb8aaa11110")); }

TEST(longest_palindromic_substring, DISABLED_empty_string) {
    EXPECT_EQ(get_longest_palindromic_substring(""), "");
}
TEST(longest_palindromic_substring, DISABLED_one_character_string) {
    EXPECT_THAT(get_longest_palindromic_substring("a"), "a");
}
TEST(longest_palindromic_substring, DISABLED_string_is_palindrome) {
    EXPECT_THAT(get_longest_palindromic_substring("level"), "level");
}
TEST(longest_palindromic_substring, DISABLED_s_123aba3218888888888c) {
    EXPECT_THAT(get_longest_palindromic_substring("123aba3218888888888c"), "8888888888");
}

TEST(problem_28_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_28_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "Longest palindromic substring in \"\" is: \"\"\n"
        "Longest palindromic substring in \"s\" is: \"s\"\n"
        "Longest palindromic substring in \"level\" is: \"level\"\n"
        "Longest palindromic substring in \"sahararahnide\" is: \"hararah\"\n"
        "Longest palindromic substring in \"123aba3218888888888c\" is: \"8888888888\"\n\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::Not(::testing::EndsWith("\n\n\n")));
}
