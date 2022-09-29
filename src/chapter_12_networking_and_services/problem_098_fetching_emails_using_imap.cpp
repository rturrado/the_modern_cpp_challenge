#include "chapter_12_networking_and_services/imap/connection.h"
#include "chapter_12_networking_and_services/problem_098_fetching_emails_using_imap.h"

#include <algorithm>  // transform
#include <exception>
#include <fmt/ostream.h>
#include <iostream>  // cin, cout
#include <memory>  // make_unique
#include <rtc/console.h>  // read_positive_number
#include <string>  // getline

using namespace tmcppc::imap;


namespace tmcppc::problem_98 {
    mailbox_folder_t read_mailbox_folder(std::istream& is, std::ostream& os) {
        std::string ret{};
        fmt::print(os, "Please enter a folder name: ");
        std::getline(is, ret);
        return ret;
    }

    void print_mailbox_folders(std::ostream& os, const mailbox_folders_t& folders) {
        fmt::print(os, "List of folders from the mailbox:\n");
        if (not folders.empty()) {
            for (const auto& folder : folders) {
                fmt::print(os, "\t{}\n", folder);
            }
        } else {
            fmt::print(os, "\tThere are no folders in the mailbox\n");
        }
    }

    void print_unread_email_ids_from_folder(std::ostream& os, const mailbox_folder_t& folder,
        const email_subjects_t& email_subjects) {

        fmt::print(os, "List of unread emails from folder '{}':\n", folder);
        if (not email_subjects.empty()) {
            for (const auto& email_subject : email_subjects) {
                fmt::print(os, "\t{}\n", email_subject);
            }
        } else {
            fmt::print(os, "\tThere are no unread emails\n");
        }
    }

    void test_imap_connection(std::istream& is, std::ostream& os, const imap_connection& connection) {
        try {
            const auto& folders{ connection.get_mailbox_folders() };
            print_mailbox_folders(os, folders);
            if (not folders.empty()) {
                auto folder{ read_mailbox_folder(is, os) };
                const auto& unread_email_ids{ connection.get_unread_email_ids(folder) };
                std::vector<email_subject_t> email_subjects(unread_email_ids.size());
                std::ranges::transform(unread_email_ids, std::begin(email_subjects), [&connection, &folder](const auto& id) {
                    return connection.get_email_subject(folder, id);
                });
                print_unread_email_ids_from_folder(os, folder, email_subjects);
            }
        } catch (const std::exception& ex) {
            fmt::print(os, "\tError: {}\n", ex.what());
        }

        fmt::print(os, "\n");
    }
}  // namespace tmcppc::problem_98


void problem_98_main(std::istream& is, std::ostream& os) {
    using namespace tmcppc::problem_98;

    auto provider{ [&is, &os]() {
        auto input{ rtc::console::read_positive_number(is, os,
            "Please enter your email service provider (0 for gmail, 1 for hotmail, 2 for yahoo): ", 0, 3) };
        return static_cast<tmcppc::imap::email_server_provider_t>(input);
    }() };
    auto username{ [&is, &os]() {
        std::string ret{};
        fmt::print(os, "Please enter your username: ");
        std::getline(is, ret);
        return ret;
    }() };
    auto password{ [&is, &os]() {
        std::string ret{};
        fmt::print(os, "Please enter your email password: ");
        std::getline(is, ret);
        return ret;
    }() };

    test_imap_connection(is, os, imap_connection{ std::make_unique<connector_curl>(provider, username, password) });
}


// Fetching emails using IMAP
//
// Write a program that can get information from an email server using IMAP.
// The program should be able to:
//   - Get a list of folders from the mailbox.
//   - Get unread emails from a particular folder.
//
// Note: I tested this:
//   - with my gmail account,
//   - getting a third-party application password, and using it as a password, and
//   - marking some emails as unread in the doctorado folder (for some reason, I couldn't retrieve unread emails from the INBOX folder).
void problem_98_main() {
    problem_98_main(std::cin, std::cout);
}
