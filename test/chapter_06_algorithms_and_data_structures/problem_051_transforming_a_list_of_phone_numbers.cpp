#include "chapter_06_algorithms_and_data_structures/problem_051_transforming_a_list_of_phone_numbers.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream

using namespace tmcppc::problem_51;


TEST(format_phone_numbers, empty_phone_numbers) {
    phone_numbers ph_nos{};
    format_phone_numbers(ph_nos, country_code::US);
    EXPECT_TRUE(ph_nos.empty());
}
TEST(format_phone_numbers, unknown_country_code) {
    phone_numbers ph_nos{ "555102030" };
    format_phone_numbers(ph_nos, static_cast<country_code>(10));
    EXPECT_TRUE(ph_nos.empty());
}
TEST(format_phone_numbers, country_code_not_found) {
    phone_numbers ph_nos{ "34987102030" };
    format_phone_numbers(ph_nos, country_code::US);
    EXPECT_TRUE(ph_nos.empty());
}
TEST(format_phone_numbers, country_code_does_not_contain_a_10_digit_number) {
    phone_numbers ph_nos{ "0 12345678" };
    format_phone_numbers(ph_nos, country_code::US);
    EXPECT_TRUE(ph_nos.empty());
}
TEST(format_phone_numbers, country_code_starts_with_zero) {
    phone_numbers ph_nos{ "+02 1234567890" };
    format_phone_numbers(ph_nos, country_code::US);
    EXPECT_TRUE(ph_nos.empty());
}
TEST(format_phone_numbers, success) {
    phone_numbers ph_nos{ "07555 111111" };
    format_phone_numbers(ph_nos, country_code::UK);
    EXPECT_THAT(ph_nos, ::testing::ElementsAre("+447555111111"));
}



TEST(problem_51_main, output) {
    std::ostringstream oss{};
    problem_51_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "List of phone numbers:\n"
        "\t[\"07555 111111\", \"07555222222\", \"+44 7555 333333\", \"44 7555 444444\", \"7555 555555\"]\n"
        "List of UK phone numbers after formatting:\n"
        "\t[\"+447555111111\", \"+447555222222\", \"+447555333333\", \"+447555444444\", \"+447555555555\"]\n"
        "\n"
        "List of phone numbers:\n"
        "\t[\"+1 2345 666666\", \"34 987 7777777\", \"0 12345678\", \"+02 1234567890\"]\n"
        "List of UK phone numbers after formatting:\n"
        "\t[]\n"
    ));
}
