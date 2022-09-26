#include "../bitcoin/samples.h"
#include "chapter_12_networking_and_services/json/bitcoin.h"
#include "chapter_12_networking_and_services/bitcoin/samples.h"

#include "nlohmann/json.hpp"

#include "gtest/gtest.h"

using namespace tmcppc::bitcoin;


TEST(exchange_rate, from_json) {
    nlohmann::json j = nlohmann::json::parse(samples::connector_response_text::exchange_rate_eur);
    exchange_rate er{};
    from_json(j, er);
    EXPECT_EQ(er, samples::exchange_rate_eur);
}
TEST(exchange_rates, from_json) {
    nlohmann::json j = nlohmann::json::parse(samples::connector_response_text::exchange_rates_eur_gbp_usd);
    exchange_rates ers{};
    from_json(j, ers);
    EXPECT_EQ(ers, samples::exchange_rates_eur_gbp_usd);
}
