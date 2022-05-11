#ifndef FACE_DETECTION_H
#define FACE_DETECTION_H

#include <filesystem>
#include <string>
#include <string_view>
#include <variant>


namespace rtc::face_detection
{
    struct FacesResponse;
    struct ErrorResponse;

    class detector {
    private:
        static inline const std::string_view endpoint{ "https://westeurope.api.cognitive.microsoft.com/face/v1.0" };
        static inline std::string_view key_header{ "Ocp-Apim-Subscription-Key" };
        static inline std::string_view content_type_header{ "Content-Type:application/octet-stream" };

        [[nodiscard]] std::variant<FacesResponse, ErrorResponse> parse_detect_response(const long status, const std::string& response) const;
    public:
        detector(std::string_view key);

        [[nodiscard]] std::variant<FacesResponse, ErrorResponse> detect(const std::filesystem::path& path) const;
    private:
        std::string key_{};
    };
}  // namespace rtc::face_detection


#endif  // FACE_DETECTION_H
