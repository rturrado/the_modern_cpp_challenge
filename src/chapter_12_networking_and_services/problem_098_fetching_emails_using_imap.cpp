#include "Chapter12_NetworkingAndServices.h"
#include "Chapter12_NetworkingAndServices/ImapConnection.h"

#include "rtc/console.h"  // read_positive_number

#include <format>
#include <iostream>  // cout
#include <string>  // getline


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
void problem_98_main()
{
    auto provider{ []() {
        auto input{ read_positive_number("Please enter your email service provider (0 for gmail, 1 for hotmail, 2 for yahoo): ", 0, 3) };
        return static_cast<rtc::imap::email_server_provider_t>(input);
    }() };
    auto username{ []() {
        std::string ret{};
        std::cout << "Please enter your username: ";
        std::getline(std::cin, ret);
        return ret;
    }() };
    auto password{ []() {
        std::string ret{};
        std::cout << "Please enter your email password: ";
        std::getline(std::cin, ret);
        return ret;
    }() };

    auto imap_connection{ rtc::imap::imap_connection(provider, username, password) };

    std::cout << "List of folders from the mailbox:\n";
    auto folders_opt{ imap_connection.get_mailbox_folders() };
    if (folders_opt.has_value())
    {
        auto folders{ folders_opt.value() };
        if (not folders.empty())
        {
            for (auto& folder : folders) {
                std::cout << "\t" << folder << "\n";
            }

            auto folder{ []() {
                std::string ret{};
                std::cout << "Please enter a folder name: ";
                std::getline(std::cin, ret);
                return ret;
            }() };

            std::cout << std::format("List of unread emails from folder '{}':\n", folder);
            auto unread_email_ids_opt{ imap_connection.get_unread_email_ids(folder) };
            if (unread_email_ids_opt.has_value())
            {
                auto unread_email_ids{ unread_email_ids_opt.value() };
                if (not unread_email_ids.empty())
                {
                    for (auto&& id : unread_email_ids)
                    {
                        auto email_subject_opt{ imap_connection.get_email_subject(folder, id) };
                        if (email_subject_opt.has_value())
                        {
                            std::cout << "\t" << email_subject_opt.value() << "\n";
                        }
                    }
                } else {
                    std::cout << "\tThere are no unread emails\n";
                }
            }
        } else {
            std::cout << "\tThere are no folders in the mailbox\n";
        }
    }

    std::cout << "\n";
}
