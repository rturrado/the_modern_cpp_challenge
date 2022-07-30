#pragma once

#include <iosfwd>
#include <map>
#include <stdexcept>  // runtime_error
#include <string>
#include <string_view>
#include <variant>


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


    struct translation_response {
        std::string text{};
    };
    struct error_response {
        std::string text{};
    };
    using translator_response = std::variant<translation_response, error_response>;


    struct translation_error : public std::runtime_error {
        translation_error(std::string_view message) : std::runtime_error{ message.data()} {}
    };


    class provider_adaptor {
    public:
        virtual ~provider_adaptor() = default;

        // Translation is done from utf8 to utf8
        [[nodiscard]] virtual std::string translate(std::string_view text, language_code from, language_code to) const = 0;
    protected:
        provider_adaptor() = default;
    };


    class provider_azure : public provider_adaptor {
    private:
        static inline std::string_view endpoint{ "https://api.microsofttranslator.com/V2/Http.svc" };
        static inline std::string_view key_header{ "Ocp-Apim-Subscription-Key" };
    public:
        provider_azure(std::string_view key);

        [[nodiscard]] virtual std::string translate(std::string_view text, language_code from, language_code to) const override;
    protected:
        std::string key_{};
    };


    class translator {
    private:
        [[nodiscard]] translator_response parse_translate_response(const std::string& response) const;
    public:
        translator(const provider_adaptor& provider);

        [[nodiscard]] virtual translator_response translate(std::string_view text, language_code from, language_code to) const;
    private:
        const provider_adaptor& provider_;
    };
}  // namespace tmcppc::text_translation
