#pragma once

#include "chapter_12_networking_and_services/text_translation.h"

#include <iosfwd>


namespace tmcppc::problem_99 {
    void test_text_translation(std::ostream& os, const tmcppc::text_translation::provider_adaptor& provider);
}  // namespace tmcppc::problem_99


void problem_99_main(std::istream& is, std::ostream& os);
void problem_99_main();
