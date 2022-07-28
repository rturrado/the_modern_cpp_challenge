#include "chapter_11_cryptography/base64.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <string>
#include <vector>

using namespace tmcppc::crypto;


TEST(encode, DISABLED_empty_input_data_with_padding) { EXPECT_TRUE(base64{}.encode(base64::data_t{}, true).empty()); }
TEST(encode, DISABLED_empty_input_data_without_padding) { EXPECT_TRUE(base64{}.encode(base64::data_t{}, false).empty()); }

TEST(encode, DISABLED_M_with_padding) {
    const std::string text{ "M" };
    base64::data_t data{ text.begin(), text.begin() + text.size() };
    EXPECT_EQ(base64{}.encode(data, true), "TQ==");
}
TEST(encode, DISABLED_M_without_padding) {
    const std::string text{ "M" };
    base64::data_t data{ text.begin(), text.begin() + text.size() };
    EXPECT_EQ(base64{}.encode(data, false), "TQ");
}

TEST(encode, DISABLED_Ma_with_padding) {
    const std::string text{ "Ma" };
    base64::data_t data{ text.begin(), text.begin() + text.size() };
    EXPECT_EQ(base64{}.encode(data, true), "TWE=");
}
TEST(encode, DISABLED_Ma_without_padding) {
    const std::string text{ "Ma" };
    base64::data_t data{ text.begin(), text.begin() + text.size() };
    EXPECT_EQ(base64{}.encode(data, false), "TWE");
}

TEST(encode, DISABLED_Man_with_padding) {
    const std::string text{ "Man" };
    base64::data_t data{ text.begin(), text.begin() + text.size() };
    EXPECT_EQ(base64{}.encode(data, true), "TWFu");
}
TEST(encode, DISABLED_Man_without_padding) {
    const std::string text{ "Man" };
    base64::data_t data{ text.begin(), text.begin() + text.size() };
    EXPECT_EQ(base64{}.encode(data, false), "TWFu");
}

TEST(encode, DISABLED_Many_with_padding) {
    const std::string text{ "Many" };
    base64::data_t data{ text.begin(), text.begin() + text.size() };
    EXPECT_EQ(base64{}.encode(data, true), "TWFueQ==");
}
TEST(encode, DISABLED_Many_without_padding) {
    const std::string text{ "Many" };
    base64::data_t data{ text.begin(), text.begin() + text.size() };
    EXPECT_EQ(base64{}.encode(data, false), "TWFueQ");
}

TEST(encode, DISABLED_Many__with_padding) {
    const std::string text{ "Many " };
    base64::data_t data{ text.begin(), text.begin() + text.size() };
    EXPECT_EQ(base64{}.encode(data, true), "TWFueSA=");
}
TEST(encode, DISABLED_Many__without_padding) {
    const std::string text{ "Many " };
    base64::data_t data{ text.begin(), text.begin() + text.size() };
    EXPECT_EQ(base64{}.encode(data, false), "TWFueSA");
}

TEST(encode, DISABLED_Many_h_with_padding) {
    const std::string text{ "Many h" };
    base64::data_t data{ text.begin(), text.begin() + text.size() };
    EXPECT_EQ(base64{}.encode(data, true), "TWFueSBo");
}
TEST(encode, DISABLED_Many_h_without_padding) {
    const std::string text{ "Many h" };
    base64::data_t data{ text.begin(), text.begin() + text.size() };
    EXPECT_EQ(base64{}.encode(data, false), "TWFueSBo");
}

TEST(encode, DISABLED_Many_hands_make_light_work_with_padding) {
    const std::string text{ "Many hands make light work" };
    base64::data_t data{ text.begin(), text.begin() + text.size() };
    EXPECT_EQ(base64{}.encode(data, true), "TWFueSBoYW5kcyBtYWtlIGxpZ2h0IHdvcms=");
}
TEST(encode, DISABLED_Many_hands_make_light_work_without_padding) {
    const std::string text{ "Many hands make light work" };
    base64::data_t data{ text.begin(), text.begin() + text.size() };
    EXPECT_EQ(base64{}.encode(data, false), "TWFueSBoYW5kcyBtYWtlIGxpZ2h0IHdvcms");
}


TEST(decode, DISABLED_empty_input_data) { EXPECT_TRUE(base64{}.decode("").empty()); }

TEST(decode, DISABLED_data_containing_only_characters_not_in_the_decoding_table_and_size_1) { EXPECT_TRUE(base64{}.decode("=").empty()); }
TEST(decode, DISABLED_data_containing_only_characters_not_in_the_decoding_table_and_size_2) { EXPECT_TRUE(base64{}.decode("==").empty()); }
TEST(decode, DISABLED_data_containing_only_characters_not_in_the_decoding_table_and_size_3) { EXPECT_TRUE(base64{}.decode("==#").empty()); }
TEST(decode, DISABLED_data_containing_only_characters_not_in_the_decoding_table_and_size_4) { EXPECT_TRUE(base64{}.decode("==##").empty()); }
TEST(decode, DISABLED_data_containing_only_characters_not_in_the_decoding_table_and_size_5) { EXPECT_TRUE(base64{}.decode("==##@").empty()); }

TEST(decode, DISABLED_M_with_padding) {
    auto ret{ base64{}.decode("TQ==") };
    EXPECT_EQ((std::string{ ret.begin(), ret.end() }), std::string{ "M" });
}

TEST(decode, DISABLED_M_without_padding) {
    auto ret{ base64{}.decode("TQ") };
    EXPECT_EQ((std::string{ ret.begin(), ret.end() }), std::string{ "M" });
}
TEST(decode, DISABLED_M_with_characters_not_in_the_decoding_table) {
    auto ret{ base64{}.decode("##T==Q@@") };
    EXPECT_EQ((std::string{ ret.begin(), ret.end() }), std::string{ "M" });
}

TEST(decode, DISABLED_Ma_with_padding) {
    auto ret{ base64{}.decode("TWE=") };
    EXPECT_EQ((std::string{ ret.begin(), ret.end() }), std::string{ "Ma" });
}
TEST(decode, DISABLED_Ma_without_padding) {
    auto ret{ base64{}.decode("TWE") };
    EXPECT_EQ((std::string{ ret.begin(), ret.end() }), std::string{ "Ma" });
}
TEST(decode, DISABLED_Ma_with_characters_not_in_the_decoding_table) {
    auto ret{ base64{}.decode("##TW==E@@") };
    EXPECT_EQ((std::string{ ret.begin(), ret.end() }), std::string{ "Ma" });
}

TEST(decode, DISABLED_Man_with_padding) {
    auto ret{ base64{}.decode("TWFu") };
    EXPECT_EQ((std::string{ ret.begin(), ret.end() }), std::string{ "Man" });
}
TEST(decode, DISABLED_Man_without_padding) {
    auto ret{ base64{}.decode("TWFu") };
    EXPECT_EQ((std::string{ ret.begin(), ret.end() }), std::string{ "Man" });
}
TEST(decode, DISABLED_Man_with_characters_not_in_the_decoding_table) {
    auto ret{ base64{}.decode("##TW==Fu@@") };
    EXPECT_EQ((std::string{ ret.begin(), ret.end() }), std::string{ "Man" });
}

TEST(decode, DISABLED_Many_with_padding) {
    auto ret{ base64{}.decode("TWFueQ==") };
    EXPECT_EQ((std::string{ ret.begin(), ret.end() }), std::string{ "Many" });
}
TEST(decode, DISABLED_Many_without_padding) {
    auto ret{ base64{}.decode("TWFueQ") };
    EXPECT_EQ((std::string{ ret.begin(), ret.end() }), std::string{ "Many" });
}
TEST(decode, DISABLED_Many_with_characters_not_in_the_decoding_table) {
    auto ret{ base64{}.decode("##TWF==ueQ@@") };
    EXPECT_EQ((std::string{ ret.begin(), ret.end() }), std::string{ "Many" });
}

TEST(decode, DISABLED_Many__with_padding) {
    auto ret{ base64{}.decode("TWFueSA=") };
    EXPECT_EQ((std::string{ ret.begin(), ret.end() }), std::string{ "Many " });
}
TEST(decode, DISABLED_Many__without_padding) {
    auto ret{ base64{}.decode("TWFueSA") };
    EXPECT_EQ((std::string{ ret.begin(), ret.end() }), std::string{ "Many " });
}
TEST(decode, DISABLED_Many__with_characters_not_in_the_decoding_table) {
    auto ret{ base64{}.decode("##TWFu==eSA@@") };
    EXPECT_EQ((std::string{ ret.begin(), ret.end() }), std::string{ "Many " });
}

TEST(decode, DISABLED_Many_h_with_padding) {
    auto ret{ base64{}.decode("TWFueSBo") };
    EXPECT_EQ((std::string{ ret.begin(), ret.end() }), std::string{ "Many h" });
}
TEST(decode, DISABLED_Many_h_without_padding) {
    auto ret{ base64{}.decode("TWFueSBo") };
    EXPECT_EQ((std::string{ ret.begin(), ret.end() }), std::string{ "Many h" });
}
TEST(decode, DISABLED_Many_h_with_characters_not_in_the_decoding_table) {
    auto ret{ base64{}.decode("##TWFu==eSBo@@") };
    EXPECT_EQ((std::string{ ret.begin(), ret.end() }), std::string{ "Many h" });
}

TEST(decode, DISABLED_Many_hands_make_light_work_with_padding) {
    auto ret{ base64{}.decode("TWFueSBoYW5kcyBtYWtlIGxpZ2h0IHdvcms=") };
    EXPECT_EQ((std::string{ ret.begin(), ret.end() }), std::string{ "Many hands make light work" });
}
TEST(decode, DISABLED_Many_hands_make_light_work_without_padding) {
    auto ret{ base64{}.decode("TWFueSBoYW5kcyBtYWtlIGxpZ2h0IHdvcms") };
    EXPECT_EQ((std::string{ ret.begin(), ret.end() }), std::string{ "Many hands make light work" });
}
TEST(decode, DISABLED_Many_hands_make_light_work_with_characters_not_in_the_decoding_table) {
    auto ret{ base64{}.decode("##TWFueSBoYW5kcyBtYW==tlIGxpZ2h0IHdvcms@@") };
    EXPECT_EQ((std::string{ ret.begin(), ret.end() }), std::string{ "Many hands make light work" });
}
