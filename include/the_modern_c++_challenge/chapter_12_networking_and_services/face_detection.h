#pragma once

#include <filesystem>
#include <iosfwd>
#include <string>
#include <string_view>
#include <variant>


namespace tmcppc::face_detection {
    struct faces_response;
    struct error_response;

    class detector {
    private:
        static inline const std::string_view endpoint{ "https://westeurope.api.cognitive.microsoft.com/face/v1.0" };
        static inline std::string_view key_header{ "Ocp-Apim-Subscription-Key" };
        static inline std::string_view content_type_header{ "Content-Type:application/octet-stream" };

        [[nodiscard]] std::variant<faces_response, error_response> parse_detect_response(const long status, const std::string& response) const;
    public:
        detector(std::string_view key);

        [[nodiscard]] std::variant<faces_response, error_response> detect(std::ostream& os, const std::filesystem::path& path) const;
    private:
        std::string key_{};
    };
}  // namespace tmcppc::face_detection
