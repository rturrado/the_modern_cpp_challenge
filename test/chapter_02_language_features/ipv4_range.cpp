#include "chapter_02_language_features/ipv4.h"
#include "chapter_02_language_features/ipv4_range.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // istringstream, ostringstream


TEST(ipv4_iterator, DISABLED_operator_star) {
    tmcppc::ipv4_iterator it{ tmcppc::ipv4{ "1.2.3.4" } };
    EXPECT_EQ(*it, tmcppc::ipv4{ "1.2.3.4" });
}

TEST(ipv4_iterator, DISABLED_operator_pointer) {
    tmcppc::ipv4_iterator it{ tmcppc::ipv4{ "1.2.3.4" } };
    EXPECT_EQ(it->to_string(), "1.2.3.4");
}

TEST(ipv4_iterator, DISABLED_pre_increment) {
    tmcppc::ipv4_iterator it{ tmcppc::ipv4{ "1.2.3.4" } };
    EXPECT_EQ(*++it, tmcppc::ipv4{ "1.2.3.5" });
}

TEST(ipv4_iterator, DISABLED_post_increment) {
    tmcppc::ipv4_iterator it{ tmcppc::ipv4{ "1.2.3.4" } };
    EXPECT_EQ(*it++, tmcppc::ipv4{ "1.2.3.4" });
    EXPECT_EQ(*it, tmcppc::ipv4{ "1.2.3.5" });
}

TEST(ipv4_iterator, DISABLED_equals) {
    EXPECT_EQ(tmcppc::ipv4_iterator{ tmcppc::ipv4{ "1.2.3.4" } }, tmcppc::ipv4_iterator{ tmcppc::ipv4{ "1.2.3.4" } });
}

TEST(ipv4_iterator, DISABLED_distinct) {
    EXPECT_NE(tmcppc::ipv4_iterator{ tmcppc::ipv4{ "1.2.3.4" } }, tmcppc::ipv4_iterator{ tmcppc::ipv4{ "1.2.3.5" } });
}


TEST(ipv4_range, DISABLED_is_an_lvalue) {
    const tmcppc::ipv4_range range{ tmcppc::ipv4{ "10.10.10.10" }, tmcppc::ipv4{ "10.10.10.15" } };
    std::ostringstream oss{};
    for (const auto& address : range) {
        oss << address << "\n";
    }
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "10.10.10.10\n"
        "10.10.10.11\n"
        "10.10.10.12\n"
        "10.10.10.13\n"
        "10.10.10.14\n"
    ));
}

TEST(ipv4_range, DISABLED_is_an_rvalue_but_constructed_from_two_ipv4_lvalues) {
    tmcppc::ipv4 a1{ "10.10.10.10" };
    tmcppc::ipv4 a2{ "10.10.10.15" };
    std::ostringstream oss{};
    for (auto&& address : tmcppc::ipv4_range{ a1, a2 }) {
        oss << address << "\n";
    }
    oss << a2 << "\n";
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "10.10.10.10\n"
        "10.10.10.11\n"
        "10.10.10.12\n"
        "10.10.10.13\n"
        "10.10.10.14\n"
        "10.10.10.15\n"
    ));
}

TEST(ipv4_range, DISABLED_is_an_rvalue_and_constructed_from_two_ipv4_rvalues) {
    std::ostringstream oss{};
    for (auto&& address : tmcppc::ipv4_range{ tmcppc::ipv4{ "10.10.10.10" }, tmcppc::ipv4{ "10.10.10.15" } }) {
        oss << address << "\n";
    }
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "10.10.10.10\n"
        "10.10.10.11\n"
        "10.10.10.12\n"
        "10.10.10.13\n"
        "10.10.10.14\n"
    ));
}

TEST(ipv4_range, DISABLED_begin_end) {
    tmcppc::ipv4_range range{ tmcppc::ipv4{ "10.10.10.10" }, tmcppc::ipv4{ "10.10.10.15" } };
    std::ostringstream oss{};
    for (auto it{ range.begin() }; it != range.end(); ++it) {
        oss << *it << "\n";
    }
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "10.10.10.10\n"
        "10.10.10.11\n"
        "10.10.10.12\n"
        "10.10.10.13\n"
        "10.10.10.14\n"
    ));
}


TEST(ipv4_range, DISABLED_begin_end_on_const_range) {
    const tmcppc::ipv4_range range{ tmcppc::ipv4{ "10.10.10.10" }, tmcppc::ipv4{ "10.10.10.15" } };
    std::ostringstream oss{};
    for (auto it{ range.begin() }; it != range.end(); ++it) {
        oss << *it << "\n";
    }
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "10.10.10.10\n"
        "10.10.10.11\n"
        "10.10.10.12\n"
        "10.10.10.13\n"
        "10.10.10.14\n"
    ));
}

TEST(ipv4_range, DISABLED_cbegin_cend) {
    const tmcppc::ipv4_range range{ tmcppc::ipv4{ "10.10.10.10" }, tmcppc::ipv4{ "10.10.10.15" } };
    std::ostringstream oss{};
    for (auto it{ range.cbegin() }; it != range.cend(); ++it) {
        oss << *it << "\n";
    }
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "10.10.10.10\n"
        "10.10.10.11\n"
        "10.10.10.12\n"
        "10.10.10.13\n"
        "10.10.10.14\n"
    ));
}
