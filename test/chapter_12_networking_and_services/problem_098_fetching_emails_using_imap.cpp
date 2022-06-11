#include "chapter_12_networking_and_services/imap_connection.h"
#include "chapter_12_networking_and_services/problem_098_fetching_emails_using_imap.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <optional>
#include <sstream>  // istringstream, ostringstream
#include <string>
#include <string_view>
#include <vector>

using namespace tmcppc::imap;
using namespace std::string_view_literals;


namespace tmcppc::imap {
    class imap_connection_mock : public imap_connection_adaptor {
    public:
        MOCK_METHOD(std::optional<std::vector<std::string>>, get_mailbox_folders,
            (), (const, override));
        MOCK_METHOD(std::optional<std::vector<size_t>>, get_unread_email_ids,
            (std::string_view folder), (const, override));
        MOCK_METHOD(std::optional<std::string>, get_email,
            (std::string_view folder, size_t id), (const, override));
        MOCK_METHOD(std::optional<std::string>, get_email_subject, 
            (std::string_view folder, size_t id), (const, override));
    };
}  // namespace tmcppc::imap


TEST(test_imap_connection, DISABLED_output_wrong_folder_name) {
    imap_connection_mock connection{};
    EXPECT_CALL(connection, get_mailbox_folders())
        .WillOnce(::testing::Return(std::vector<std::string>{ "Inbox", "Sent", "Trash" }));
    EXPECT_CALL(connection, get_unread_email_ids("wrong_folder_name"sv))
        .WillOnce(::testing::Throw(imap_connection_error{ "Login denied" }));

    std::istringstream iss{ "wrong_folder_name\n" };
    std::ostringstream oss{};
    tmcppc::problem_98::test_imap_connection(iss, oss, &connection);

    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "List of folders from the mailbox:\n"
        "\tInbox\n"
        "\tSent\n"
        "\tTrash\n"
        "Please enter a folder name: "  // wrong_folder_name
        "List of unread emails from folder 'wrong_folder_name':\n"
        "\tError: Login denied\n"
    ));
}


TEST(test_imap_connection, DISABLED_output) {
    imap_connection_mock connection{};
    EXPECT_CALL(connection, get_mailbox_folders())
        .WillOnce(::testing::Return(std::vector<std::string>{ "Inbox", "Sent", "Trash" }));
    EXPECT_CALL(connection, get_unread_email_ids("Inbox"sv))
        .WillOnce(::testing::Return(std::vector<std::size_t>{0, 1, 2}));
    EXPECT_CALL(connection, get_email_subject("Inbox"sv, 0))
        .WillOnce(::testing::Return("Subject: This is subject 1"));
    EXPECT_CALL(connection, get_email_subject("Inbox"sv, 1))
        .WillOnce(::testing::Return("Subject: And this is subject 2"));
    EXPECT_CALL(connection, get_email_subject("Inbox"sv, 2))
        .WillOnce(::testing::Return("Subject: And subject 3"));

    std::istringstream iss{ "Inbox\n" };
    std::ostringstream oss{};
    tmcppc::problem_98::test_imap_connection(iss, oss, &connection);

    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "List of folders from the mailbox:\n"
        "\tInbox\n"
        "\tSent\n"
        "\tTrash\n"
        "Please enter a folder name: "  // Inbox
        "List of unread emails from folder 'Inbox':\n"
        "\tSubject: This is subject 1\n"
        "\tSubject: And this is subject 2\n"
        "\tSubject: And subject 3\n"
    ));
}
