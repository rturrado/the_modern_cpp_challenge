#include "Chapter12_NetworkingAndServices/JsonFaces.h"
#include "Chapter12_NetworkingAndServices/FaceDetection.h"
#include "Chapter12_NetworkingAndServices/Faces.h"

#include "rtc/filesystem.h"

#include "curlcpp/master/include/curl_easy.h"
#include "curlcpp/master/include/curl_header.h"

#include "nlohmann/json.hpp"

#include <filesystem>
#include <sstream>  // ostringstream
#include <string>
#include <variant>


namespace rtc::face_detection
{
    detector::detector(std::string_view key) : key_{ key } {}

    [[nodiscard]] std::variant<FacesResponse, ErrorResponse> detector::parse_detect_response(const long status, const std::string& response) const
    {
        nlohmann::json j = nlohmann::json::parse(response);
        if (status == 200) {
            FacesResponse faces_response = j;
            return faces_response;
        }
        else if (status >= 400)
        {
            ErrorResponse error_response = j;
            return error_response;
        }
        return FacesResponse{};
    }

    [[nodiscard]] std::variant<FacesResponse, ErrorResponse> detector::detect(const std::filesystem::path& path) const
    {
        std::variant<FacesResponse, ErrorResponse> ret{};
        try
        {
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
        }
        catch (const curl::curl_easy_exception& ex) {
            std::cout << "\tError: " << ex.what() << "\n";
        }
        return ret;
    }

}  // namespace rtc::face_detection
