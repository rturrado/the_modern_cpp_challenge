#include "chapter_12_networking_and_services/face_detection.h"
#include "chapter_12_networking_and_services/faces.h"
#include "chapter_12_networking_and_services/json_faces.h"

#include "rtc/filesystem.h"

#include "curl_easy.h"
#include "curl_header.h"

#include "nlohmann/json.hpp"

#include <filesystem>
#include <ostream>
#include <sstream>  // ostringstream
#include <string>
#include <variant>


namespace tmcppc::face_detection {
    detector::detector(std::string_view key) : key_{ key } {}

    [[nodiscard]] std::variant<faces_response, error_response> detector::parse_detect_response(const long status, const std::string& response) const {
        nlohmann::json j = nlohmann::json::parse(response);
        if (status == 200) {
            faces_response faces_response = j;
            return faces_response;
        } else if (status >= 400) {
            error_response error_response = j;
            return error_response;
        }
        return faces_response{};
    }

    [[nodiscard]] std::variant<faces_response, error_response> detector::detect(std::ostream& os, const std::filesystem::path& path) const {
        std::variant<faces_response, error_response> ret{};
        try {
            std::ostringstream oss{};
            curl::curl_ios<std::ostringstream> writer{ oss };
            curl::curl_easy easy{ writer };

            std::ostringstream oss_url{};
            oss_url << endpoint << "/Detect"
                << "?returnFaceId=true"
                << "&returnFaceLandmarks=true"
                << "&returnFaceAttributes=age,gender,emotion";
            easy.add<CURLOPT_URL>(oss_url.str().c_str());

            curl::curl_header header{};
            std::ostringstream oss_key_header{};
            oss_key_header << key_header << ":" << key_;
            header.add(oss_key_header.str().c_str());
            header.add(content_type_header.data());
            auto file_content{ rtc::filesystem::get_binary_file_content<char>(path) };
            easy.add<CURLOPT_HTTPHEADER>(header.get());
            easy.add<CURLOPT_POSTFIELDSIZE>(static_cast<long>(file_content.size()));
            easy.add<CURLOPT_POSTFIELDS>(file_content.data());

            easy.perform();

            ret = parse_detect_response(easy.get_info<CURLINFO_RESPONSE_CODE>().get(), oss.str());
        } catch (const curl::curl_easy_exception& ex) {
            fmt::print(os, "\tError: {}\n", ex.what());
        }
        return ret;
    }
}  // namespace tmcppc::face_detection
