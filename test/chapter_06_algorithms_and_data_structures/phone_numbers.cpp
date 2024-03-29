#include "chapter_06_algorithms_and_data_structures/phone_numbers.h"

#include <fmt/format.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using tmcppc::phone::country_code;


TEST(country_code_US, fmt_format) { EXPECT_EQ(fmt::format("{}", country_code::US), "US"); }
TEST(country_code_Spain, fmt_format) { EXPECT_EQ(fmt::format("{}", country_code::Spain), "Spain"); }
TEST(country_code_UK, fmt_format) { EXPECT_EQ(fmt::format("{}", country_code::UK), "UK"); }
TEST(country_code_unknown, fmt_format) {
    EXPECT_EQ(fmt::format("{}", static_cast<country_code>(10)), "Unknown country code");
}
