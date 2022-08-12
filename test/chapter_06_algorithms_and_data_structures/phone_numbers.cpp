#include "chapter_06_algorithms_and_data_structures/phone_numbers.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <fmt/format.h>

using tmcppc::phone::country_code;


TEST(country_code_US, DISABLED_fmt_format) { EXPECT_EQ(fmt::format("{}", country_code::US), "US"); }
TEST(country_code_Spain, DISABLED_fmt_format) { EXPECT_EQ(fmt::format("{}", country_code::Spain), "Spain"); }
TEST(country_code_UK, DISABLED_fmt_format) { EXPECT_EQ(fmt::format("{}", country_code::UK), "UK"); }
TEST(country_code_unknown, DISABLED_fmt_format) {
    EXPECT_EQ(fmt::format("{}", static_cast<country_code>(10)), "Unknown country code");
}
