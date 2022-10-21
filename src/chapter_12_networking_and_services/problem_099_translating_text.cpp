#include "chapter_12_networking_and_services/problem_099_translating_text.h"
#include "chapter_12_networking_and_services/text_translation.h"

#include <exception>
#include <fmt/ostream.h>
#include <memory>  // make_unique
#include <string_view>
#include <string>  // getline
#include <variant>  // get, holds_alternative

using namespace tmcppc::text_translation;


namespace tmcppc::problem_99 {
    void test_text_translation(std::ostream& os, const translator& translator) {
        auto from_code{ language_code::English };
        auto from_code_str{ language_code_to_string_map[from_code] };
        std::string_view text{ "It was a wrong number that started it, the telephone ringing three times in the dead of night." };
        fmt::print(os, "\t{}: {}\n", from_code_str, text);

        for (auto&& [to_code, to_code_str] : language_code_to_string_map) {
            if (from_code != to_code) {
                try {
                    const auto& result{ translator.translate(text, from_code, to_code) };
                    if (std::holds_alternative<translation_response>(result)) {
                        fmt::print(os, "\t{}: {}\n", to_code_str, std::get<translation_response>(result).text);
                    } else {
                        fmt::print(os, "\t{}: Error: {}\n", to_code_str, std::get<error_response>(result).text);
                    }
                } catch (const std::exception& ex) {
                    fmt::print(os, "\tError: {}\n", ex.what());
                }
            }
        }

        fmt::print(os, "\n");
    }
}  // namespace tmcppc::problem_99


// Translating text to any language
//
// Write a program that can translate text from one language to another using an online service.
// It should be possible to specify the text that you wish to translate, the language of the text,
// and the language to translate to.
void problem_99_main(std::istream& is, std::ostream& os) {
    using namespace tmcppc::problem_99;

    fmt::print(os, "Please enter the Azure translator resource key: ");
    std::string key{};
    std::getline(is, key);
    test_text_translation(os, translator{ std::make_unique<provider_azure>(key) });
}
