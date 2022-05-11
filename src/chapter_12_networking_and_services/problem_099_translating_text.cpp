#include "Chapter12_NetworkingAndServices.h"
#include "Chapter12_NetworkingAndServices/TextTranslation.h"

#include <fmt/core.h>
#include <iostream>  // cin, cout
#include <string>


// Translating text to any language
//
// Write a program that can translate text from one language to another using an online service.
// It should be possible to specify the text that you wish to translate, the language of the text,
// and the language to translate to.
void problem_99_main()
{
    using namespace rtc::text_translation;
    
    std::cout << "Please enter the Azure translator resource key: ";
    std::string key{}; std::cin >> key; std::cout << "\n";
    translator translator{ key };

    auto from_code{ language_code::English };
    auto from_code_str{ language_code_to_string_map[from_code] };
    const std::string text{ "It was a wrong number that started it, the telephone ringing three times in the dead of night." };
    fmt::print("\t{}: {}\n", from_code_str, text);

    for (auto&& [to_code, to_code_str] : language_code_to_string_map)
    {
        if (from_code != to_code)
        {
            auto translated_text{ translator.translate(text, from_code, to_code) };
            fmt::print("\t{}: {}\n", to_code_str, translated_text);
        }
    }

    std::cout << "\n";
}
