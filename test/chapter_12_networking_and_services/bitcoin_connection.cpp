#include "chapter_12_networking_and_services/bitcoin.h"
#include "bitcoin_connection/mock.h"
#include "bitcoin_connection/samples.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace tmcppc::bitcoin;


TEST(bitcoin_connection, DISABLED_get_current_exchange_rates_and_connector_throws) {
    std::unique_ptr<connector_adaptor> connector_up{ std::make_unique<connector_mock>() };
    const auto& connector{ *(dynamic_cast<connector_mock*>(connector_up.get())) };
    EXPECT_CALL(connector, get_current_exchange_rates())
        .WillOnce(::testing::Throw(bitcoin_connection_error{ "Couldn't resolve host name" }));

    bitcoin_connection connection{ std::move(connector_up) };
    EXPECT_THROW((void) connection.get_current_exchange_rates(), bitcoin_connection_error);
}


TEST(bitcoin_connection, DISABLED_get_current_exchange_rates_and_connector_returns_a_correct_response) {
    std::unique_ptr<connector_adaptor> connector_up{ std::make_unique<connector_mock>() };
    const auto& connector{ *(dynamic_cast<connector_mock*>(connector_up.get())) };
    EXPECT_CALL(connector, get_current_exchange_rates())
        .WillOnce(::testing::Return(samples::connector_adaptor_response));

    bitcoin_connection connection{ std::move(connector_up) };
    EXPECT_EQ(
        connection.get_current_exchange_rates(),
        (exchange_rates{ .data = {
            { "EUR" , exchange_rate{ "EUR", 22777.77, 22777.77, 22777.77, 22777.77 } },
            { "GBP" , exchange_rate{ "GBP", 19210.63, 19210.63, 19210.63, 19210.63 } },
            { "USD" , exchange_rate{ "USD", 23187.23, 23187.23, 23187.23, 23187.23 } }
        }})
    );
}
