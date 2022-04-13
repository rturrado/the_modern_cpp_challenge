#include "chapter_02_language_features/ipv4.h"
#include "chapter_02_language_features/ipv4_range.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // istringstream, ostringstream


TEST(ipv4_iterator, operator_star) {
    ipv4_iterator it{ ipv4{ "1.2.3.4" } };
    EXPECT_EQ(*it, ipv4{ "1.2.3.4" });
}

TEST(ipv4_iterator, operator_pointer) {
    ipv4_iterator it{ ipv4{ "1.2.3.4" } };
    EXPECT_EQ(it->to_string(), "1.2.3.4");
}

TEST(ipv4_iterator, pre_increment) {
    ipv4_iterator it{ ipv4{ "1.2.3.4" } };
    EXPECT_EQ(*++it, ipv4{ "1.2.3.5" });
}

TEST(ipv4_iterator, post_increment) {
    ipv4_iterator it{ ipv4{ "1.2.3.4" } };
    EXPECT_EQ(*it++, ipv4{ "1.2.3.4" });
    EXPECT_EQ(*it, ipv4{ "1.2.3.5" });
}

TEST(ipv4_iterator, equals) {
    EXPECT_EQ(ipv4_iterator{ ipv4{ "1.2.3.4" } }, ipv4_iterator{ ipv4{ "1.2.3.4" } });
}

TEST(ipv4_iterator, distinct) {
    EXPECT_NE(ipv4_iterator{ ipv4{ "1.2.3.4" } }, ipv4_iterator{ ipv4{ "1.2.3.5" } });
}


TEST(ipv4_range, is_an_lvalue) {
    const ipv4_range range{ ipv4{ "10.10.10.10" }, ipv4{ "10.10.10.15" } };
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

TEST(ipv4_range, is_an_rvalue_but_constructed_from_two_ipv4_lvalues) {
    ipv4 a1{ "10.10.10.10" };
    ipv4 a2{ "10.10.10.15" };
    std::ostringstream oss{};
    for (auto&& address : ipv4_range{ a1, a2 }) {
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

TEST(ipv4_range, is_an_rvalue_and_constructed_from_two_ipv4_rvalues) {
    std::ostringstream oss{};
    for (auto&& address : ipv4_range{ ipv4{ "10.10.10.10" }, ipv4{ "10.10.10.15" } }) {
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

TEST(ipv4_range, begin_end) {
    ipv4_range range{ ipv4{ "10.10.10.10" }, ipv4{ "10.10.10.15" } };
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


TEST(ipv4_range, begin_end_on_const_range) {
    const ipv4_range range{ ipv4{ "10.10.10.10" }, ipv4{ "10.10.10.15" } };
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

TEST(ipv4_range, cbegin_cend) {
    const ipv4_range range{ ipv4{ "10.10.10.10" }, ipv4{ "10.10.10.15" } };
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
