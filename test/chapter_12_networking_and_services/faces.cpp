#include "chapter_12_networking_and_services/face_detection/samples.h"
#include "chapter_12_networking_and_services/faces.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <fmt/format.h>
#include <sstream>  // ostringstream
#include <string>

using namespace tmcppc::face_detection;


// Error
TEST(error, DISABLED_print) {
    std::ostringstream oss{};
    samples::error.print(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(samples::error_output));
}
TEST(error, DISABLED_println) {
    std::ostringstream oss{};
    samples::error.println(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(samples::error_output + "\n"));
}
TEST(error, DISABLED_operator_insertion) {
    std::ostringstream oss{};
    oss << samples::error;
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(samples::error_output));
}
TEST(error, DISABLED_fmt_format) {
    EXPECT_THAT(
        fmt::format("{}", samples::error),
        ::testing::HasSubstr(samples::error_output)
    );
}


// Error response
TEST(error_response, DISABLED_print) {
    std::ostringstream oss{};
    samples::error_response.print(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(samples::error_response_output));
}
TEST(error_response, DISABLED_println) {
    std::ostringstream oss{};
    samples::error_response.println(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(samples::error_response_output + "\n"));
}
TEST(error_response, DISABLED_operator_insertion) {
    std::ostringstream oss{};
    oss << samples::error_response;
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(samples::error_response_output));
}
TEST(error_response, DISABLED_fmt_format) {
    EXPECT_THAT(
        fmt::format("{}", samples::error_response),
        ::testing::HasSubstr(samples::error_response_output)
    );
}


// Point
TEST(point, DISABLED_print) {
    std::ostringstream oss{};
    samples::point.print(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(samples::point_output));
}
TEST(point, DISABLED_println) {
    std::ostringstream oss{};
    samples::point.println(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(samples::point_output + "\n"));
}
TEST(point, DISABLED_operator_insertion) {
    std::ostringstream oss{};
    oss << samples::point;
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(samples::point_output));
}
TEST(point, DISABLED_fmt_format) {
    EXPECT_THAT(
        fmt::format("{}", samples::point),
        ::testing::HasSubstr(samples::point_output)
    );
}


// Rectangle
TEST(rectangle, DISABLED_print) {
    std::ostringstream oss{};
    samples::rectangle.print(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(samples::rectangle_output));
}
TEST(rectangle, DISABLED_println) {
    std::ostringstream oss{};
    samples::rectangle.println(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(samples::rectangle_output + "\n"));
}
TEST(rectangle, DISABLED_operator_insertion) {
    std::ostringstream oss{};
    oss << samples::rectangle;
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(samples::rectangle_output));
}
TEST(rectangle, DISABLED_fmt_format) {
    EXPECT_THAT(
        fmt::format("{}", samples::rectangle),
        ::testing::HasSubstr(samples::rectangle_output)
    );
}


// Face landmarks
TEST(face_landmarks, DISABLED_print) {
    std::ostringstream oss{};
    samples::face_landmarks_1.print(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(samples::get_face_landmarks_1_output()));
}
TEST(face_landmarks, DISABLED_println) {
    std::ostringstream oss{};
    samples::face_landmarks_1.println(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(samples::get_face_landmarks_1_output() + "\n"));
}
TEST(face_landmarks, DISABLED_operator_insertion) {
    std::ostringstream oss{};
    oss << samples::face_landmarks_1;
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(samples::get_face_landmarks_1_output()));
}
TEST(face_landmarks, DISABLED_fmt_format) {
    EXPECT_THAT(
        fmt::format("{}", samples::face_landmarks_1),
        ::testing::HasSubstr(samples::get_face_landmarks_1_output())
    );
}


// Emotion
TEST(emotion, DISABLED_print) {
    std::ostringstream oss{};
    samples::emotion_1.print(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(samples::get_emotion_1_output()));
}
TEST(emotion, DISABLED_println) {
    std::ostringstream oss{};
    samples::emotion_1.println(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(samples::get_emotion_1_output() + "\n"));
}
TEST(emotion, DISABLED_operator_insertion) {
    std::ostringstream oss{};
    oss << samples::emotion_1;
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(samples::get_emotion_1_output()));
}
TEST(emotion, DISABLED_fmt_format) {
    EXPECT_THAT(
        fmt::format("{}", samples::emotion_1),
        ::testing::HasSubstr(samples::get_emotion_1_output())
    );
}


// Face attributes
TEST(face_attributes, DISABLED_print) {
    std::ostringstream oss{};
    samples::face_attributes_1.print(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(samples::get_face_attributes_1_output()));
}
TEST(face_attributes, DISABLED_println) {
    std::ostringstream oss{};
    samples::face_attributes_1.println(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(samples::get_face_attributes_1_output() + "\n"));
}
TEST(face_attributes, DISABLED_operator_insertion) {
    std::ostringstream oss{};
    oss << samples::face_attributes_1;
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(samples::get_face_attributes_1_output()));
}
TEST(face_attributes, DISABLED_fmt_format) {
    EXPECT_THAT(
        fmt::format("{}", samples::face_attributes_1),
        ::testing::HasSubstr(samples::get_face_attributes_1_output())
    );
}


// Face
TEST(face, DISABLED_print) {
    std::ostringstream oss{};
    samples::face_1.print(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(samples::get_face_1_output()));
}
TEST(face, DISABLED_println) {
    std::ostringstream oss{};
    samples::face_1.println(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(samples::get_face_1_output() + "\n"));
}
TEST(face, DISABLED_operator_insertion) {
    std::ostringstream oss{};
    oss << samples::face_1;
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(samples::get_face_1_output()));
}
TEST(face, DISABLED_fmt_format) {
    EXPECT_THAT(
        fmt::format("{}", samples::face_1),
        ::testing::HasSubstr(samples::get_face_1_output())
    );
}


// Faces response
TEST(faces_response, DISABLED_print) {
    std::ostringstream oss{};
    samples::faces_response.print(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(samples::get_faces_response_output()));
}
TEST(faces_response, DISABLED_println) {
    std::ostringstream oss{};
    samples::faces_response.println(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(samples::get_faces_response_output() + "\n"));
}
TEST(faces_response, DISABLED_operator_insertion) {
    std::ostringstream oss{};
    oss << samples::faces_response;
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(samples::get_faces_response_output()));
}
TEST(faces_response, DISABLED_fmt_format) {
    EXPECT_THAT(
        fmt::format("{}", samples::faces_response),
        ::testing::HasSubstr(samples::get_faces_response_output())
    );
}
