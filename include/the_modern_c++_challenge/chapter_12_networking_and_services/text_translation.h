#pragma once

#include <curl_easy.h>
#include <curl_header.h>
#include <fmt/format.h>
#include <map>
#include <memory>  // unique_ptr
#include <regex>  // regex_match, smatch
#include <sstream>  // ostringstream
#include <stdexcept>  // runtime_error
#include <string>
#include <string_view>
#include <utility>  // move
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
        explicit translation_error(std::string_view message)
            : std::runtime_error{ message.data() }
        {}
    };


    struct provider_adaptor {
        virtual ~provider_adaptor() = default;

        // Translation is done from utf8 to utf8
        [[nodiscard]] virtual std::string translate(std::string_view text, language_code from, language_code to) const = 0;
    };


    class provider_azure : public provider_adaptor {
    private:
        static inline std::string_view endpoint{ "https://api.microsofttranslator.com/V2/Http.svc" };
        static inline std::string_view key_header{ "Ocp-Apim-Subscription-Key" };
    public:
        explicit provider_azure(std::string_view key)
            : key_{ key }
        {}

        [[nodiscard]] std::string translate(std::string_view text, language_code from, language_code to) const override {
            try {
                std::ostringstream oss{};
                curl::curl_ios<std::ostringstream> writer{ oss };
                curl::curl_easy easy{ writer };

                std::string url_encoded_text{ text };
                easy.escape(url_encoded_text);

                auto from_code_str{ language_code_to_string_map[from] };
                auto to_code_str{ language_code_to_string_map[to] };

                easy.add<CURLOPT_URL>(fmt::format(
                    "{}/Translate?from={}&to={}&text={}", endpoint, from_code_str, to_code_str, url_encoded_text)
                    .c_str());

                curl::curl_header header{};
                header.add(fmt::format("{}:{}", key_header, key_));
                easy.add<CURLOPT_HTTPHEADER>(header.get());

                easy.perform();

                return oss.str();
            } catch (const curl::curl_easy_exception& ex) {
                throw translation_error{ ex.what() };
            }
        }
    protected:
        std::string key_{};
    };


    class translator {
    private:
        [[nodiscard]] static translator_response parse_translate_response(const std::string& response) {
            const std::regex pattern{ R"(<string xmlns="[^"]+">([^<]*)</string>)" };
            const std::regex error_pattern{ R"(<html><body><h1>Argument Exception</h1>.*<p>Message: ([^<]+)</p>.*)" };
            std::smatch matches{};
            if (std::regex_match(response, matches, pattern)) {
                return translation_response{ matches[1].str() };
            } else if (std::regex_match(response, matches, error_pattern)) {
                return error_response{ matches[1].str() };
            }
            return error_response{ "unknown provider response" };
        }
    public:
        explicit translator(std::unique_ptr<provider_adaptor> provider)
            : provider_{ std::move(provider) } {

            if (not provider_) {
                throw translation_error{ "provider is null" };
            }
        }

        [[nodiscard]] virtual translator_response translate(std::string_view text, language_code from, language_code to) const {
            return parse_translate_response(provider_->translate(text, from, to));
        }
    private:
        std::unique_ptr<provider_adaptor> provider_;
    };
}  // namespace tmcppc::text_translation
