#include "chapter_01_math/roman.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <stdexcept>  // out_of_range

using namespace tmcppc::date;


TEST(to_roman_v1, n_0) { EXPECT_THROW(to_roman_v1(0), std::out_of_range); }
TEST(to_roman_v2, n_0) { EXPECT_THROW(to_roman_v2(0), std::out_of_range); }
TEST(to_roman_v3, n_0) { EXPECT_THROW(to_roman_v3(0), std::out_of_range); }
TEST(to_roman_v4, n_0) { EXPECT_THROW(to_roman_v4(0), std::out_of_range); }

TEST(to_roman_v1, n_4000) { EXPECT_THROW(to_roman_v1(4000), std::out_of_range); }
TEST(to_roman_v2, n_4000) { EXPECT_THROW(to_roman_v2(4000), std::out_of_range); }
TEST(to_roman_v3, n_4000) { EXPECT_THROW(to_roman_v3(4000), std::out_of_range); }
TEST(to_roman_v4, n_4000) { EXPECT_THROW(to_roman_v4(4000), std::out_of_range); }

TEST(to_roman_v1, n_4) { EXPECT_EQ(to_roman_v1(4), "IV"); }
TEST(to_roman_v1, n_44) { EXPECT_EQ(to_roman_v1(44), "XLIV"); }
TEST(to_roman_v1, n_444) { EXPECT_EQ(to_roman_v1(444), "CDXLIV"); }
TEST(to_roman_v1, n_8) { EXPECT_EQ(to_roman_v1(8), "VIII"); }
TEST(to_roman_v1, n_88) { EXPECT_EQ(to_roman_v1(88), "LXXXVIII"); }
TEST(to_roman_v1, n_888) { EXPECT_EQ(to_roman_v1(888), "DCCCLXXXVIII"); }
TEST(to_roman_v1, n_95) { EXPECT_EQ(to_roman_v1(95), "XCV"); }
TEST(to_roman_v1, n_195) { EXPECT_EQ(to_roman_v1(195), "CXCV"); }
TEST(to_roman_v1, n_1950) { EXPECT_EQ(to_roman_v1(1950), "MCML"); }

TEST(to_roman_v2, n_4) { EXPECT_EQ(to_roman_v2(4), "IV"); }
TEST(to_roman_v2, n_44) { EXPECT_EQ(to_roman_v2(44), "XLIV"); }
TEST(to_roman_v2, n_444) { EXPECT_EQ(to_roman_v2(444), "CDXLIV"); }
TEST(to_roman_v2, n_8) { EXPECT_EQ(to_roman_v2(8), "VIII"); }
TEST(to_roman_v2, n_88) { EXPECT_EQ(to_roman_v2(88), "LXXXVIII"); }
TEST(to_roman_v2, n_888) { EXPECT_EQ(to_roman_v2(888), "DCCCLXXXVIII"); }
TEST(to_roman_v2, n_95) { EXPECT_EQ(to_roman_v2(95), "XCV"); }
TEST(to_roman_v2, n_195) { EXPECT_EQ(to_roman_v2(195), "CXCV"); }
TEST(to_roman_v2, n_1950) { EXPECT_EQ(to_roman_v2(1950), "MCML"); }

TEST(to_roman_v3, n_4) { EXPECT_EQ(to_roman_v3(4), "IV"); }
TEST(to_roman_v3, n_44) { EXPECT_EQ(to_roman_v3(44), "XLIV"); }
TEST(to_roman_v3, n_444) { EXPECT_EQ(to_roman_v3(444), "CDXLIV"); }
TEST(to_roman_v3, n_8) { EXPECT_EQ(to_roman_v3(8), "VIII"); }
TEST(to_roman_v3, n_88) { EXPECT_EQ(to_roman_v3(88), "LXXXVIII"); }
TEST(to_roman_v3, n_888) { EXPECT_EQ(to_roman_v3(888), "DCCCLXXXVIII"); }
TEST(to_roman_v3, n_95) { EXPECT_EQ(to_roman_v3(95), "XCV"); }
TEST(to_roman_v3, n_195) { EXPECT_EQ(to_roman_v3(195), "CXCV"); }
TEST(to_roman_v3, n_1950) { EXPECT_EQ(to_roman_v3(1950), "MCML"); }

TEST(to_roman_v4, n_4) { EXPECT_EQ(to_roman_v4(4), "IV"); }
TEST(to_roman_v4, n_44) { EXPECT_EQ(to_roman_v4(44), "XLIV"); }
TEST(to_roman_v4, n_444) { EXPECT_EQ(to_roman_v4(444), "CDXLIV"); }
TEST(to_roman_v4, n_8) { EXPECT_EQ(to_roman_v4(8), "VIII"); }
TEST(to_roman_v4, n_88) { EXPECT_EQ(to_roman_v4(88), "LXXXVIII"); }
TEST(to_roman_v4, n_888) { EXPECT_EQ(to_roman_v4(888), "DCCCLXXXVIII"); }
TEST(to_roman_v4, n_95) { EXPECT_EQ(to_roman_v4(95), "XCV"); }
TEST(to_roman_v4, n_195) { EXPECT_EQ(to_roman_v4(195), "CXCV"); }
TEST(to_roman_v4, n_1950) { EXPECT_EQ(to_roman_v4(1950), "MCML"); }
