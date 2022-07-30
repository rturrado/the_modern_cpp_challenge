#include "chapter_12_networking_and_services/face_detection.h"
#include "chapter_12_networking_and_services/faces.h"
#include "chapter_12_networking_and_services/json_faces.h"

#include "rtc/filesystem.h"

#include "curl_easy.h"
#include "curl_header.h"

#include "nlohmann/json.hpp"

#include <filesystem>
#include <fmt/format.h>
#include <ostream>
#include <sstream>  // ostringstream
#include <string>
#include <variant>

namespace fs = std::filesystem;


namespace tmcppc::face_detection {
    provider_azure::provider_azure(std::string_view key) : key_{ key } {}

    [[nodiscard]] provider_response provider_azure::detect(const fs::path& path) const {
        try {
            std::ostringstream oss{};
            curl::curl_ios<std::ostringstream> writer{ oss };
            curl::curl_easy easy{ writer };

            easy.add<CURLOPT_URL>(fmt::format(
                "{}/Detect?returnFaceId=true&returnFaceLandmarks=true&returnFaceAttributes=age,gender,emotion", endpoint)
                .c_str());

            curl::curl_header header{};
            header.add(fmt::format("{}:{}", key_header, key_).c_str());
            header.add(content_type_header.data());
            auto file_content{ rtc::filesystem::get_binary_file_content<char>(path) };
            easy.add<CURLOPT_HTTPHEADER>(header.get());
            easy.add<CURLOPT_POSTFIELDSIZE>(static_cast<long>(file_content.size()));
            easy.add<CURLOPT_POSTFIELDS>(file_content.data());

            easy.perform();

            return { easy.get_info<CURLINFO_RESPONSE_CODE>().get(), oss.str() };
        } catch (const curl::curl_easy_exception& ex) {
            throw detection_error{ ex.what() };
        }
    }

    [[nodiscard]] std::variant<faces_response, error_response> detector::parse_detect_response(const provider_response& response) const {
        auto& [status, text] = response;
        nlohmann::json j = nlohmann::json::parse(text);
        if (status == 200) {
            faces_response faces_response = j;
            return faces_response;
        } else if (status >= 400) {
            error_response error_response = j;
            return error_response;
        }
        return faces_response{};
    }

    detector::detector(const provider_adaptor& provider) : provider_{ provider } {}

    [[nodiscard]] std::variant<faces_response, error_response> detector::detect(const fs::path& path) const {
        if (not fs::exists(path)) {
            throw rtc::filesystem::file_path_does_not_exist_error{ path.generic_string() };
        }

        try {
            return parse_detect_response(provider_.detect(path));
        } catch (const curl::curl_easy_exception& ex) {
            throw detection_error{ ex.what() };
        }
    }
}  // namespace tmcppc::face_detection
