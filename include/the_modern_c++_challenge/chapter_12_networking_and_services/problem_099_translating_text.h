#pragma once

#include "chapter_12_networking_and_services/text_translation.h"

#include <iosfwd>


namespace tmcppc::problem_99 {
    void test_text_translation(std::ostream& os, tmcppc::text_translation::translator_adaptor* translator);
}  // namespace tmcppc::problem_99


void problem_99_main(std::istream& is, std::ostream& os);
void problem_99_main();
