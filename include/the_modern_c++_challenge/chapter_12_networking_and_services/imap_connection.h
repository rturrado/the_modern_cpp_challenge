#pragma once

#include <iosfwd>
#include <memory>  // unique_ptr
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

    using mailbox_folder_t = std::string;
    using mailbox_folders_t = std::vector<mailbox_folder_t>;
    using id_t = size_t;
    using email_ids_t = std::vector<id_t>;
    using email_t = std::string;
    using email_subject_t = std::string;
    using email_subjects_t = std::vector<std::string>;


    struct imap_connection_error : public std::runtime_error {
        imap_connection_error(std::string_view message)
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

        void setup_easy(curl::curl_easy& easy) const;
    public:
        connector_curl(email_server_provider_t provider, std::string_view username, std::string_view password);

        [[nodiscard]] virtual std::string get_mailbox_folders() const override;
        [[nodiscard]] virtual std::string get_unread_email_ids(std::string_view folder) const override;
        [[nodiscard]] virtual std::string get_email(std::string_view folder, size_t id) const override;
    private:
        email_server_provider_t provider_{};
        std::string url_{};
        std::string username_{};
        std::string password_{};
    };


    class imap_connection {
    private:
        [[nodiscard]] mailbox_folders_t parse_get_mailbox_folders_response(const std::string& response) const;
        [[nodiscard]] email_ids_t parse_get_unread_email_ids_response(std::string response) const;
        [[nodiscard]] email_subject_t parse_email_subject(const std::string& email) const;
    public:
        imap_connection(std::unique_ptr<connector_adaptor> connector);

        [[nodiscard]] mailbox_folders_t get_mailbox_folders() const;
        [[nodiscard]] email_ids_t get_unread_email_ids(std::string_view folder) const;
        [[nodiscard]] email_t get_email(std::string_view folder, size_t id) const;
        [[nodiscard]] email_subject_t get_email_subject(std::string_view folder, size_t id) const;
    private:
        std::unique_ptr<connector_adaptor> connector_;
    };
}  // namespace tmcppc::imap
