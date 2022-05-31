#include "chapter_12_networking_and_services/problem_099_translating_text.h"
#include "chapter_12_networking_and_services/text_translation.h"

#include <fmt/ostream.h>
#include <iostream>  // cin, cout
#include <string>  // getline


void problem_99_main(std::istream& is, std::ostream& os) {
    using namespace tmcppc::text_translation;

    fmt::print(os, "Please enter the Azure translator resource key: ");
    std::string key{};
    std::getline(is, key);
    translator translator{ key };

    auto from_code{ language_code::English };
    auto from_code_str{ language_code_to_string_map[from_code] };
    const std::string text{ "It was a wrong number that started it, the telephone ringing three times in the dead of night." };
    fmt::print(os, "\t{}: {}\n", from_code_str, text);

    for (auto&& [to_code, to_code_str] : language_code_to_string_map) {
        if (from_code != to_code) {
            auto translated_text{ translator.translate(os, text, from_code, to_code) };
            fmt::print(os, "\t{}: {}\n", to_code_str, translated_text);
        }
    }

    fmt::print(os, "\n");
}


// Translating text to any language
//
// Write a program that can translate text from one language to another using an online service.
// It should be possible to specify the text that you wish to translate, the language of the text,
// and the language to translate to.
void problem_99_main() {
    problem_99_main(std::cin, std::cout);
}
