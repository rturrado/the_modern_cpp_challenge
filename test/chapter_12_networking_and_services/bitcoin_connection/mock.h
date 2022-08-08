#pragma once

#include "chapter_12_networking_and_services/bitcoin_connection.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <string>


namespace tmcppc::bitcoin {
    struct connector_mock : public connector_adaptor {
        MOCK_METHOD((std::string), get_current_exchange_rates, (), (const, override));
    };
}  // namespace tmcppc::bitcoin
