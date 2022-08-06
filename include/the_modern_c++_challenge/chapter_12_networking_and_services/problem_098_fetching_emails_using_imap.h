#pragma once

#include "chapter_12_networking_and_services/imap_connection.h"

#include <iosfwd>


namespace tmcppc::problem_98 {
    tmcppc::imap::mailbox_folder_t read_mailbox_folder(
        std::istream& is,
        std::ostream& os
    );
    void print_mailbox_folders(
        std::ostream& os,
        const tmcppc::imap::mailbox_folders_t& folders
    );
    void print_unread_email_ids_from_folder(
        std::ostream& os,
        const tmcppc::imap::mailbox_folder_t& folder,
        const tmcppc::imap::email_subjects_t& email_subjects
    );
    void test_imap_connection(
        std::istream& is,
        std::ostream& os,
        const tmcppc::imap::imap_connection& connection
    );
}  // namespace tmcppc::problem_98


void problem_98_main(std::istream& is, std::ostream& os);
void problem_98_main();
