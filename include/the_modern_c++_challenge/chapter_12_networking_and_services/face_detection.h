#pragma once

#include "chapter_12_networking_and_services/faces.h"
#include "chapter_12_networking_and_services/json/faces.h"

#include <curl_easy.h>
#include <curl_header.h>
#include <fmt/format.h>
#include <filesystem>
#include <memory>  // unique_ptr
#include <nlohmann/json.hpp>
#include <ostream>
#include <rtc/filesystem.h>
#include <sstream>  // ostringstream
#include <stdexcept>  // runtime_error
#include <string>
#include <string_view>
#include <utility>  // move
#include <variant>


namespace tmcppc::face_detection {
    struct faces_response;
    struct error_response;


    struct detection_error : public std::runtime_error {
        detection_error(std::string_view message)
            : std::runtime_error{ message.data() }
        {}
    };


    struct provider_response {
        long status{};
        std::string text{};
    };


    struct provider_adaptor {
        virtual ~provider_adaptor() = default;

        [[nodiscard]] virtual provider_response detect(const std::filesystem::path& path) const = 0;
    };


    class provider_azure : public provider_adaptor {
    private:
        static inline const std::string_view endpoint{ "https://westeurope.api.cognitive.microsoft.com/face/v1.0" };
        static inline std::string_view key_header{ "Ocp-Apim-Subscription-Key" };
        static inline std::string_view content_type_header{ "Content-Type:application/octet-stream" };
    public:
        provider_azure(std::string_view key)
            : key_{ key }
        {}

        [[nodiscard]] provider_response detect(const std::filesystem::path& path) const override {
            try {
                std::ostringstream oss{};
                curl::curl_ios<std::ostringstream> writer{ oss };
                curl::curl_easy easy{ writer };

                easy.add<CURLOPT_URL>(
                    fmt::format(
                        "{}/Detect?returnFaceId=true&returnFaceLandmarks=true&returnFaceAttributes=age,gender,emotion",
                        endpoint
                    ).c_str()
                );

                curl::curl_header header{};
                header.add(fmt::format("{}:{}", key_header, key_));
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
    private:
        std::string key_{};
    };


    using detector_response_t = std::variant<faces_response, error_response>;


    class detector {
    private:
        [[nodiscard]] static detector_response_t parse_detect_response(const provider_response& response) {
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
    public:
        detector(std::unique_ptr<provider_adaptor> provider)
            : provider_{ std::move(provider) } {

            if (not provider_) {
                throw detection_error{ "provider is null" };
            }
        }

        [[nodiscard]] detector_response_t detect(const std::filesystem::path& path) const {
            if (not std::filesystem::exists(path)) {
                throw rtc::filesystem::file_path_does_not_exist_error{ path.generic_string() };
            }

            return parse_detect_response(provider_->detect(path));
        }
    private:
        std::unique_ptr<provider_adaptor> provider_;
    };
}  // namespace tmcppc::face_detection
