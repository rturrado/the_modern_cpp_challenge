#include "chapter_12_networking_and_services/fizz_buzz.h"
#include "tcp/mock.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>  // make_unique, unique_ptr
#include <string>
#include <string_view>
#include <system_error>  // error_code, system_category
#include <utility>  // move

using namespace ::testing;
using namespace std::string_literals;
using namespace std::string_view_literals;
using namespace tmcppc::fizz_buzz;
using namespace tmcppc::tcp;


TEST(remove_newline, empty_text) { EXPECT_TRUE(remove_newline("").empty()); }
TEST(remove_newline, text_without_newline) { EXPECT_EQ(remove_newline("abcd"), "abcd"); }
TEST(remove_newline, text_with_newline_at_the_beggining) { EXPECT_EQ(remove_newline("\nabcd"), "\nabcd"); }
TEST(remove_newline, text_with_newline_at_the_middle) { EXPECT_EQ(remove_newline("ab\ncd"), "ab\ncd"); }
TEST(remove_newline, text_with_newline_at_the_end) { EXPECT_EQ(remove_newline("abcd\n"), "abcd"); }


TEST(read_line, read_line_until_returns_ab_and_newline) {
    std::unique_ptr<connector> connector_up{ std::make_unique<connector_mock>() };
    auto& connector{ *(dynamic_cast<connector_mock*>(connector_up.get())) };
    std::string ret{};
    std::error_code ec{};
    EXPECT_CALL(connector, read_until(ret, "\n"sv, ec))
        .WillOnce(DoAll(SetArgReferee<0>("ab\n"), Return(3)));
    std::ostringstream oss{};
    EXPECT_EQ(read_line(oss, connector_up.get()), "ab");
}
TEST(read_line, read_line_until_returns_error_code) {
    std::unique_ptr<connector> connector_up{ std::make_unique<connector_mock>() };
    auto& connector{ *(dynamic_cast<connector_mock*>(connector_up.get())) };
    std::string ret{};
    std::error_code ec{};
    EXPECT_CALL(connector, read_until(ret, "\n"sv, ec))
        .WillOnce(DoAll(SetArgReferee<2>(std::error_code{1, std::system_category()}), Return(0)));
    std::ostringstream oss{};
    (void) read_line(oss, connector_up.get());
    EXPECT_THAT(oss.str(), HasSubstr("Error: reading: "));
}


TEST(write_line, write_returns_error_code) {
    std::unique_ptr<connector> connector_up{ std::make_unique<connector_mock>() };
    auto& connector{ *(dynamic_cast<connector_mock*>(connector_up.get())) };
    std::string message{ "abcd" };
    std::error_code ec{};
    EXPECT_CALL(connector, write(message + "\n", ec))
        .WillOnce(DoAll(SetArgReferee<1>(std::error_code{ 1, std::system_category() })));
    std::ostringstream oss{};
    write_line(oss, connector_up.get(), message);
    EXPECT_THAT(oss.str(), HasSubstr("Error: writing: "));
}


TEST(server, run) {
    std::ostringstream oss{};
    std::unique_ptr<connector> server_connector_up{ std::make_unique<connector_mock>() };
    auto& server_connector{ *(dynamic_cast<connector_mock*>(server_connector_up.get())) };
    server s{ oss, std::move(server_connector_up) };

    EXPECT_CALL(server_connector, accept());

    EXPECT_CALL(server_connector, read_until(_, "\n"sv, _))
        .WillOnce(DoAll(SetArgReferee<0>("1\n"), Return(2)))
        .WillOnce(DoAll(SetArgReferee<0>("3\n"), Return(2)))
        .WillOnce(DoAll(SetArgReferee<0>("5\n"), Return(2)))
        .WillOnce(DoAll(SetArgReferee<0>("15\n"), Return(3)))
        .WillOnce(DoAll(SetArgReferee<0>("quit\n"), Return(5)));

    EXPECT_CALL(server_connector, write("1\n", _));
    EXPECT_CALL(server_connector, write("fizz\n", _));
    EXPECT_CALL(server_connector, write("buzz\n", _));
    EXPECT_CALL(server_connector, write("fizz-buzz\n", _));

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
    std::unique_ptr<connector> client_connector_up{ std::make_unique<connector_mock>() };
    auto& client_connector{ *(dynamic_cast<connector_mock*>(client_connector_up.get())) };
    client c{ iss, oss, std::move(client_connector_up) };

    EXPECT_CALL(client_connector, connect());

    EXPECT_CALL(client_connector, write("1\n", _));
    EXPECT_CALL(client_connector, write("3\n", _));
    EXPECT_CALL(client_connector, write("5\n", _));
    EXPECT_CALL(client_connector, write("15\n", _));
    EXPECT_CALL(client_connector, write("quit\n", _));

    EXPECT_CALL(client_connector, read_until(_, "\n"sv, _))
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
