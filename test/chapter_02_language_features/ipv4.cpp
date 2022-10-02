#include "chapter_02_language_features/ipv4.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <string>

using namespace tmcppc::network;


TEST(ipv4, default_constructor) {
    ipv4 address{};
    EXPECT_EQ(address.to_string(), "0.0.0.0");
    EXPECT_EQ(address.to_ulong(), static_cast<unsigned long>(0));
}

TEST(ipv4_string_constructor, abc) { EXPECT_THROW(ipv4{ std::string{ "abc" } }, invalid_ipv4_address_error); }
TEST(ipv4_string_constructor, n_127_0_0_999) { EXPECT_THROW(ipv4{ std::string{ "127.0.0.999" } }, invalid_ipv4_address_error); }

TEST(ipv4_char_star_constructor, abc) { EXPECT_THROW(ipv4{ "abc" }, invalid_ipv4_address_error); }
TEST(ipv4_char_star_constructor, n_127_0_0_999) { EXPECT_THROW(ipv4{ "abc" }, invalid_ipv4_address_error); }

TEST(ipv4_uint32_t_constructor, n_127_0_0_1) {
    EXPECT_EQ(ipv4{ 0x7f'00'00'01 }.to_ulong(), static_cast<unsigned long>(0x7f'00'00'01));
}
TEST(ipv4_octets_constructor, n_127_0_0_1) {
    ipv4 address{ 0x7f, 0x00, 0x00, 0x01 };
    EXPECT_EQ(address.to_ulong(), static_cast<unsigned long>(0x7f'00'00'01));
}

TEST(ipv4_pre_increment, n_127_0_0_1) {
    ipv4 address{ "127.0.0.1"};
    EXPECT_EQ(++address, ipv4{ "127.0.0.2" });
}
TEST(ipv4_pre_increment, n_255_255_255_255) {
    ipv4 address{ "255.255.255.255" };
    EXPECT_EQ(++address, ipv4{ "0.0.0.0" });
}
TEST(ipv4_post_increment, n_127_0_0_1) {
    ipv4 address{ "127.0.0.1" };
    EXPECT_EQ(address++, ipv4{ "127.0.0.1" });
    EXPECT_EQ(address, ipv4{ "127.0.0.2" });
}
TEST(ipv4_post_increment, n_255_255_255_255) {
    ipv4 address{ "255.255.255.255" };
    EXPECT_EQ(address++, ipv4{ "255.255.255.255" });
    EXPECT_EQ(address, ipv4{ "0.0.0.0" });
}

TEST(ipv4, equals) { EXPECT_EQ(ipv4{ "127.0.0.1" }, ipv4{ 0x7f'00'00'01 }); }
TEST(ipv4_less_than, ok) { EXPECT_TRUE(ipv4{ "1.1.1.1" } < ipv4{ "1.2.1.1" }); }
TEST(ipv4_less_than, error) { EXPECT_FALSE(ipv4{ "1.1.1.1" } < ipv4{ "1.1.1.1" }); }

TEST(ipv4_operator_insertion, n_127_0_0_1) {
    std::ostringstream oss{};
    oss << ipv4{ "127.0.0.1" };
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("127.0.0.1"));
}
TEST(ipv4_operator_extraction, n_127_0_0_1) {
    std::istringstream iss{ "127.0.0.1" };
    ipv4 address{};
    iss >> address;
    EXPECT_EQ(address, ipv4{ "127.0.0.1" });
}
TEST(validate_ipv4_address, abc) {
    ipv4 address{};
    auto ret{ validate_ipv4_address("abc", address) };
    EXPECT_FALSE(ret);
    EXPECT_EQ(address.to_string(), "0.0.0.0");
    EXPECT_EQ(address.to_ulong(), static_cast<unsigned long>(0));
}
TEST(validate_ipv4_address, n_127_0_0_999) {
    ipv4 address{};
    auto ret{ validate_ipv4_address("127.0.0.999", address) };
    EXPECT_FALSE(ret);
    EXPECT_EQ(address.to_string(), "0.0.0.0");
    EXPECT_EQ(address.to_ulong(), static_cast<unsigned long>(0));
}
TEST(validate_ipv4_address, n_127_0_0_1) {
    ipv4 address{};
    auto ret{ validate_ipv4_address("127.0.0.1", address) };
    EXPECT_TRUE(ret);
    EXPECT_EQ(address.to_string(), "127.0.0.1");
    EXPECT_EQ(address.to_ulong(), static_cast<unsigned long>(0x7f'00'00'01));
}
