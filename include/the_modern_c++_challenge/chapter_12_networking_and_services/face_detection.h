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


    class detector_adaptor {
    public:
        virtual ~detector_adaptor() = default;

        [[nodiscard]] virtual std::variant<faces_response, error_response> detect(
            const std::filesystem::path& path) const = 0;
    protected:
        detector_adaptor() = default;
    };


    class detector_azure : public detector_adaptor {
    private:
        static inline const std::string_view endpoint{ "https://westeurope.api.cognitive.microsoft.com/face/v1.0" };
        static inline std::string_view key_header{ "Ocp-Apim-Subscription-Key" };
        static inline std::string_view content_type_header{ "Content-Type:application/octet-stream" };

        [[nodiscard]] std::variant<faces_response, error_response> parse_detect_response(
            const long status, const std::string& response) const;
    public:
        detector_azure(std::string_view key);

        [[nodiscard]] virtual std::variant<faces_response, error_response> detect(
            const std::filesystem::path& path) const override;
    private:
        std::string key_{};
    };
}  // namespace tmcppc::face_detection
