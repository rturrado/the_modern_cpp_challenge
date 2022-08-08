#include "chapter_12_networking_and_services/face_detection.h"
#include "chapter_12_networking_and_services/faces.h"
#include "env.h"
#include "face_detection/mock.h"
#include "face_detection/samples.h"

#include "rtc/filesystem.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <filesystem>
#include <memory>  // make_unique, unique_ptr
#include <variant>  // get, holds_alternative

using namespace tmcppc::face_detection;
namespace fs = std::filesystem;


TEST(detector, DISABLED_detect_and_file_does_not_exist) {
    EXPECT_THROW((void) detector{ std::make_unique<provider_mock>() }.detect(fs::path{}),
        rtc::filesystem::file_path_does_not_exist_error
    );
}


TEST(detector, DISABLED_detect_and_provider_returns_an_error_response) {
    std::unique_ptr<provider_adaptor> provider_up{ std::make_unique<provider_mock>() };
    auto& provider{ *(dynamic_cast<provider_mock*>(provider_up.get())) };
    const auto input_file_path{ tmcppc::env::get_instance().get_resource_folder_path() / "sample_file.txt" };
    EXPECT_CALL(provider, detect(input_file_path))
        .WillOnce(::testing::Return(provider_response{
            401,
            R"({"error":{"code":"401","message" : "Access denied due to invalid subscription key or wrong API endpoint. )"
            R"(Make sure to provide a valid key for an active subscription and )"
            R"(use a correct regional API endpoint for your resource."}})"
        }));
    const auto& result{ detector{ std::move(provider_up) }.detect(input_file_path) };
    EXPECT_TRUE(std::holds_alternative<error_response>(result));
    const auto& error{ std::get<error_response>(result).error_ };
    EXPECT_EQ(error.code, "401");
    EXPECT_EQ(error.message,
        "Access denied due to invalid subscription key or wrong API endpoint. "
        "Make sure to provide a valid key for an active subscription and "
        "use a correct regional API endpoint for your resource."
    );
}


TEST(detector, DISABLED_detect_and_provider_returns_a_faces_response) {
    std::unique_ptr<provider_adaptor> provider_up{ std::make_unique<provider_mock>() };
    auto& provider{ *(dynamic_cast<provider_mock*>(provider_up.get())) };
    const auto input_file_path{ tmcppc::env::get_instance().get_resource_folder_path() / "faces.jpg" };
    EXPECT_CALL(provider, detect(input_file_path))
        .WillOnce(::testing::Return(provider_response{ 200, samples::faces_response_text }));
    const auto& result{ detector{ std::move(provider_up) }.detect(input_file_path) };
    EXPECT_TRUE(std::holds_alternative<faces_response>(result));
    const auto& faces{ std::get<faces_response>(result).faces };
    EXPECT_THAT(faces, ::testing::ElementsAre(
        face{
            "473bc81f-6c04-498d-8581-0d22184b1637",
            rectangle{118, 615, 100, 100},
            face_landmarks{
                point{645, 146},
                point{685, 144},
                point{662, 166},
                point{646, 194},
                point{685, 194},
                point{628, 135},
                point{658, 137},
                point{638, 147},
                point{643, 144},
                point{644, 149},
                point{651, 146},
                point{671, 136},
                point{702, 137},
                point{679, 145},
                point{686, 142},
                point{686, 147},
                point{692, 146},
                point{656, 146},
                point{671, 146},
                point{653, 160},
                point{674, 160},
                point{649, 169},
                point{678, 169},
                point{663, 186},
                point{662, 191},
                point{663, 198},
                point{663, 206}
            },
            face_attributes{
                "male",
                31.0,
                emotion{0.031, 0.001, 0.000, 0.000, 0.001, 0.940, 0.000, 0.027}
            }
        },
        face{
            "a4834808-6727-4004-8e7a-b16d5f857694",
            rectangle{29, 268, 94, 94},
            face_landmarks{
                point{298, 52},
                point{337, 57},
                point{314, 75},
                point{293, 97},
                point{329, 101},
                point{282, 39},
                point{309, 42},
                point{290, 51},
                point{297, 48},
                point{296, 55},
                point{305, 53},
                point{327, 45},
                point{356, 50},
                point{330, 56},
                point{338, 52},
                point{337, 60},
                point{345, 58},
                point{310, 54},
                point{324, 56},
                point{305, 68},
                point{326, 71},
                point{300, 74},
                point{327, 78},
                point{313, 87},
                point{312, 94},
                point{310, 99},
                point{309, 108},
            },
            face_attributes{
                "male",
                34.0,
                emotion{0.000, 0.000, 0.000, 0.001, 0.000, 0.886, 0.000, 0.112}
            }
        }
    ));
}
