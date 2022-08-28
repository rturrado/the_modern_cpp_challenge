#include "chapter_12_networking_and_services/face_detection.h"
#include "chapter_12_networking_and_services/face_detection/samples.h"
#include "chapter_12_networking_and_services/faces.h"
#include "chapter_12_networking_and_services/problem_100_detecting_faces_in_a_picture.h"
#include "env.h"
#include "face_detection/mock.h"
#include "face_detection/samples.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <filesystem>
#include <memory>  // make_unique, unique_ptr
#include <sstream>  // ostringstream
#include <variant>

using namespace tmcppc::face_detection;


TEST(test_face_detection, output) {
    std::unique_ptr<provider_adaptor> provider_up{ std::make_unique<provider_mock>() };
    auto& provider{ *(dynamic_cast<provider_mock*>(provider_up.get())) };
    EXPECT_CALL(provider, detect(tmcppc::env::get_instance().get_resource_folder_path() / "faces.jpg"))
        .WillOnce(::testing::Return(provider_response{ 200, samples::provider_response_text::faces_response }));

    std::ostringstream oss{};
    tmcppc::problem_100::test_face_detection(oss, detector{ std::move(provider_up) });

    EXPECT_THAT(oss.str(), ::testing::HasSubstr(samples::get_faces_response_output<1>()));
    EXPECT_THAT(oss.str(), ::testing::EndsWith("\n\n"));
    EXPECT_THAT(oss.str(), ::testing::Not(::testing::EndsWith("\n\n\n")));
}
