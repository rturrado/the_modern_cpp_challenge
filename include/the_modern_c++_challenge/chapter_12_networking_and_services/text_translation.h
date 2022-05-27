#pragma once

#include <iosfwd>
#include <map>
#include <string>
#include <string_view>


namespace tmcppc::text_translation {
    enum class language_code {
        Arabic,
        German,
        Greek,
        English,
        Spanish,
        French,
        Italian,
        Polish,
        Portuguese_Portugal,
        Chinese_Simplified
    };
    static inline std::map<language_code, std::string> language_code_to_string_map{
        { language_code::Arabic, "ar" },
        { language_code::German, "de" },
        { language_code::Greek, "el" },
        { language_code::English, "en" },
        { language_code::Spanish, "es" },
        { language_code::French, "fr" },
        { language_code::Italian, "it" },
        { language_code::Polish, "pl" },
        { language_code::Portuguese_Portugal, "pt-pt" },
        { language_code::Chinese_Simplified, "zh-Hans" }
    };

    class translator {
    private:
        static inline std::string_view endpoint{ "https://api.microsofttranslator.com/V2/Http.svc" };
        static inline std::string_view key_header{ "Ocp-Apim-Subscription-Key" };

        [[nodiscard]] std::string parse_translate_response(const std::string& response) const;
    public:
        translator(std::string_view key);
        
        // Translation is done from utf8 to utf8
        [[nodiscard]] std::string translate(std::ostream& os, std::string_view text, language_code from, language_code to) const;
    private:
        std::string key_{};
    };
}  // namespace tmcppc::text_translation
