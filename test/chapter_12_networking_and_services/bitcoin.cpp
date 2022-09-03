#include "chapter_12_networking_and_services/bitcoin.h"
#include "chapter_12_networking_and_services/bitcoin/samples.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <fmt/format.h>
#include <sstream>  // ostringstream

using namespace rtc::pretty_print;
using namespace tmcppc::bitcoin;


TEST(exchange_rate, print) {
    std::ostringstream oss{};
    samples::exchange_rate_eur.print(oss);
    EXPECT_EQ(oss.str(), samples::exchange_rate_eur_output);
}
TEST(exchange_rate, operator_insertion) {
    std::ostringstream oss{};
    oss << samples::exchange_rate_eur;
    EXPECT_EQ(oss.str(), samples::exchange_rate_eur_output);
}
TEST(exchange_rate, fmt_format) {
    EXPECT_EQ(fmt::format("{}", samples::exchange_rate_eur), samples::exchange_rate_eur_output);
}
TEST(exchange_rate, operator_spaceship) {
    auto& er1{ samples::exchange_rate_eur };
    auto& er2{ samples::exchange_rate_eur };
    auto& er3{ samples::exchange_rate_gbp };
    EXPECT_TRUE(er1 == er2);
    EXPECT_TRUE(er1 != er3);
    EXPECT_TRUE(er1 < er3);
    EXPECT_TRUE(er3 > er1);
    EXPECT_TRUE(er1 <= er2);
    EXPECT_TRUE(er1 <= er3);
    EXPECT_TRUE(er2 >= er1);
    EXPECT_TRUE(er3 >= er1);
}

TEST(exchange_rates, print_empty_data) {
    std::ostringstream oss{};
    exchange_rates{}.print(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("{}"));
}
TEST(exchange_rates, print) {
    std::ostringstream oss{};
    samples::exchange_rates_eur_gbp.print(oss);
    EXPECT_EQ(oss.str(), samples::exchange_rates_eur_gbp_output);
}
TEST(exchange_rates, operator_insertion) {
    std::ostringstream oss{};
    oss << samples::exchange_rates_eur_gbp;
    EXPECT_EQ(oss.str(), samples::exchange_rates_eur_gbp_output);
}
TEST(exchange_rates, fmt_format) {
    EXPECT_THAT(fmt::format("{}", samples::exchange_rates_eur_gbp), samples::exchange_rates_eur_gbp_output);
}
TEST(exchange_rates, operator_spaceship) {
    auto& ers1{ samples::exchange_rates_eur_gbp };
    auto& ers2{ samples::exchange_rates_eur_gbp };
    auto& ers3{ samples::exchange_rates_eur_usd };
    EXPECT_TRUE(ers1 == ers2);
    EXPECT_TRUE(ers1 != ers3);
    EXPECT_TRUE(ers1 < ers3);
    EXPECT_TRUE(ers3 > ers1);
    EXPECT_TRUE(ers1 <= ers2);
    EXPECT_TRUE(ers1 <= ers3);
    EXPECT_TRUE(ers2 >= ers1);
    EXPECT_TRUE(ers3 >= ers1);
}
