#include "chapter_02_language_features/ipv4.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // istringstream, ostringstream
#include <string>


TEST(ipv4, DISABLED_default_constructor) {
    tmcppc::ipv4 address{};
    EXPECT_EQ(address.to_string(), "0.0.0.0");
    EXPECT_EQ(address.to_ulong(), static_cast<unsigned long>(0));
}

TEST(ipv4_string_constructor, DISABLED_abc) { EXPECT_THROW(tmcppc::ipv4{ std::string{ "abc" } }, tmcppc::invalid_ipv4_address_error); }
TEST(ipv4_string_constructor, DISABLED_n_127_0_0_999) { EXPECT_THROW(tmcppc::ipv4{ std::string{ "127.0.0.999" } }, tmcppc::invalid_ipv4_address_error); }

TEST(ipv4_char_star_constructor, DISABLED_abc) { EXPECT_THROW(tmcppc::ipv4{ "abc" }, tmcppc::invalid_ipv4_address_error); }
TEST(ipv4_char_star_constructor, DISABLED_n_127_0_0_999) { EXPECT_THROW(tmcppc::ipv4{ "abc" }, tmcppc::invalid_ipv4_address_error); }

TEST(ipv4_uint32_t_constructor, DISABLED_n_127_0_0_1) {
    EXPECT_EQ(tmcppc::ipv4{ 0x7f'00'00'01 }.to_ulong(), static_cast<unsigned long>(0x7f'00'00'01));
}
TEST(ipv4_octets_constructor, DISABLED_n_127_0_0_1) {
    tmcppc::ipv4 address{ 0x7f, 0x00, 0x00, 0x01 };
    EXPECT_EQ(address.to_ulong(), static_cast<unsigned long>(0x7f'00'00'01));
}

TEST(ipv4_pre_increment, DISABLED_n_127_0_0_1) {
    tmcppc::ipv4 address{ "127.0.0.1"};
    EXPECT_EQ(++address, tmcppc::ipv4{ "127.0.0.2" });
}
TEST(ipv4_pre_increment, DISABLED_n_255_255_255_255) {
    tmcppc::ipv4 address{ "255.255.255.255" };
    EXPECT_EQ(++address, tmcppc::ipv4{ "0.0.0.0" });
}
TEST(ipv4_post_increment, DISABLED_n_127_0_0_1) {
    tmcppc::ipv4 address{ "127.0.0.1" };
    EXPECT_EQ(address++, tmcppc::ipv4{ "127.0.0.1" });
    EXPECT_EQ(address, tmcppc::ipv4{ "127.0.0.2" });
}
TEST(ipv4_post_increment, DISABLED_n_255_255_255_255) {
    tmcppc::ipv4 address{ "255.255.255.255" };
    EXPECT_EQ(address++, tmcppc::ipv4{ "255.255.255.255" });
    EXPECT_EQ(address, tmcppc::ipv4{ "0.0.0.0" });
}

TEST(ipv4, DISABLED_equals) { EXPECT_EQ(tmcppc::ipv4{ "127.0.0.1" }, tmcppc::ipv4{ 0x7f'00'00'01 }); }
TEST(ipv4_less_than, DISABLED_ok) { EXPECT_TRUE(tmcppc::ipv4{ "1.1.1.1" } < tmcppc::ipv4{ "1.2.1.1" }); }
TEST(ipv4_less_than, DISABLED_error) { EXPECT_FALSE(tmcppc::ipv4{ "1.1.1.1" } < tmcppc::ipv4{ "1.1.1.1" }); }

TEST(ipv4_operator_insertion, DISABLED_n_127_0_0_1) {
    std::ostringstream oss{};
    oss << tmcppc::ipv4{ "127.0.0.1" };
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("127.0.0.1"));
}
TEST(ipv4_operator_extraction, DISABLED_n_127_0_0_1) {
    std::istringstream iss{ "127.0.0.1" };
    tmcppc::ipv4 address{};
    iss >> address;
    EXPECT_EQ(address, tmcppc::ipv4{ "127.0.0.1" });
}
TEST(validate_ipv4_address, DISABLED_abc) {
    tmcppc::ipv4 address{};
    auto ret{ validate_ipv4_address("abc", address) };
    EXPECT_FALSE(ret);
    EXPECT_EQ(address.to_string(), "0.0.0.0");
    EXPECT_EQ(address.to_ulong(), static_cast<unsigned long>(0));
}
TEST(validate_ipv4_address, DISABLED_n_127_0_0_999) {
    tmcppc::ipv4 address{};
    auto ret{ validate_ipv4_address("127.0.0.999", address) };
    EXPECT_FALSE(ret);
    EXPECT_EQ(address.to_string(), "0.0.0.0");
    EXPECT_EQ(address.to_ulong(), static_cast<unsigned long>(0));
}
TEST(validate_ipv4_address, DISABLED_n_127_0_0_1) {
    tmcppc::ipv4 address{};
    auto ret{ validate_ipv4_address("127.0.0.1", address) };
    EXPECT_TRUE(ret);
    EXPECT_EQ(address.to_string(), "127.0.0.1");
    EXPECT_EQ(address.to_ulong(), static_cast<unsigned long>(0x7f'00'00'01));
}
