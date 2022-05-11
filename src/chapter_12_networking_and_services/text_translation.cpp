#include "Chapter12_NetworkingAndServices/TextTranslation.h"

#include "curlcpp/master/include/curl_easy.h"
#include "curlcpp/master/include/curl_header.h"

#include <regex>  // regex_match, smatch
#include <sstream>  // ostringstream
#include <string>
#include <string_view>


namespace rtc::text_translation
{
    translator::translator(std::string_view key) : key_{ key } {}

    [[nodiscard]] std::string translator::parse_translate_response(const std::string& response) const
    {
        std::string ret{};
        const std::regex pattern{ R"(<string xmlns="[^"]+">([^<]*)</string>)" };
        const std::regex error_pattern{ R"(<html><body><h1>Argument Exception</h1>.*<p>Message: ([^<]+)</p>.*)" };
        std::smatch matches{};
        if (std::regex_match(response, matches, pattern))
        {
            ret = matches[1].str();
        }
        else if (std::regex_match(response, matches, error_pattern))
        {
            std::ostringstream oss{};
            oss << "Error: " << matches[1].str();
            ret = oss.str();
        }
        return ret;
    }

    [[nodiscard]] std::string translator::translate(std::string_view text, language_code from, language_code to) const
    {
        std::string ret{};
        try
        {
            std::ostringstream oss{};
            curl::curl_ios<std::ostringstream> writer{ oss };
            curl::curl_easy easy{ writer };

            std::string url_encoded_text{ text };
            easy.escape(url_encoded_text);

            auto from_code_str{ language_code_to_string_map[from] };
            auto to_code_str{ language_code_to_string_map[to] };

            std::ostringstream oss_url{};
            oss_url << endpoint << "/Translate" << "?from=" << from_code_str << "&to=" << to_code_str << "&text=" << url_encoded_text;
            easy.add<CURLOPT_URL>(oss_url.str().c_str());

            curl::curl_header header{};
            std::ostringstream oss_header{};
            oss_header << key_header << ":" << key_;
            header.add(oss_header.str().c_str());
            easy.add<CURLOPT_HTTPHEADER>(header.get());

            easy.perform();

            ret = parse_translate_response(oss.str());
        }
        catch (const curl::curl_easy_exception& ex) {
            std::cout << "\tError: " << ex.what() << "\n";
        }
        return ret;
    }

}  // namespace rtc::text_translation
