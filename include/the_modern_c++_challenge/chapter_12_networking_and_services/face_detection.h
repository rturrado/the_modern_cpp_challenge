#pragma once

#include <filesystem>
#include <iosfwd>
#include <stdexcept>  // runtime_error
#include <string>
#include <string_view>
#include <variant>


namespace tmcppc::face_detection {
    struct faces_response;
    struct error_response;


    struct detection_error : public std::runtime_error {
        detection_error(std::string_view message) : std::runtime_error{ message.data() } {}
    };


    struct provider_response {
        long status{};
        std::string text{};
    };


    class provider_adaptor {
    public:
        virtual ~provider_adaptor() = default;

        [[nodiscard]] virtual provider_response detect(const std::filesystem::path& path) const = 0;
    protected:
        provider_adaptor() = default;
    };


    class provider_azure : public provider_adaptor {
    private:
        static inline const std::string_view endpoint{ "https://westeurope.api.cognitive.microsoft.com/face/v1.0" };
        static inline std::string_view key_header{ "Ocp-Apim-Subscription-Key" };
        static inline std::string_view content_type_header{ "Content-Type:application/octet-stream" };
    public:
        provider_azure(std::string_view key);

        [[nodiscard]] virtual provider_response detect(const std::filesystem::path& path) const override;
    private:
        std::string key_{};
    };


    class detector {
    private:
        [[nodiscard]] std::variant<faces_response, error_response> parse_detect_response(const provider_response& response) const;
    public:
        detector(const provider_adaptor& provider);

        [[nodiscard]] std::variant<faces_response, error_response> detect(const std::filesystem::path& path) const;
    private:
        const provider_adaptor& provider_;
    };
}  // namespace tmcppc::face_detection
