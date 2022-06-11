#pragma once

#include "chapter_12_networking_and_services/imap_connection.h"

#include <iosfwd>


namespace tmcppc::problem_98 {
    void test_imap_connection(std::istream& is, std::ostream& os,
        tmcppc::imap::imap_connection_adaptor* imap_connection_adaptor);
}  // namespace tmcppc::problem_98


void problem_98_main(std::istream& is, std::ostream& os);
void problem_98_main();
