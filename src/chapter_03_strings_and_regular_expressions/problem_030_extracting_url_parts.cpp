#include "chapter_03_strings_and_regular_expressions/problem_030_extracting_url_parts.h"

#include <exception>
#include <iostream>  // cout
#include <optional>
#include <ostream>
#include <regex>  // regex_search
#include <string>  // stoi


struct invalid_url : public std::exception
{
    explicit invalid_url(const std::string& url) noexcept { message_ += "\"" + url + "\""; }
    const char* what() const noexcept { return message_.c_str(); }
private:
    std::string message_{ "invalid URL: "};
};


struct url
{
private:
    const std::string protocol_str{ R"((^[[:alnum:]]+))" };  // ^\w+
    const std::string login_str{ R"((?:([^@]+)@)?)" };  // :[^@]+@, this part is optional, and we don't capture the final @
    const std::string domain_str{ R"(([^\:/\?#]+))" };  // [^:/\?#]+
    const std::string port_str{ R"((?:(?:\:([0-9]+))?))" };  // :\d+, this part is optional, and we don't capture the initial :
    const std::string path_str{ R"((?:(?:/([^\?#]+))?))" };  // /[^\?#]+, this part is optional, and we don't capture the initial /
    const std::string query_str{ R"((?:(?:\?([^#]+))?))" };  // \?[^#]+, this part is optional, and we don't capture the initial ?
    const std::string fragment_str{ R"((?:(?:#(.*$))?))" };  // #[^\?#]+, this part is optional, and we don't capture the initial #

    const std::string url_str{
        protocol_str + R"((?:\://))" + login_str + domain_str + port_str + path_str + query_str + fragment_str
    };

    const std::regex url_pattern{ url_str };

public:
    url(const std::string& s)
    {
        std::smatch matches{};
        if (std::regex_search(s, matches, url_pattern) and matches.size() == 8)
        {
            protocol_ = matches[1];
            domain_ = matches[3];
            if (matches[2].matched) { login_ = matches[2]; }
            if (matches[4].matched) { port_ = std::stoi(matches[4].str()); }
            if (matches[5].matched) { path_ = matches[5]; }
            if (matches[6].matched) { query_ = matches[6]; }
            if (matches[7].matched) { fragment_ = matches[7]; }
        }
        else
        {
            throw invalid_url{ s };
        }
    }

    url() = default;
    url(const url& other) = default;
    url(url&& other) = default;
    url& operator=(const url& other) = default;
    url& operator=(url&& other) = default;

    friend std::ostream& operator<<(std::ostream& os, const url& u);

private:
    std::string protocol_;
    std::optional<std::string> login_;
    std::string domain_;
    std::optional<int> port_;
    std::optional<std::string> path_;
    std::optional<std::string> query_;
    std::optional<std::string> fragment_;
};


/*friend*/ std::ostream& operator<<(std::ostream& os, const url& u)
{
    os << "\t" << "Protocol: " << u.protocol_ << "\n";
    if (u.login_.has_value()) { os << "\t" << "Login: " << u.login_.value() << "\n"; }
    os << "\t" << "Domain: " << u.domain_ << "\n";
    if (u.port_.has_value()) { os << "\t" << "Port: " << u.port_.value() << "\n"; }
    if (u.path_.has_value()) { os << "\t" << "Path: " << u.path_.value() << "\n"; }
    if (u.query_.has_value()) { os << "\t" << "Query: " << u.query_.value() << "\n"; }
    if (u.fragment_.has_value()) { os << "\t" << "Fragment: " << u.fragment_.value(); }
    
    return os;
}


// Extracting URL parts
//
// Write a function that, given a string that represents a URL, parses and extracts the parts of the URL
// (protocol, domain, port, path, query, and fragment)
void problem_30_main()
{
    for (const auto& s : { "http://user:pass@example.com:992/animal/bird?species=seagull#wings",
                           "http://example.com/animal/bird#wings",
                           "This is not a valid URL!" })
    {
        try
        {
            url u{ s };
            std::cout << "Parsing URL \"" << s << "\":\n" << u << "\n";
        }
        catch (const std::exception& err)
        {
            std::cout << "Error: " << err.what() << "\n";
        }
    }

    std::cout << "\n";
}
