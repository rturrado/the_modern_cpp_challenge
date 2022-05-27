#include "chapter_12_networking_and_services/imap_connection.h"

#include "curlcpp/master/include/curl_easy.h"

#include <algorithm>  // transform
#include <boost/algorithm/string.hpp>
#include <fmt/ostream.h>
#include <iostream>  // cout
#include <iterator>  // back_inserter
#include <optional>
#include <ostream>
#include <regex>  // regex_match, smatch, sregex_iterator
#include <sstream>  // istringstream, ostringstream
#include <string>  // getline, stoull
#include <string_view>
#include <unordered_map>
#include <vector>


namespace tmcppc::imap {
    void imap_connection::setup_easy(curl::curl_easy& easy) const {
        easy.add<CURLOPT_PORT>(email_server_port);
        easy.add<CURLOPT_USERNAME>(username_.c_str());
        easy.add<CURLOPT_PASSWORD>(password_.c_str());
        easy.add<CURLOPT_USE_SSL>(CURLUSESSL_ALL);
        easy.add<CURLOPT_SSL_VERIFYPEER>(0L);
        easy.add<CURLOPT_SSL_VERIFYHOST>(0L);
        easy.add<CURLOPT_USERAGENT>("libcurl-agent/1.0");
    }

    [[nodiscard]] auto imap_connection::parse_get_mailbox_folders_response(const std::string& response) const -> std::vector<std::string> {
        std::vector<std::string> ret{};
        std::istringstream iss{ response };
        std::string line{};
        std::smatch matches{};
        const std::regex pattern{ R"(\* LIST \([^\)]+\) \"[^"]+\" \"([^\\]+)\".*)" };
        while (std::getline(iss, line)) {
            boost::algorithm::trim_right(line);
            if (std::regex_match(line, matches, pattern)) {
                ret.push_back(matches[1]);
            }
        }
        return ret;
    }

    [[nodiscard]] auto imap_connection::parse_get_unread_email_ids_response(std::string response) const -> std::vector<std::size_t> {
        std::vector<std::size_t> ret{};
        std::smatch matches{};
        boost::algorithm::trim_right(response);
        const std::regex response_pattern{ R"(\* SEARCH(?: \d+)+)" };
        if (std::regex_match(response, matches, response_pattern)) {
            const std::regex id_pattern{ R"(\d+)" };
            std::transform(
                std::sregex_iterator{ std::cbegin(response), std::cend(response), id_pattern },
                std::sregex_iterator{},
                std::back_inserter(ret),
                [](const std::smatch match) { return static_cast<size_t>(std::stoull(match.str())); }
            );
        }
        return ret;
    }

    [[nodiscard]] auto imap_connection::parse_email_subject(const std::string& email) const -> std::optional<std::string> {
        std::optional<std::string> ret{};
        std::istringstream iss{ email };
        std::string line{};
        std::smatch matches{};
        const std::regex pattern{ R"(^Subject: .*$)" };
        while (std::getline(iss, line)) {
            boost::algorithm::trim_right(line);
            if (std::regex_match(line, matches, pattern)) {
                ret = matches[0].str();
                break;
            }
        }
        return ret;
    }

    imap_connection::imap_connection(email_server_provider_t provider, std::string_view username, std::string_view password)
        : provider_{ provider }
        , url_{ email_server_provider_to_url.at(provider_) }
        , username_{ username }
        , password_{ password }
    {}

    [[nodiscard]] auto imap_connection::get_mailbox_folders(std::ostream& os) const -> std::optional<std::vector<std::string>> {
        std::optional<std::vector<std::string>> ret{};
        try {
            std::ostringstream oss{};
            curl::curl_ios<std::ostringstream> writer{ oss };
            curl::curl_easy easy{ writer };

            setup_easy(easy);
            easy.add<CURLOPT_URL>(url_.c_str());
            easy.perform();

            ret = parse_get_mailbox_folders_response(oss.str());
        } catch (const curl::curl_easy_exception& ex) {
            fmt::print(os, "\tError: {}\n", ex.what());
        }
        return ret;
    }

    [[nodiscard]] auto imap_connection::get_unread_email_ids(std::ostream& os, std::string_view folder) const -> std::optional<std::vector<size_t>> {
        std::optional<std::vector<size_t>> ret{};
        try {
            std::ostringstream oss{};
            curl::curl_ios<std::ostringstream> writer{ oss };
            curl::curl_easy easy{ writer };

            setup_easy(easy);
            std::ostringstream url_oss{};
            fmt::print(url_oss, "{}/{}/", url_, folder.data());
            easy.add<CURLOPT_URL>(url_oss.str().c_str());
            easy.add<CURLOPT_CUSTOMREQUEST>("SEARCH UNSEEN");

            easy.perform();

            ret = parse_get_unread_email_ids_response(oss.str());
        } catch (const curl::curl_easy_exception& ex) {
            fmt::print(os, "\tError: {}\n", ex.what());
        }
        return ret;
    }

    [[nodiscard]] auto imap_connection::get_email(std::ostream& os, std::string_view folder, size_t id) const -> std::optional<std::string> {
        std::optional<std::string> ret{};
        try {
            std::ostringstream oss{};
            curl::curl_ios<std::ostringstream> writer{ oss };
            curl::curl_easy easy{ writer };

            setup_easy(easy);
            std::ostringstream url_oss{};
            fmt::print(url_oss, "{}/{}/;UID=", url_, folder.data(), id);
            easy.add<CURLOPT_URL>(url_oss.str().c_str());

            easy.perform();

            ret = oss.str();
        } catch (const curl::curl_easy_exception& ex) {
            fmt::print(os, "\tError: {}\n", ex.what());
        }
        return ret;
    }

    [[nodiscard]] auto imap_connection::get_email_subject(std::ostream& os, std::string_view folder, size_t id) const -> std::optional<std::string> {
        std::optional<std::string> ret{};
        auto email_opt{ get_email(os, folder, id) };
        if (email_opt.has_value()) {
            ret = parse_email_subject(email_opt.value());
        }
        return ret;
    }
}  // namespace tmcppc::imap
