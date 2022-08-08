#pragma once

#include "chapter_12_networking_and_services/tcp_connection.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <string>
#include <string_view>
#include <system_error>  // error_code


namespace tmcppc::tcp {
    struct connector_mock : public connector {
        MOCK_METHOD((size_t), read_until, (std::string& data, std::string_view delimiter, std::error_code& ec), (override));
        MOCK_METHOD((void), write, (const std::string& message, std::error_code& ec), (override));
        MOCK_METHOD((void), accept, (), (override));
        MOCK_METHOD((void), connect, (), (override));
    };
}  // naespace tmcppc::tcp
