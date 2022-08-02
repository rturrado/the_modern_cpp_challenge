#pragma once

#include "chapter_12_networking_and_services/text_translation.h"

#include <iosfwd>
#include <memory>  // unique_ptr


namespace tmcppc::problem_99 {
    void test_text_translation(std::ostream& os, std::unique_ptr<tmcppc::text_translation::provider_adaptor> provider);
}  // namespace tmcppc::problem_99


void problem_99_main(std::istream& is, std::ostream& os);
void problem_99_main();
