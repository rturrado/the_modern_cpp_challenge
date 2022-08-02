#include "chapter_12_networking_and_services/fizz_buzz.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>  // make_unique, unique_ptr
#include <sstream>  // ostringstream
#include <string>
#include <string_view>
#include <system_error>  // error_code, system_category

#define BOOST_ASIO_STANDALONE
#include <asio.hpp>
#include <boost/system/error_code.hpp>

using namespace tmcppc::fizz_buzz;
using namespace std::string_literals;
using namespace std::string_view_literals;
using namespace ::testing;


class tcp_connection_mock : public tcp_connection {
public:
    MOCK_METHOD((size_t), read_until, (std::string& data, std::string_view delimiter, std::error_code& ec), (override));
    MOCK_METHOD((void), write, (const std::string& message, std::error_code& ec), (override));
    MOCK_METHOD((void), accept, (), (override));
    MOCK_METHOD((void), connect, (), (override));
};


TEST(remove_newline, empty_text) { EXPECT_TRUE(remove_newline("").empty()); }
TEST(remove_newline, text_without_newline) { EXPECT_EQ(remove_newline("abcd"), "abcd"); }
TEST(remove_newline, text_with_newline_at_the_beggining) { EXPECT_EQ(remove_newline("\nabcd"), "\nabcd"); }
TEST(remove_newline, text_with_newline_at_the_middle) { EXPECT_EQ(remove_newline("ab\ncd"), "ab\ncd"); }
TEST(remove_newline, text_with_newline_at_the_end) { EXPECT_EQ(remove_newline("abcd\n"), "abcd"); }


TEST(read_line, read_line_until_returns_ab_and_newline) {
    tcp_connection_mock connection{};
    std::string ret{};
    std::error_code ec{};
    EXPECT_CALL(connection, read_until(ret, "\n"sv, ec))
        .WillOnce(DoAll(SetArgReferee<0>("ab\n"), Return(3)));
    std::ostringstream oss{};
    EXPECT_EQ(read_line(oss, &connection), "ab");
}
TEST(read_line, read_line_until_returns_error_code) {
    tcp_connection_mock connection{};
    std::string ret{};
    std::error_code ec{};
    EXPECT_CALL(connection, read_until(ret, "\n"sv, ec))
        .WillOnce(DoAll(SetArgReferee<2>(std::error_code{1, std::system_category()}), Return(0)));
    std::ostringstream oss{};
    (void) read_line(oss, &connection);
    EXPECT_THAT(oss.str(), HasSubstr("Error: reading: "));
}


TEST(write_line, write_returns_error_code) {
    tcp_connection_mock connection{};
    std::string message{ "abcd" };
    std::error_code ec{};
    EXPECT_CALL(connection, write(message + "\n", ec))
        .WillOnce(DoAll(SetArgReferee<1>(std::error_code{ 1, std::system_category() })));
    std::ostringstream oss{};
    write_line(oss, &connection, message);
    EXPECT_THAT(oss.str(), HasSubstr("Error: writing: "));
}


TEST(server, run) {
    std::ostringstream oss{};
    std::unique_ptr<tcp_connection> server_connection_up{ std::make_unique<tcp_connection_mock>() };
    auto& server_connection{ *(dynamic_cast<tcp_connection_mock*>(server_connection_up.get())) };
    server s{ oss, std::move(server_connection_up) };

    EXPECT_CALL(server_connection, accept());

    EXPECT_CALL(server_connection, read_until(_, "\n"sv, _))
        .WillOnce(DoAll(SetArgReferee<0>("1\n"), Return(2)))
        .WillOnce(DoAll(SetArgReferee<0>("3\n"), Return(2)))
        .WillOnce(DoAll(SetArgReferee<0>("5\n"), Return(2)))
        .WillOnce(DoAll(SetArgReferee<0>("15\n"), Return(3)))
        .WillOnce(DoAll(SetArgReferee<0>("quit\n"), Return(5)));

    EXPECT_CALL(server_connection, write("1\n", _));
    EXPECT_CALL(server_connection, write("fizz\n", _));
    EXPECT_CALL(server_connection, write("buzz\n", _));
    EXPECT_CALL(server_connection, write("fizz-buzz\n", _));

    s.run();

    EXPECT_THAT(oss.str(), HasSubstr("[server] Starting\n"));
    EXPECT_THAT(oss.str(), HasSubstr("[server] Exiting\n"));
}


TEST(client, run) {
    std::istringstream iss{
        "1\n"
        "3\n"
        "5\n"
        "15\n"
        "quit\n"
    };
    std::ostringstream oss{};
    std::unique_ptr<tcp_connection> client_connection_up{ std::make_unique<tcp_connection_mock>() };
    auto& client_connection{ *(dynamic_cast<tcp_connection_mock*>(client_connection_up.get())) };
    client c{ iss, oss, std::move(client_connection_up) };

    EXPECT_CALL(client_connection, connect());

    EXPECT_CALL(client_connection, write("1\n", _));
    EXPECT_CALL(client_connection, write("3\n", _));
    EXPECT_CALL(client_connection, write("5\n", _));
    EXPECT_CALL(client_connection, write("15\n", _));
    EXPECT_CALL(client_connection, write("quit\n", _));

    EXPECT_CALL(client_connection, read_until(_, "\n"sv, _))
        .WillOnce(DoAll(SetArgReferee<0>("1\n"), Return(2)))
        .WillOnce(DoAll(SetArgReferee<0>("fizz\n"), Return(5)))
        .WillOnce(DoAll(SetArgReferee<0>("buzz\n"), Return(5)))
        .WillOnce(DoAll(SetArgReferee<0>("fizz-buzz\n"), Return(10)));

    c.run();

    EXPECT_THAT(oss.str(), ::testing::HasSubstr("[client] Starting\n"));
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "[client] Please enter a number between 1 and 99 ('quit' to finish the game): "  // 1
        "[client] Says '1'\n"
        "[server] Says '1'\n"
        "[client] Please enter a number between 1 and 99 ('quit' to finish the game): "  // 3
        "[client] Says '3'\n"
        "[server] Says 'fizz'\n"
        "[client] Please enter a number between 1 and 99 ('quit' to finish the game): "  // 5
        "[client] Says '5'\n"
        "[server] Says 'buzz'\n"
        "[client] Please enter a number between 1 and 99 ('quit' to finish the game): "  // 15
        "[client] Says '15'\n"
        "[server] Says 'fizz-buzz'\n"
        "[client] Please enter a number between 1 and 99 ('quit' to finish the game): "  // quit
        "[client] Says 'quit'\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("[client] Exiting\n"));
}
