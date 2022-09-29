#include "chapter_11_cryptography/base64.h"

#include <gtest/gtest.h>
#include <string>
#include <vector>

using namespace tmcppc::crypto;


TEST(encode, empty_input_data_with_padding) { EXPECT_TRUE(base64{}.encode(base64::data_t{}, true).empty()); }
TEST(encode, empty_input_data_without_padding) { EXPECT_TRUE(base64{}.encode(base64::data_t{}, false).empty()); }

TEST(encode, M_with_padding) {
    const std::string text{ "M" };
    base64::data_t data{ text.begin(), text.begin() + text.size() };
    EXPECT_EQ(base64{}.encode(data, true), "TQ==");
}
TEST(encode, M_without_padding) {
    const std::string text{ "M" };
    base64::data_t data{ text.begin(), text.begin() + text.size() };
    EXPECT_EQ(base64{}.encode(data, false), "TQ");
}

TEST(encode, Ma_with_padding) {
    const std::string text{ "Ma" };
    base64::data_t data{ text.begin(), text.begin() + text.size() };
    EXPECT_EQ(base64{}.encode(data, true), "TWE=");
}
TEST(encode, Ma_without_padding) {
    const std::string text{ "Ma" };
    base64::data_t data{ text.begin(), text.begin() + text.size() };
    EXPECT_EQ(base64{}.encode(data, false), "TWE");
}

TEST(encode, Man_with_padding) {
    const std::string text{ "Man" };
    base64::data_t data{ text.begin(), text.begin() + text.size() };
    EXPECT_EQ(base64{}.encode(data, true), "TWFu");
}
TEST(encode, Man_without_padding) {
    const std::string text{ "Man" };
    base64::data_t data{ text.begin(), text.begin() + text.size() };
    EXPECT_EQ(base64{}.encode(data, false), "TWFu");
}

TEST(encode, Many_with_padding) {
    const std::string text{ "Many" };
    base64::data_t data{ text.begin(), text.begin() + text.size() };
    EXPECT_EQ(base64{}.encode(data, true), "TWFueQ==");
}
TEST(encode, Many_without_padding) {
    const std::string text{ "Many" };
    base64::data_t data{ text.begin(), text.begin() + text.size() };
    EXPECT_EQ(base64{}.encode(data, false), "TWFueQ");
}

TEST(encode, Many__with_padding) {
    const std::string text{ "Many " };
    base64::data_t data{ text.begin(), text.begin() + text.size() };
    EXPECT_EQ(base64{}.encode(data, true), "TWFueSA=");
}
TEST(encode, Many__without_padding) {
    const std::string text{ "Many " };
    base64::data_t data{ text.begin(), text.begin() + text.size() };
    EXPECT_EQ(base64{}.encode(data, false), "TWFueSA");
}

TEST(encode, Many_h_with_padding) {
    const std::string text{ "Many h" };
    base64::data_t data{ text.begin(), text.begin() + text.size() };
    EXPECT_EQ(base64{}.encode(data, true), "TWFueSBo");
}
TEST(encode, Many_h_without_padding) {
    const std::string text{ "Many h" };
    base64::data_t data{ text.begin(), text.begin() + text.size() };
    EXPECT_EQ(base64{}.encode(data, false), "TWFueSBo");
}

TEST(encode, Many_hands_make_light_work_with_padding) {
    const std::string text{ "Many hands make light work" };
    base64::data_t data{ text.begin(), text.begin() + text.size() };
    EXPECT_EQ(base64{}.encode(data, true), "TWFueSBoYW5kcyBtYWtlIGxpZ2h0IHdvcms=");
}
TEST(encode, Many_hands_make_light_work_without_padding) {
    const std::string text{ "Many hands make light work" };
    base64::data_t data{ text.begin(), text.begin() + text.size() };
    EXPECT_EQ(base64{}.encode(data, false), "TWFueSBoYW5kcyBtYWtlIGxpZ2h0IHdvcms");
}


TEST(decode, empty_input_data) { EXPECT_TRUE(base64{}.decode("").empty()); }

TEST(decode, data_containing_only_characters_not_in_the_decoding_table_and_size_1) { EXPECT_TRUE(base64{}.decode("=").empty()); }
TEST(decode, data_containing_only_characters_not_in_the_decoding_table_and_size_2) { EXPECT_TRUE(base64{}.decode("==").empty()); }
TEST(decode, data_containing_only_characters_not_in_the_decoding_table_and_size_3) { EXPECT_TRUE(base64{}.decode("==#").empty()); }
TEST(decode, data_containing_only_characters_not_in_the_decoding_table_and_size_4) { EXPECT_TRUE(base64{}.decode("==##").empty()); }
TEST(decode, data_containing_only_characters_not_in_the_decoding_table_and_size_5) { EXPECT_TRUE(base64{}.decode("==##@").empty()); }

TEST(decode, M_with_padding) {
    auto ret{ base64{}.decode("TQ==") };
    EXPECT_EQ((std::string{ ret.begin(), ret.end() }), std::string{ "M" });
}

TEST(decode, M_without_padding) {
    auto ret{ base64{}.decode("TQ") };
    EXPECT_EQ((std::string{ ret.begin(), ret.end() }), std::string{ "M" });
}
TEST(decode, M_with_characters_not_in_the_decoding_table) {
    auto ret{ base64{}.decode("##T==Q@@") };
    EXPECT_EQ((std::string{ ret.begin(), ret.end() }), std::string{ "M" });
}

TEST(decode, Ma_with_padding) {
    auto ret{ base64{}.decode("TWE=") };
    EXPECT_EQ((std::string{ ret.begin(), ret.end() }), std::string{ "Ma" });
}
TEST(decode, Ma_without_padding) {
    auto ret{ base64{}.decode("TWE") };
    EXPECT_EQ((std::string{ ret.begin(), ret.end() }), std::string{ "Ma" });
}
TEST(decode, Ma_with_characters_not_in_the_decoding_table) {
    auto ret{ base64{}.decode("##TW==E@@") };
    EXPECT_EQ((std::string{ ret.begin(), ret.end() }), std::string{ "Ma" });
}

TEST(decode, Man_with_padding) {
    auto ret{ base64{}.decode("TWFu") };
    EXPECT_EQ((std::string{ ret.begin(), ret.end() }), std::string{ "Man" });
}
TEST(decode, Man_without_padding) {
    auto ret{ base64{}.decode("TWFu") };
    EXPECT_EQ((std::string{ ret.begin(), ret.end() }), std::string{ "Man" });
}
TEST(decode, Man_with_characters_not_in_the_decoding_table) {
    auto ret{ base64{}.decode("##TW==Fu@@") };
    EXPECT_EQ((std::string{ ret.begin(), ret.end() }), std::string{ "Man" });
}

TEST(decode, Many_with_padding) {
    auto ret{ base64{}.decode("TWFueQ==") };
    EXPECT_EQ((std::string{ ret.begin(), ret.end() }), std::string{ "Many" });
}
TEST(decode, Many_without_padding) {
    auto ret{ base64{}.decode("TWFueQ") };
    EXPECT_EQ((std::string{ ret.begin(), ret.end() }), std::string{ "Many" });
}
TEST(decode, Many_with_characters_not_in_the_decoding_table) {
    auto ret{ base64{}.decode("##TWF==ueQ@@") };
    EXPECT_EQ((std::string{ ret.begin(), ret.end() }), std::string{ "Many" });
}

TEST(decode, Many__with_padding) {
    auto ret{ base64{}.decode("TWFueSA=") };
    EXPECT_EQ((std::string{ ret.begin(), ret.end() }), std::string{ "Many " });
}
TEST(decode, Many__without_padding) {
    auto ret{ base64{}.decode("TWFueSA") };
    EXPECT_EQ((std::string{ ret.begin(), ret.end() }), std::string{ "Many " });
}
TEST(decode, Many__with_characters_not_in_the_decoding_table) {
    auto ret{ base64{}.decode("##TWFu==eSA@@") };
    EXPECT_EQ((std::string{ ret.begin(), ret.end() }), std::string{ "Many " });
}

TEST(decode, Many_h_with_padding) {
    auto ret{ base64{}.decode("TWFueSBo") };
    EXPECT_EQ((std::string{ ret.begin(), ret.end() }), std::string{ "Many h" });
}
TEST(decode, Many_h_without_padding) {
    auto ret{ base64{}.decode("TWFueSBo") };
    EXPECT_EQ((std::string{ ret.begin(), ret.end() }), std::string{ "Many h" });
}
TEST(decode, Many_h_with_characters_not_in_the_decoding_table) {
    auto ret{ base64{}.decode("##TWFu==eSBo@@") };
    EXPECT_EQ((std::string{ ret.begin(), ret.end() }), std::string{ "Many h" });
}

TEST(decode, Many_hands_make_light_work_with_padding) {
    auto ret{ base64{}.decode("TWFueSBoYW5kcyBtYWtlIGxpZ2h0IHdvcms=") };
    EXPECT_EQ((std::string{ ret.begin(), ret.end() }), std::string{ "Many hands make light work" });
}
TEST(decode, Many_hands_make_light_work_without_padding) {
    auto ret{ base64{}.decode("TWFueSBoYW5kcyBtYWtlIGxpZ2h0IHdvcms") };
    EXPECT_EQ((std::string{ ret.begin(), ret.end() }), std::string{ "Many hands make light work" });
}
TEST(decode, Many_hands_make_light_work_with_characters_not_in_the_decoding_table) {
    auto ret{ base64{}.decode("##TWFueSBoYW5kcyBtYW==tlIGxpZ2h0IHdvcms@@") };
    EXPECT_EQ((std::string{ ret.begin(), ret.end() }), std::string{ "Many hands make light work" });
}
