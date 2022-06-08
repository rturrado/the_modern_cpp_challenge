#pragma once

#include <iosfwd>
#include <optional>
#include <stdexcept>  // runtime_error
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>


namespace curl {
    class curl_easy;
}


namespace tmcppc::imap {
    enum class email_server_provider_t { gmail, hotmail, yahoo };


    struct imap_connection_error : public std::runtime_error {
        imap_connection_error(std::string_view message) : std::runtime_error{ message.data() } {}
    };


    class imap_connection_adaptor {
    public:
        virtual ~imap_connection_adaptor() = default;

        [[nodiscard]] virtual std::optional<std::vector<std::string>> get_mailbox_folders() const = 0;
        [[nodiscard]] virtual std::optional<std::vector<size_t>> get_unread_email_ids(
            std::string_view folder) const = 0;
        [[nodiscard]] virtual std::optional<std::string> get_email(
            std::string_view folder, size_t id) const = 0;
        [[nodiscard]] virtual std::optional<std::string> get_email_subject(
            std::string_view folder, size_t id) const = 0;

    protected:
        imap_connection_adaptor() = default;
    };


    class imap_connection : public imap_connection_adaptor {
    private:
        static inline const std::unordered_map<email_server_provider_t, std::string_view> email_server_provider_to_url{
            { email_server_provider_t::gmail, "imaps://imap.gmail.com" },
            { email_server_provider_t::hotmail, "imaps://imap-mail.outlook.com" },
            { email_server_provider_t::yahoo, "imaps://imap.mail.yahoo.com" }
        };
        static inline const size_t email_server_port{ 993 };

        void setup_easy(curl::curl_easy& easy) const;
        [[nodiscard]] auto parse_get_mailbox_folders_response(const std::string& response) const -> std::vector<std::string>;
        [[nodiscard]] auto parse_get_unread_email_ids_response(std::string response) const -> std::vector<std::size_t>;
        [[nodiscard]] auto parse_email_subject(const std::string& email) const -> std::optional<std::string>;

    public:
        imap_connection(email_server_provider_t provider, std::string_view username, std::string_view password);
        [[nodiscard]] virtual std::optional<std::vector<std::string>> get_mailbox_folders() const override;
        [[nodiscard]] virtual std::optional<std::vector<size_t>> get_unread_email_ids(
            std::string_view folder) const override;
        [[nodiscard]] virtual std::optional<std::string> get_email(
            std::string_view folder, size_t id) const override;
        [[nodiscard]] virtual std::optional<std::string> get_email_subject(
            std::string_view folder, size_t id) const override;

    private:
        email_server_provider_t provider_{};
        std::string url_{};
        std::string username_{};
        std::string password_{};
    };
}  // namespace tmcppc::imap
