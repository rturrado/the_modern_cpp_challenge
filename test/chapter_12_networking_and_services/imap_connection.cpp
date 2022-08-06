#include "chapter_12_networking_and_services/imap_connection.h"
#include "imap_connection/mock.h"
#include "imap_connection/samples.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <string_view>

using namespace std::string_view_literals;
using namespace tmcppc::imap;


TEST(imap_connection, get_mailbox_folders_and_provider_throws) {
    std::unique_ptr<connector_adaptor> connector_up{ std::make_unique<connector_mock>() };
    const auto& connector{ *(dynamic_cast<connector_mock*>(connector_up.get())) };
    EXPECT_CALL(connector, get_mailbox_folders())
        .WillOnce(::testing::Throw(imap_connection_error{ "Login denied" }));

    imap_connection connection{ std::move(connector_up) };
    EXPECT_THROW((void) connection.get_mailbox_folders(), imap_connection_error);
}
TEST(imap_connection, get_mailbox_folders_and_provider_returns_a_correct_response) {
    std::unique_ptr<connector_adaptor> connector_up{ std::make_unique<connector_mock>() };
    const auto& connector{ *(dynamic_cast<connector_mock*>(connector_up.get())) };
    EXPECT_CALL(connector, get_mailbox_folders())
        .WillOnce(::testing::Return(R"(* LIST (\HasNoChildren) "/" "test/tmcppc/problem_98")""\r\n"));

    imap_connection connection{ std::move(connector_up) };
    EXPECT_THAT(connection.get_mailbox_folders(), ::testing::ElementsAre("test/tmcppc/problem_98"));
}


TEST(imap_connection, get_unread_email_ids_response_and_provider_throws) {
    std::unique_ptr<connector_adaptor> connector_up{ std::make_unique<connector_mock>() };
    const auto& connector{ *(dynamic_cast<connector_mock*>(connector_up.get())) };
    EXPECT_CALL(connector, get_unread_email_ids("wrong_folder_name"sv))
        .WillOnce(::testing::Throw(imap_connection_error{ "Login denied" }));

    imap_connection connection{ std::move(connector_up) };
    EXPECT_THROW((void) connection.get_unread_email_ids("wrong_folder_name"sv), imap_connection_error);
}
TEST(imap_connection, get_unread_email_ids_and_provider_returns_a_correct_response) {
    std::unique_ptr<connector_adaptor> connector_up{ std::make_unique<connector_mock>() };
    const auto& connector{ *(dynamic_cast<connector_mock*>(connector_up.get())) };
    EXPECT_CALL(connector, get_unread_email_ids("test/tmcppc/problem_98"sv))
        .WillOnce(::testing::Return(R"(* SEARCH 1)""\r\n"));

    imap_connection connection{ std::move(connector_up) };
    EXPECT_THAT(connection.get_unread_email_ids("test/tmcppc/problem_98"sv), ::testing::ElementsAre(1));
}


TEST(imap_connection, get_email_and_provider_throws) {
    std::unique_ptr<connector_adaptor> connector_up{ std::make_unique<connector_mock>() };
    const auto& connector{ *(dynamic_cast<connector_mock*>(connector_up.get())) };
    EXPECT_CALL(connector, get_email("inbox"sv, 333))
        .WillOnce(::testing::Throw(imap_connection_error{ "Login denied" }));

    imap_connection connection{ std::move(connector_up) };
    EXPECT_THROW((void) connection.get_email("inbox"sv, 333), imap_connection_error);
}
TEST(imap_connection, get_email_and_provider_returns_a_correct_response) {
    std::unique_ptr<connector_adaptor> connector_up{ std::make_unique<connector_mock>() };
    const auto& connector{ *(dynamic_cast<connector_mock*>(connector_up.get())) };
    EXPECT_CALL(connector, get_email("test/tmcppc/problem_98"sv, 1))
        .WillOnce(::testing::Return(samples::email));

    imap_connection connection{ std::move(connector_up) };
    EXPECT_EQ(connection.get_email("test/tmcppc/problem_98"sv, 1), samples::email);
}


TEST(imap_connection, get_email_subject_and_provider_throws) {
    std::unique_ptr<connector_adaptor> connector_up{ std::make_unique<connector_mock>() };
    const auto& connector{ *(dynamic_cast<connector_mock*>(connector_up.get())) };
    EXPECT_CALL(connector, get_email("inbox"sv, 333))
        .WillOnce(::testing::Throw(imap_connection_error{ "Login denied" }));

    imap_connection connection{ std::move(connector_up) };
    EXPECT_THROW((void) connection.get_email_subject("inbox"sv, 333), imap_connection_error);
}
TEST(imap_connection, get_email_subject_and_provider_returns_a_correct_response) {
    std::unique_ptr<connector_adaptor> connector_up{ std::make_unique<connector_mock>() };
    const auto& connector{ *(dynamic_cast<connector_mock*>(connector_up.get())) };
    EXPECT_CALL(connector, get_email("test/tmcppc/problem_98"sv, 1))
        .WillOnce(::testing::Return(samples::email));

    imap_connection connection{ std::move(connector_up) };
    EXPECT_EQ(connection.get_email_subject("test/tmcppc/problem_98"sv, 1), 
        "Subject: =?UTF-8?Q?Harry_Potter=E2=80=99s_acceptance_letter_in_Harry_Potter_a?="
    );
}
