#include "chapter_12_networking_and_services/face_detection/samples.h"
#include "chapter_12_networking_and_services/faces.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <fmt/format.h>
#include <sstream>  // ostringstream
#include <string>

using namespace tmcppc::face_detection;


// Error
TEST(error, print) {
    std::ostringstream oss{};
    samples::error.print(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(samples::error_output));
}
TEST(error, println) {
    std::ostringstream oss{};
    samples::error.println(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(samples::error_output + "\n"));
}
TEST(error, operator_insertion) {
    std::ostringstream oss{};
    oss << samples::error;
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(samples::error_output));
}
TEST(error, fmt_format) {
    EXPECT_THAT(
        fmt::format("{}", samples::error),
        ::testing::HasSubstr(samples::error_output)
    );
}


// Error response
TEST(error_response, print) {
    std::ostringstream oss{};
    samples::error_response.print(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(samples::error_response_output));
}
TEST(error_response, println) {
    std::ostringstream oss{};
    samples::error_response.println(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(samples::error_response_output + "\n"));
}
TEST(error_response, operator_insertion) {
    std::ostringstream oss{};
    oss << samples::error_response;
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(samples::error_response_output));
}
TEST(error_response, fmt_format) {
    EXPECT_THAT(
        fmt::format("{}", samples::error_response),
        ::testing::HasSubstr(samples::error_response_output)
    );
}


// Point
TEST(point, print) {
    std::ostringstream oss{};
    samples::point.print(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(samples::point_output));
}
TEST(point, println) {
    std::ostringstream oss{};
    samples::point.println(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(samples::point_output + "\n"));
}
TEST(point, operator_insertion) {
    std::ostringstream oss{};
    oss << samples::point;
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(samples::point_output));
}
TEST(point, fmt_format) {
    EXPECT_THAT(
        fmt::format("{}", samples::point),
        ::testing::HasSubstr(samples::point_output)
    );
}


// Rectangle
TEST(rectangle, print) {
    std::ostringstream oss{};
    samples::rectangle.print(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(samples::rectangle_output));
}
TEST(rectangle, println) {
    std::ostringstream oss{};
    samples::rectangle.println(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(samples::rectangle_output + "\n"));
}
TEST(rectangle, operator_insertion) {
    std::ostringstream oss{};
    oss << samples::rectangle;
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(samples::rectangle_output));
}
TEST(rectangle, fmt_format) {
    EXPECT_THAT(
        fmt::format("{}", samples::rectangle),
        ::testing::HasSubstr(samples::rectangle_output)
    );
}


// Face landmarks
TEST(face_landmarks, print) {
    std::ostringstream oss{};
    samples::face_landmarks_1.print(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(samples::get_face_landmarks_1_output()));
}
TEST(face_landmarks, println) {
    std::ostringstream oss{};
    samples::face_landmarks_1.println(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(samples::get_face_landmarks_1_output() + "\n"));
}
TEST(face_landmarks, operator_insertion) {
    std::ostringstream oss{};
    oss << samples::face_landmarks_1;
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(samples::get_face_landmarks_1_output()));
}
TEST(face_landmarks, fmt_format) {
    EXPECT_THAT(
        fmt::format("{}", samples::face_landmarks_1),
        ::testing::HasSubstr(samples::get_face_landmarks_1_output())
    );
}


// Emotion
TEST(emotion, print) {
    std::ostringstream oss{};
    samples::emotion_1.print(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(samples::get_emotion_1_output()));
}
TEST(emotion, println) {
    std::ostringstream oss{};
    samples::emotion_1.println(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(samples::get_emotion_1_output() + "\n"));
}
TEST(emotion, operator_insertion) {
    std::ostringstream oss{};
    oss << samples::emotion_1;
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(samples::get_emotion_1_output()));
}
TEST(emotion, fmt_format) {
    EXPECT_THAT(
        fmt::format("{}", samples::emotion_1),
        ::testing::HasSubstr(samples::get_emotion_1_output())
    );
}


// Face attributes
TEST(face_attributes, print) {
    std::ostringstream oss{};
    samples::face_attributes_1.print(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(samples::get_face_attributes_1_output()));
}
TEST(face_attributes, println) {
    std::ostringstream oss{};
    samples::face_attributes_1.println(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(samples::get_face_attributes_1_output() + "\n"));
}
TEST(face_attributes, operator_insertion) {
    std::ostringstream oss{};
    oss << samples::face_attributes_1;
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(samples::get_face_attributes_1_output()));
}
TEST(face_attributes, fmt_format) {
    EXPECT_THAT(
        fmt::format("{}", samples::face_attributes_1),
        ::testing::HasSubstr(samples::get_face_attributes_1_output())
    );
}


// Face
TEST(face, print) {
    std::ostringstream oss{};
    samples::face_1.print(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(samples::get_face_1_output()));
}
TEST(face, println) {
    std::ostringstream oss{};
    samples::face_1.println(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(samples::get_face_1_output() + "\n"));
}
TEST(face, operator_insertion) {
    std::ostringstream oss{};
    oss << samples::face_1;
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(samples::get_face_1_output()));
}
TEST(face, fmt_format) {
    EXPECT_THAT(
        fmt::format("{}", samples::face_1),
        ::testing::HasSubstr(samples::get_face_1_output())
    );
}


// Faces response
TEST(faces_response, print) {
    std::ostringstream oss{};
    samples::faces_response.print(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(samples::get_faces_response_output()));
}
TEST(faces_response, println) {
    std::ostringstream oss{};
    samples::faces_response.println(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(samples::get_faces_response_output() + "\n"));
}
TEST(faces_response, operator_insertion) {
    std::ostringstream oss{};
    oss << samples::faces_response;
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(samples::get_faces_response_output()));
}
TEST(faces_response, fmt_format) {
    EXPECT_THAT(
        fmt::format("{}", samples::faces_response),
        ::testing::HasSubstr(samples::get_faces_response_output())
    );
}
