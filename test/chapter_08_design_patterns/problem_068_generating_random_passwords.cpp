#include "chapter_08_design_patterns/problem_068_generating_random_passwords.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <algorithm>  // all_of
#include <cctype>  // isdigit, islower, ispunct, isupper
#include <memory>  // make_unique
#include <sstream>  // ostringstream

using namespace tmcppc::password;


TEST(symbol_generator, zero_length) { EXPECT_TRUE(symbol_generator{ 0 }.generate().empty()); }
TEST(symbol_generator, nonzero_length) {
    auto result{ symbol_generator{5}.generate() };
    EXPECT_EQ(result.size(), 5);
    EXPECT_TRUE(std::ranges::all_of(result, [](unsigned char c) { return std::ispunct(c); }));
}


TEST(contains_digit_generator, zero_length) { EXPECT_TRUE(contains_generator<digit_range>{ 0 }.generate().empty()); }
TEST(contains_digit_generator, nonzero_length) {
    auto result{ contains_generator<digit_range>{5}.generate() };
    EXPECT_EQ(result.size(), 5);
    EXPECT_TRUE(std::ranges::all_of(result, [](unsigned char c) { return std::isdigit(c); }));
}

TEST(contains_uppercase_generator, zero_length) { EXPECT_TRUE(contains_generator<uppercase_range>{ 0 }.generate().empty()); }
TEST(contains_uppercase_generator, nonzero_length) {
    auto result{ contains_generator<uppercase_range>{5}.generate() };
    EXPECT_EQ(result.size(), 5);
    EXPECT_TRUE(std::ranges::all_of(result, [](unsigned char c) { return std::isupper(c); }));
}

TEST(contains_lowercase_generator, zero_length) { EXPECT_TRUE(contains_generator<lowercase_range>{ 0 }.generate().empty()); }
TEST(contains_lowercase_generator, nonzero_length) {
    auto result{ contains_generator<lowercase_range>{5}.generate() };
    EXPECT_EQ(result.size(), 5);
    EXPECT_TRUE(std::ranges::all_of(result, [](unsigned char c) { return std::islower(c); }));
}


TEST(composite_password_generator, no_generators) { EXPECT_TRUE(composite_password_generator{}.generate().empty()); }
TEST(composite_password_generator, some_generators) {
    composite_password_generator cpg{};
    cpg.add_generator(std::make_unique<symbol_generator>(2));
    cpg.add_generator(std::make_unique<contains_generator<digit_range>>(2));
    cpg.add_generator(std::make_unique<contains_generator<uppercase_range>>(2));
    cpg.add_generator(std::make_unique<contains_generator<lowercase_range>>(2));
    auto result{ cpg.generate() };
    EXPECT_EQ(result.size(), 8);
    EXPECT_EQ(std::ranges::count_if(result, [](unsigned char c) { return std::ispunct(c); }), 2);
    EXPECT_EQ(std::ranges::count_if(result, [](unsigned char c) { return std::isdigit(c); }), 2);
    EXPECT_EQ(std::ranges::count_if(result, [](unsigned char c) { return std::isupper(c); }), 2);
    EXPECT_EQ(std::ranges::count_if(result, [](unsigned char c) { return std::islower(c); }), 2);
}


TEST(problem_68_main, output) {
    std::ostringstream oss{};
    problem_68_main(oss);
    EXPECT_THAT(oss.str(), ::testing::ContainsRegex(
        "Creating a password with 2 symbols, 2 digits, 2 lowercase letters, and 2 uppercase letters: ........\n\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::Not(::testing::EndsWith("\n\n\n")));
}
