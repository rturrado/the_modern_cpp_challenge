#pragma once

#include "chapter_12_networking_and_services/text_translation.h"

#include <iosfwd>

using namespace tmcppc::text_translation;


void test_text_translation(std::ostream& os, translator_adaptor* translator);

void problem_99_main(std::istream& is, std::ostream& os);
void problem_99_main();
