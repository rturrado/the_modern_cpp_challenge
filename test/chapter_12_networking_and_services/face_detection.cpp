#include "chapter_12_networking_and_services/face_detection.h"
#include "chapter_12_networking_and_services/face_detection/samples.h"
#include "chapter_12_networking_and_services/faces.h"
#include "env.h"
#include "face_detection/mock.h"
#include "face_detection/samples.h"

#include <filesystem>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <rtc/filesystem.h>
#include <utility>  // move
#include <variant>  // get, holds_alternative

namespace fs = std::filesystem;
using namespace tmcppc::face_detection;


TEST(detector, provider_is_null) { EXPECT_THROW(detector{ nullptr }, detection_error); }


TEST(detector, detect_and_file_does_not_exist) {
    EXPECT_THROW((void) detector{ std::make_unique<provider_mock>() }.detect(fs::path{}),
        rtc::filesystem::file_path_does_not_exist_error
    );
}


TEST(detector, detect_and_provider_returns_an_error_response) {
    std::unique_ptr<provider_adaptor> provider_up{ std::make_unique<provider_mock>() };
    auto& provider{ *(dynamic_cast<provider_mock*>(provider_up.get())) };
    const auto input_file_path{ tmcppc::env::get_instance().get_resource_folder_path() / "sample_file.txt" };
    EXPECT_CALL(provider, detect(input_file_path))
        .WillOnce(::testing::Return(provider_response{ 401, samples::provider_response_text::error_response }));
    const auto& result{ detector{ std::move(provider_up) }.detect(input_file_path) };
    EXPECT_TRUE(std::holds_alternative<error_response>(result));
    const auto& error{ std::get<error_response>(result).error_ };
    EXPECT_EQ(error.code, samples::provider_response_text::error_code);
    EXPECT_EQ(error.message, samples::provider_response_text::error_message);
}


TEST(detector, detect_and_provider_returns_a_faces_response) {
    std::unique_ptr<provider_adaptor> provider_up{ std::make_unique<provider_mock>() };
    auto& provider{ *(dynamic_cast<provider_mock*>(provider_up.get())) };
    const auto input_file_path{ tmcppc::env::get_instance().get_resource_folder_path() / "faces.jpg" };
    EXPECT_CALL(provider, detect(input_file_path))
        .WillOnce(::testing::Return(provider_response{ 200, samples::provider_response_text::faces_response }));
    const auto& result{ detector{ std::move(provider_up) }.detect(input_file_path) };
    EXPECT_TRUE(std::holds_alternative<faces_response>(result));
    const auto& faces{ std::get<faces_response>(result).faces };
    EXPECT_EQ(faces, samples::faces_response.faces);
}
