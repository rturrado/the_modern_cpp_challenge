#pragma once

#include "curl_easy.h"

#include <algorithm>  // transform
#include <boost/algorithm/string.hpp>
#include "fmt/format.h"
#include <iterator>  // back_inserter
#include <memory>  // unique_ptr
#include <ostream>
#include <regex>  // regex_match, smatch, sregex_iterator
#include <sstream>  // istringstream, ostringstream
#include <stdexcept>  // runtime_error
#include <string>  // getline, stoull
#include <string_view>
#include <unordered_map>
#include <utility>  // move
#include <vector>


namespace curl {
    class curl_easy;
}


namespace tmcppc::imap {
    enum class email_server_provider_t { gmail, hotmail, yahoo };

    using mailbox_folder_t = std::string;
    using mailbox_folders_t = std::vector<mailbox_folder_t>;
    using id_t = size_t;
    using email_ids_t = std::vector<id_t>;
    using email_t = std::string;
    using email_subject_t = std::string;
    using email_subjects_t = std::vector<std::string>;


    struct imap_connection_error : public std::runtime_error {
        explicit imap_connection_error(std::string_view message)
            : std::runtime_error{ message.data() }
        {}
    };


    class connector_adaptor {
    public:
        virtual ~connector_adaptor() = default;

        [[nodiscard]] virtual std::string get_mailbox_folders() const = 0;
        [[nodiscard]] virtual std::string get_unread_email_ids(std::string_view folder) const = 0;
        [[nodiscard]] virtual std::string get_email(std::string_view folder, size_t id) const = 0;
    protected:
        connector_adaptor() = default;
    };


    class connector_curl : public connector_adaptor {
    private:
        static inline std::unordered_map<email_server_provider_t, std::string_view> email_server_provider_to_url{
            { email_server_provider_t::gmail, "imaps://imap.gmail.com" },
            { email_server_provider_t::hotmail, "imaps://imap-mail.outlook.com" },
            { email_server_provider_t::yahoo, "imaps://imap.mail.yahoo.com" }
        };
        static inline long email_server_port{ 993 };

        void setup_easy(curl::curl_easy& easy) const {
            easy.add<CURLOPT_PORT>(email_server_port);
            easy.add<CURLOPT_USERNAME>(username_.c_str());
            easy.add<CURLOPT_PASSWORD>(password_.c_str());
            easy.add<CURLOPT_USE_SSL>(CURLUSESSL_ALL);
            easy.add<CURLOPT_SSL_VERIFYPEER>(0L);
            easy.add<CURLOPT_SSL_VERIFYHOST>(0L);
            easy.add<CURLOPT_USERAGENT>("libcurl-agent/1.0");
        }
    public:
        connector_curl(email_server_provider_t provider, std::string_view username, std::string_view password)
            : provider_{ provider }
            , url_{ email_server_provider_to_url.at(provider_) }
            , username_{ username }
            , password_{ password }
        {}

        [[nodiscard]] std::string get_mailbox_folders() const override {
            try {
                std::ostringstream oss{};
                curl::curl_ios<std::ostringstream> writer{ oss };
                curl::curl_easy easy{ writer };

                setup_easy(easy);
                easy.add<CURLOPT_URL>(url_.c_str());
                easy.perform();

                return oss.str();
            } catch (const curl::curl_easy_exception& ex) {
                throw imap_connection_error{ ex.what() };
            }
        }
        [[nodiscard]] std::string get_unread_email_ids(std::string_view folder) const override {
            try {
                std::ostringstream oss{};
                curl::curl_ios<std::ostringstream> writer{ oss };
                curl::curl_easy easy{ writer };

                setup_easy(easy);
                easy.add<CURLOPT_URL>(fmt::format("{}/{}/", url_, folder.data()).c_str());
                easy.add<CURLOPT_CUSTOMREQUEST>("SEARCH UNSEEN");

                easy.perform();

                return oss.str();
            } catch (const curl::curl_easy_exception& ex) {
                throw imap_connection_error{ ex.what() };
            }
        }
        [[nodiscard]] std::string get_email(std::string_view folder, size_t id) const override {
            try {
                std::ostringstream oss{};
                curl::curl_ios<std::ostringstream> writer{ oss };
                curl::curl_easy easy{ writer };

                setup_easy(easy);
                easy.add<CURLOPT_URL>(fmt::format("{}/{}/;UID={}", url_, folder.data(), id).c_str());

                easy.perform();

                return oss.str();
            } catch (const curl::curl_easy_exception& ex) {
                throw imap_connection_error{ ex.what() };
            }
        }
    private:
        email_server_provider_t provider_{};
        std::string url_{};
        std::string username_{};
        std::string password_{};
    };


    class imap_connection {
    private:
        [[nodiscard]] static mailbox_folders_t parse_get_mailbox_folders_response(const std::string& response) {
            mailbox_folders_t ret{};
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
        [[nodiscard]] static email_ids_t parse_get_unread_email_ids_response(std::string response) {
            email_ids_t ret{};
            std::smatch matches{};
            boost::algorithm::trim_right(response);
            const std::regex response_pattern{ R"(\* SEARCH(?: \d+)+)" };
            if (std::regex_match(response, matches, response_pattern)) {
                const std::regex id_pattern{ R"(\d+)" };
                std::transform(
                    std::sregex_iterator{ std::cbegin(response), std::cend(response), id_pattern },
                    std::sregex_iterator{},
                    std::back_inserter(ret),
                    [](const std::smatch& match) { return static_cast<size_t>(std::stoull(match.str())); }
                );
            }
            return ret;
        }
        [[nodiscard]] static email_subject_t parse_email_subject(const std::string& email) {
            std::istringstream iss{ email };
            std::string line{};
            std::smatch matches{};
            const std::regex pattern{ R"(^Subject: .*$)" };
            while (std::getline(iss, line)) {
                boost::algorithm::trim_right(line);
                if (std::regex_match(line, matches, pattern)) {
                    return matches[0].str();
                }
            }
            return {};
        }
    public:
        explicit imap_connection(std::unique_ptr<connector_adaptor> connector)
            : connector_{ std::move(connector) } {

            if (not connector_) {
                throw imap_connection_error{ "connector is null" };
            }
        }

        [[nodiscard]] mailbox_folders_t get_mailbox_folders() const {
            return parse_get_mailbox_folders_response(connector_->get_mailbox_folders());
        }
        [[nodiscard]] email_ids_t get_unread_email_ids(std::string_view folder) const {
            return parse_get_unread_email_ids_response(connector_->get_unread_email_ids(folder));
        }
        [[nodiscard]] email_t get_email(std::string_view folder, size_t id) const {
            return connector_->get_email(folder, id);
        }
        [[nodiscard]] email_subject_t get_email_subject(std::string_view folder, size_t id) const {
            const auto& email{ get_email(folder, id) };
            if (not email.empty()) {
                return parse_email_subject(email);
            }
            return {};
        }
    private:
        std::unique_ptr<connector_adaptor> connector_;
    };
}  // namespace tmcppc::imap
