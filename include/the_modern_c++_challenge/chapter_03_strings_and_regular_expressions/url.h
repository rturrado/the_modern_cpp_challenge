#pragma once

#include <exception>
#include <fmt/format.h>
#include <fmt/ostream.h>
#include <optional>
#include <ostream>
#include <regex>  // regex_search, smatch
#include <string>  // stoi


namespace tmcppc::network {
    struct invalid_url_error : public std::exception {
        explicit invalid_url_error(const std::string& url) noexcept { message_ += "\"" + url + "\""; }
        [[nodiscard]] const char* what() const noexcept override { return message_.c_str(); }
    private:
        std::string message_{ "invalid URL: " };
    };


    class url {
    private:
        inline static const std::string protocol_str{ R"((^[[:alnum:]]+))" };  // ^\w+
        inline static const std::string login_str{ R"((?:(.+?)@)?)" };  // :(.+?)@, this part is optional, and we don't capture the final @
        inline static const std::string domain_str{ R"(([^\:/\?#]+))" };  // [^:/\?#]+
        inline static const std::string port_str{ R"((?:(?:\:([0-9]+))?))" };  // :\d+, this part is optional, and we don't capture the initial :
        inline static const std::string path_str{ R"((?:(?:/([^\?#]+))?))" };  // /[^\?#]+, this part is optional, and we don't capture the initial /
        inline static const std::string query_str{ R"((?:(?:\?([^#]+))?))" };  // \?[^#]+, this part is optional, and we don't capture the initial ?
        inline static const std::string fragment_str{ R"((?:(?:#(.*$))?))" };  // #[^\?#]+, this part is optional, and we don't capture the initial #

        inline static const std::string url_str{
            protocol_str + R"((?:\://))" + login_str + domain_str + port_str + path_str + query_str + fragment_str
        };

        inline static const std::regex url_pattern{ url_str };

    public:
        explicit url(const std::string& s) {
            std::smatch matches{};
            if (std::regex_search(s, matches, url_pattern) and matches.size() == 8) {
                protocol_ = matches[1];
                domain_ = matches[3];
                if (matches[2].matched) { login_ = matches[2]; }
                if (matches[4].matched) { port_ = std::stoi(matches[4].str()); }
                if (matches[5].matched) { path_ = matches[5]; }
                if (matches[6].matched) { query_ = matches[6]; }
                if (matches[7].matched) { fragment_ = matches[7]; }
            } else {
                throw invalid_url_error{ s };
            }
        }

        url() = default;
        ~url() = default;
        url(const url& other) = default;
        url(url&& other) noexcept = default;
        url& operator=(const url& other) = default;
        url& operator=(url&& other) noexcept = default;

        [[nodiscard]] std::string protocol() const { return protocol_; }
        [[nodiscard]] std::optional<std::string> login() const { return login_; }
        [[nodiscard]] std::string domain() const { return domain_; }
        [[nodiscard]] std::optional<int> port() const { return port_; }
        [[nodiscard]] std::optional<std::string> path() const { return path_; }
        [[nodiscard]] std::optional<std::string> query() const { return query_; }
        [[nodiscard]] std::optional<std::string> fragment() const { return fragment_; }

        auto operator<=>(const url& other) const = default;

        friend std::ostream& operator<<(std::ostream& os, const tmcppc::network::url& u) {
            os << fmt::format("[\n");
            os << fmt::format("\tProtocol: {}\n", u.protocol_);
            if (u.login_.has_value()) {
                os << fmt::format("\tLogin: {}\n", u.login_.value());
            }
            os << fmt::format("\tDomain: {}\n", u.domain_);
            if (u.port_.has_value()) {
                os << fmt::format("\tPort: {}\n", u.port_.value());
            }
            if (u.path_.has_value()) {
                os << fmt::format("\tPath: {}\n", u.path_.value());
            }
            if (u.query_.has_value()) {
                os << fmt::format("\tQuery: {}\n", u.query_.value());
            }
            if (u.fragment_.has_value()) {
                os << fmt::format("\tFragment: {}\n", u.fragment_.value());
            }
            return os << fmt::format("]");
        }

    private:
        std::string protocol_;
        std::optional<std::string> login_;
        std::string domain_;
        std::optional<int> port_;
        std::optional<std::string> path_;
        std::optional<std::string> query_;
        std::optional<std::string> fragment_;
    };
}  // namespace tmcppc::network


// fmt formatter
template <>
struct fmt::formatter<tmcppc::network::url> : fmt::ostream_formatter {};
