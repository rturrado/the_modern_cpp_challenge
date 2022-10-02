#include "chapter_06_algorithms_and_data_structures/problem_050_filtering_a_list_of_phone_numbers.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <sstream>  // ostringstream

using namespace tmcppc::problem_50;


TEST(filter_phone_numbers_by_country_code, empty_phone_numbers) {
    EXPECT_TRUE(filter_phone_numbers_by_country_code(phone_numbers{}, country_code::US).empty());
}
TEST(filter_phone_numbers_by_country_code, unknown_country_code) {
    EXPECT_TRUE(filter_phone_numbers_by_country_code(phone_numbers{ "555102030" }, static_cast<country_code>(10)).empty());
}
TEST(filter_phone_numbers_by_country_code, country_code_not_found) {
    EXPECT_TRUE(filter_phone_numbers_by_country_code(phone_numbers{ "34987102030" }, country_code::US).empty());
}
TEST(filter_phone_numbers_by_country_code, country_code_does_not_contain_a_10_digit_number) {
    EXPECT_TRUE(filter_phone_numbers_by_country_code(phone_numbers{ "0 12345678" }, country_code::US).empty());
}
TEST(filter_phone_numbers_by_country_code, country_code_starts_with_zero) {
    EXPECT_TRUE(filter_phone_numbers_by_country_code(phone_numbers{ "+02 1234567890" }, country_code::US).empty());
}
TEST(filter_phone_numbers_by_country_code, success) {
    EXPECT_THAT(
        filter_phone_numbers_by_country_code(phone_numbers{ "1555607080" }, country_code::US),
        ::testing::ElementsAre("1555607080")
    );
}


TEST(problem_50_main, output) {
    std::ostringstream oss{};
    problem_50_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "List of phone numbers:\n"
        "\t[\"555102030\", \"600111222\", \"798070238\", \"1555607080\", \"34987102030\", \"44798183123\", \"+1555101112\", \"+34985242526\", \"+44223344567\"]\n"
        "\n"
        "Filtering numbers from: US\n"
        "\t[\"1555607080\", \"+1555101112\"]\n"
        "\n"
        "Filtering numbers from: Spain\n"
        "\t[\"34987102030\", \"+34985242526\"]\n"
        "\n"
        "Filtering numbers from: UK\n"
        "\t[\"44798183123\", \"+44223344567\"]\n"
    ));
}

