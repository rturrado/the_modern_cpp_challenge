#include "../face_detection/samples.h"
#include "chapter_12_networking_and_services/face_detection/samples.h"
#include "chapter_12_networking_and_services/json/faces.h"

#include "nlohmann/json.hpp"

#include "gtest/gtest.h"

using namespace tmcppc::face_detection;


TEST(error, to_json) {
    nlohmann::json j;
    to_json(j, samples::error);
    EXPECT_EQ(j.dump(), samples::provider_response_text::error);
}
TEST(error, from_json) {
    nlohmann::json j = nlohmann::json::parse(samples::provider_response_text::error);
    error e{};
    from_json(j, e);
    EXPECT_EQ(e, samples::error);
}
TEST(error_response, to_json) {
    nlohmann::json j;
    to_json(j, samples::error_response);
    EXPECT_EQ(j.dump(), samples::provider_response_text::error_response);
}
TEST(error_response, from_json) {
    nlohmann::json j = nlohmann::json::parse(samples::provider_response_text::error_response);
    error_response er{};
    from_json(j, er);
    EXPECT_EQ(er, samples::error_response);
}
TEST(point, to_json) {
    nlohmann::json j;
    to_json(j, samples::point);
    EXPECT_EQ(j.dump(), samples::provider_response_text::point);
}
TEST(point, from_json) {
    nlohmann::json j = nlohmann::json::parse(samples::provider_response_text::point);
    point p{};
    from_json(j, p);
    EXPECT_EQ(p, samples::point);
}
TEST(rectangle, to_json) {
    nlohmann::json j;
    to_json(j, samples::rectangle);
    EXPECT_EQ(j.dump(), samples::provider_response_text::rectangle);
}
TEST(rectangle, from_json) {
    nlohmann::json j = nlohmann::json::parse(samples::provider_response_text::rectangle);
    rectangle r{};
    from_json(j, r);
    EXPECT_EQ(r, samples::rectangle);
}
TEST(face_landmarks, to_json) {
    nlohmann::json j;
    to_json(j, samples::face_landmarks_1);
    EXPECT_EQ(j.dump(), samples::provider_response_text::face_landmarks_1);
}
TEST(face_landmarks, from_json) {
    nlohmann::json j = nlohmann::json::parse(samples::provider_response_text::face_landmarks_1);
    face_landmarks fl{};
    from_json(j, fl);
    EXPECT_EQ(fl, samples::face_landmarks_1);
}
TEST(emotion, to_json) {
    nlohmann::json j;
    to_json(j, samples::emotion_1);
    EXPECT_EQ(j.dump(), samples::provider_response_text::emotion_1);
}
TEST(emotion, from_json) {
    nlohmann::json j = nlohmann::json::parse(samples::provider_response_text::emotion_1);
    emotion e{};
    from_json(j, e);
    EXPECT_EQ(e, samples::emotion_1);
}
TEST(face_attributes, to_json) {
    nlohmann::json j;
    to_json(j, samples::face_attributes_1);
    EXPECT_EQ(j.dump(), samples::provider_response_text::face_attributes_1);
}
TEST(face_attributes, from_json) {
    nlohmann::json j = nlohmann::json::parse(samples::provider_response_text::face_attributes_1);
    face_attributes fa{};
    from_json(j, fa);
    EXPECT_EQ(fa, samples::face_attributes_1);
}
TEST(face, to_json) {
    nlohmann::json j;
    to_json(j, samples::face_1);
    EXPECT_EQ(j.dump(), samples::provider_response_text::face_1);
}
TEST(face, from_json) {
    nlohmann::json j = nlohmann::json::parse(samples::provider_response_text::face_1);
    face fa{};
    from_json(j, fa);
    EXPECT_EQ(fa, samples::face_1);
}
TEST(faces_response, to_json) {
    nlohmann::json j;
    to_json(j, samples::faces_response);
    EXPECT_EQ(j.dump(), samples::provider_response_text::faces_response);
}
TEST(faces_response, from_json) {
    nlohmann::json j = nlohmann::json::parse(samples::provider_response_text::faces_response);
    faces_response fr{};
    from_json(j, fr);
    EXPECT_EQ(fr, samples::faces_response);
}
