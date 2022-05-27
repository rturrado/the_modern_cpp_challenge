#include "chapter_12_networking_and_services/imap_connection.h"
#include "chapter_12_networking_and_services/problem_098_fetching_emails_using_imap.h"

#include "rtc/console.h"  // read_positive_number

#include <fmt/ostream.h>
#include <iostream>  // cin, cout
#include <ostream>
#include <string>  // getline


void problem_98_main(std::istream& is, std::ostream& os) {
    auto provider{ [&is, &os]() {
        auto input{ rtc::console::read_positive_number(is, os, "Please enter your email service provider (0 for gmail, 1 for hotmail, 2 for yahoo): ", 0, 3) };
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

    auto imap_connection{ tmcppc::imap::imap_connection(provider, username, password) };

    fmt::print(os, "List of folders from the mailbox:\n");
    auto folders_opt{ imap_connection.get_mailbox_folders(os) };
    if (folders_opt.has_value()) {
        auto folders{ folders_opt.value() };
        if (not folders.empty()) {
            for (auto& folder : folders) {
                fmt::print(os, "\t{}\n", folder);
            }

            auto folder{ [&is, &os]() {
                std::string ret{};
                fmt::print(os, "Please enter a folder name: ");
                std::getline(is, ret);
                return ret;
            }() };

            fmt::print(os, "List of unread emails from folder '{}':\n", folder);
            auto unread_email_ids_opt{ imap_connection.get_unread_email_ids(os, folder) };
            if (unread_email_ids_opt.has_value()) {
                auto unread_email_ids{ unread_email_ids_opt.value() };
                if (not unread_email_ids.empty()) {
                    for (auto&& id : unread_email_ids) {
                        auto email_subject_opt{ imap_connection.get_email_subject(os, folder, id) };
                        if (email_subject_opt.has_value()) {
                            fmt::print(os, "\t{}\n", email_subject_opt.value());
                        }
                    }
                } else {
                    fmt::print(os, "\tThere are no unread emails\n");
                }
            }
        } else {
            fmt::print(os, "\tThere are no folders in the mailbox\n");
        }
    }

    fmt::print(os, "\n");
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
