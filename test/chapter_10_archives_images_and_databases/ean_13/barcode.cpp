#include "chapter_10_archives_images_and_databases/ean_13/barcode.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <bitset>

using namespace tmcppc::ean_13;


// Precondition: '0' <= c <= '9'
TEST(to_uint_8_t, DISABLED_zero) { EXPECT_EQ(to_uint8_t('0'), 0); }
TEST(to_uint_8_t, DISABLED_five) { EXPECT_EQ(to_uint8_t('5'), 5); }
TEST(to_uint_8_t, DISABLED_nine) { EXPECT_EQ(to_uint8_t('9'), 9); }


TEST(digit_l_encode, DISABLED_zero) { digit d{ digit_type::l }; EXPECT_EQ(d.encode(0), digit_bs{ "0001101" }); }
TEST(digit_l_encode, DISABLED_five) { digit d{ digit_type::l }; EXPECT_EQ(d.encode(5), digit_bs{ "0110001" }); }
TEST(digit_l_encode, DISABLED_nine) { digit d{ digit_type::l }; EXPECT_EQ(d.encode(9), digit_bs{ "0001011" }); }

TEST(digit_g_encode, DISABLED_zero) { digit d{ digit_type::g }; EXPECT_EQ(d.encode(0), digit_bs{ "0100111" }); }
TEST(digit_g_encode, DISABLED_five) { digit d{ digit_type::g }; EXPECT_EQ(d.encode(5), digit_bs{ "0111001" }); }
TEST(digit_g_encode, DISABLED_nine) { digit d{ digit_type::g }; EXPECT_EQ(d.encode(9), digit_bs{ "0010111" }); }

TEST(digit_r_encode, DISABLED_zero) { digit d{ digit_type::r }; EXPECT_EQ(d.encode(0), digit_bs{ "1110010" }); }
TEST(digit_r_encode, DISABLED_five) { digit d{ digit_type::r }; EXPECT_EQ(d.encode(5), digit_bs{ "1001110" }); }
TEST(digit_r_encode, DISABLED_nine) { digit d{ digit_type::r }; EXPECT_EQ(d.encode(9), digit_bs{ "1110100" }); }


TEST(digit_group_encode, DISABLED_llgglg) {
    digit_group dg{
        digit{ digit_type::l },
        digit{ digit_type::l },
        digit{ digit_type::g },
        digit{ digit_type::g },
        digit{ digit_type::l },
        digit{ digit_type::g }
    };
    EXPECT_THAT(dg.encode("407014"), ::testing::ElementsAre(
        digit_bs{ "0100011" },  // l 4
        digit_bs{ "0001101" },  // l 0
        digit_bs{ "0010001" },  // g 7
        digit_bs{ "0100111" },  // g 0
        digit_bs{ "0011001" },  // l 1
        digit_bs{ "0011101" }  // g 4
    ));
}
TEST(digit_group_encode, DISABLED_rrrrrr) {
    digit_group dg{
        digit{ digit_type::r },
        digit{ digit_type::r },
        digit{ digit_type::r },
        digit{ digit_type::r },
        digit{ digit_type::r },
        digit{ digit_type::r }
    };
    EXPECT_THAT(dg.encode("001944"), ::testing::ElementsAre(
        digit_bs{ "1110010" },  // r 0
        digit_bs{ "1110010" },  // r 0
        digit_bs{ "1100110" },  // r 1
        digit_bs{ "1110100" },  // r 9
        digit_bs{ "1011100" },  // r 4
        digit_bs{ "1011100" }  // r 4
    ));
}

TEST(barcode, DISABLED_constructor_with_invalid_code_size) { EXPECT_THROW(barcode{ "1234567890" }, invalid_code_size_exception); }
TEST(barcode, DISABLED_constructor_with_invalid_code) { EXPECT_THROW(barcode{ "1234567890abc" }, invalid_code_exception); }
TEST(barcode, DISABLED_constructor) {
    barcode b{ "2407014001944" };
    EXPECT_EQ(b.get_first_digit_char(), '2');
    EXPECT_EQ(b.get_first_digit_group_string(), "407014");
    EXPECT_EQ(b.get_second_digit_group_string(), "001944");
    EXPECT_THAT(b.get_first_digit_group_bs(), ::testing::ElementsAre(
        digit_bs{ "0100011" },  // l 4
        digit_bs{ "0001101" },  // l 0
        digit_bs{ "0010001" },  // g 7
        digit_bs{ "0100111" },  // g 0
        digit_bs{ "0011001" },  // l 1
        digit_bs{ "0011101" }  // g 4
    ));
    EXPECT_THAT(b.get_second_digit_group_bs(), ::testing::ElementsAre(
        digit_bs{ "1110010" },  // r 0
        digit_bs{ "1110010" },  // r 0
        digit_bs{ "1100110" },  // r 1
        digit_bs{ "1110100" },  // r 9
        digit_bs{ "1011100" },  // r 4
        digit_bs{ "1011100" }  // r 4
    ));
}
