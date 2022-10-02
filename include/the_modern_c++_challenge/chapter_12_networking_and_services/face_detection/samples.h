#pragma once

#include "../faces.h"

#include <fmt/format.h>
#include <rtc/pretty_print.h>
#include <string>


namespace tmcppc::face_detection::samples {
    // Error
    static inline const tmcppc::face_detection::error error{ .code = "401", .message =
        "Access denied due to invalid subscription key or wrong API endpoint. "
        "Make sure to provide a valid key for an active subscription and "
        "use a correct regional API endpoint for your resource."
    };
    static inline const std::string error_output{
        fmt::format(
            "(code: {}, message: '{}')",
            "401",
            "Access denied due to invalid subscription key or wrong API endpoint. "
            "Make sure to provide a valid key for an active subscription and "
            "use a correct regional API endpoint for your resource."
        )
    };


    // Error response
    static inline const tmcppc::face_detection::error_response error_response{
        .error_ = error
    };
    static inline const std::string error_response_output{ fmt::format("Error: {}", error_output) };


    // Point
    static inline const tmcppc::face_detection::point point{
        .x = 645.0,
        .y = 146.8
    };
    static inline const std::string point_output{ "(x: 645.0, y: 146.8)" };


    // Rectangle
    static inline const tmcppc::face_detection::rectangle rectangle{
        .top = 118.0,
        .left = 615.0,
        .width = 100.0,
        .height = 100.0
    };
    static inline const std::string rectangle_output{ "(top: 118.0, left: 615.0, width: 100.0, height: 100.0)" };


    // Face landmarks
    static inline const tmcppc::face_detection::face_landmarks face_landmarks_1{
        .pupil_left = { .x = 645.0, .y = 146.8 },
        .pupil_right = { .x = 685.6, .y = 144.9 },
        .nose_tip = { .x = 662.3, .y = 166.6 },
        .mouth_left = { .x = 646.4, .y = 194.5 },
        .mouth_right = { .x = 685.9, .y = 194.2 },
        .eyebrow_left_outer = { .x = 628.5, .y = 135.1 },
        .eyebrow_left_inner = { .x = 658.3, .y = 137.0 },
        .eye_left_outer = { .x = 638.3, .y = 147.9 },
        .eye_left_top = { .x = 643.9, .y = 144.5 },
        .eye_left_bottom = { .x = 644.8, .y = 149.2 },
        .eye_left_inner = { .x = 651.3, .y = 146.8 },
        .eyebrow_right_inner = { .x = 671.9, .y = 136.1 },
        .eyebrow_right_outer = { .x = 702.9, .y = 137.2 },
        .eye_right_inner = { .x = 679.3, .y = 145.2 },
        .eye_right_top = { .x = 686.9, .y = 142.7 },
        .eye_right_bottom = { .x = 686.2, .y = 147.5 },
        .eye_right_outer = { .x = 692.7, .y = 146.1 },
        .nose_root_left = { .x = 656.8, .y = 146.2 },
        .nose_root_right = { .x = 671.3, .y = 146.4 },
        .nose_left_alar_top = { .x = 653.2, .y = 160.8 },
        .nose_right_alar_top = { .x = 674.1, .y = 160.8 },
        .nose_left_alar_out_tip = { .x = 649.7, .y = 169.6 },
        .nose_right_alar_out_tip = { .x = 678.9, .y = 169.1 },
        .upper_lip_top = { .x = 663.0, .y = 186.7 },
        .upper_lip_bottom = { .x = 662.8, .y = 191.8 },
        .under_lip_top = { .x = 663.6, .y = 198.3 },
        .under_lip_bottom = { .x = 663.4, .y = 206.4 }
    };
    static inline const tmcppc::face_detection::face_landmarks face_landmarks_2{
        .pupil_left = { .x = 298.6, .y = 52.2 },
        .pupil_right = { .x = 337.6, .y = 57.2 },
        .nose_tip = { .x = 314.1, .y = 75.0 },
        .mouth_left = { .x = 293.4, .y = 97.8 },
        .mouth_right = { .x = 329.8, .y = 101.4 },
        .eyebrow_left_outer = { .x = 282.4, .y = 39.7 },
        .eyebrow_left_inner = { .x = 309.7, .y = 42.4 },
        .eye_left_outer = { .x = 290.5, .y = 51.6 },
        .eye_left_top = { .x = 297.7, .y = 48.6 },
        .eye_left_bottom = { .x = 296.6, .y = 55.7 },
        .eye_left_inner = { .x = 305.2, .y = 53.4 },
        .eyebrow_right_inner = { .x = 327.4, .y = 45.3 },
        .eyebrow_right_outer = { .x = 356.8, .y = 50.2 },
        .eye_right_inner = { .x = 330.7, .y = 56.7 },
        .eye_right_top = { .x = 338.9, .y = 52.9 },
        .eye_right_bottom = { .x = 337.4, .y = 60.7 },
        .eye_right_outer = { .x = 345.1, .y = 58.6 },
        .nose_root_left = { .x = 310.9, .y = 54.9 },
        .nose_root_right = { .x = 324.6, .y = 56.6 },
        .nose_left_alar_top = { .x = 305.7, .y = 68.5 },
        .nose_right_alar_top = { .x = 326.5, .y = 71.6 },
        .nose_left_alar_out_tip = { .x = 300.7, .y = 74.8 },
        .nose_right_alar_out_tip = { .x = 327.9, .y = 78.6 },
        .upper_lip_top = { .x = 313.7, .y = 87.4 },
        .upper_lip_bottom = { .x = 312.9, .y = 94.3 },
        .under_lip_top = { .x = 310.7, .y = 99.3 },
        .under_lip_bottom = { .x = 309.3, .y = 108.9 }
    };
    template <size_t L = 0>
    auto get_face_landmarks_1_output() {
        return fmt::format(
            "{0}Face landmarks:\n"
            "{1}Pupil left: {2}\n"
            "{1}Pupil right: (x: 685.6, y: 144.9)\n"
            "{1}Nose tip: (x: 662.3, y: 166.6)\n"
            "{1}Mouth left: (x: 646.4, y: 194.5)\n"
            "{1}Mouth right: (x: 685.9, y: 194.2)\n"
            "{1}Eyebrow left outer: (x: 628.5, y: 135.1)\n"
            "{1}Eyebrow left inner: (x: 658.3, y: 137.0)\n"
            "{1}Eye left outer: (x: 638.3, y: 147.9)\n"
            "{1}Eye left top: (x: 643.9, y: 144.5)\n"
            "{1}Eye left bottom: (x: 644.8, y: 149.2)\n"
            "{1}Eye left inner: (x: 651.3, y: 146.8)\n"
            "{1}Eyebrow right inner: (x: 671.9, y: 136.1)\n"
            "{1}Eyebrow right outer: (x: 702.9, y: 137.2)\n"
            "{1}Eye right inner: (x: 679.3, y: 145.2)\n"
            "{1}Eye right top: (x: 686.9, y: 142.7)\n"
            "{1}Eye right bottom: (x: 686.2, y: 147.5)\n"
            "{1}Eye right outer: (x: 692.7, y: 146.1)\n"
            "{1}Nose root left: (x: 656.8, y: 146.2)\n"
            "{1}Nose root right: (x: 671.3, y: 146.4)\n"
            "{1}Nose left alar top: (x: 653.2, y: 160.8)\n"
            "{1}Nose right alar top: (x: 674.1, y: 160.8)\n"
            "{1}Nose left alar out tip: (x: 649.7, y: 169.6)\n"
            "{1}Nose right alar out tip: (x: 678.9, y: 169.1)\n"
            "{1}Upper lip top: (x: 663.0, y: 186.7)\n"
            "{1}Upper lip bottom: (x: 662.8, y: 191.8)\n"
            "{1}Under lip top: (x: 663.6, y: 198.3)\n"
            "{1}Under lip bottom: (x: 663.4, y: 206.4)",
            rtc::pretty_print::indentation{ L },
            rtc::pretty_print::indentation{ L + 1 },
            point_output
        );
    }
    template <size_t L = 0>
    auto get_face_landmarks_2_output() {
        return fmt::format(
            "{0}Face landmarks:\n"
            "{1}Pupil left: (x: 298.6, y: 52.2)\n"
            "{1}Pupil right: (x: 337.6, y: 57.2)\n"
            "{1}Nose tip: (x: 314.1, y: 75.0)\n"
            "{1}Mouth left: (x: 293.4, y: 97.8)\n"
            "{1}Mouth right: (x: 329.8, y: 101.4)\n"
            "{1}Eyebrow left outer: (x: 282.4, y: 39.7)\n"
            "{1}Eyebrow left inner: (x: 309.7, y: 42.4)\n"
            "{1}Eye left outer: (x: 290.5, y: 51.6)\n"
            "{1}Eye left top: (x: 297.7, y: 48.6)\n"
            "{1}Eye left bottom: (x: 296.6, y: 55.7)\n"
            "{1}Eye left inner: (x: 305.2, y: 53.4)\n"
            "{1}Eyebrow right inner: (x: 327.4, y: 45.3)\n"
            "{1}Eyebrow right outer: (x: 356.8, y: 50.2)\n"
            "{1}Eye right inner: (x: 330.7, y: 56.7)\n"
            "{1}Eye right top: (x: 338.9, y: 52.9)\n"
            "{1}Eye right bottom: (x: 337.4, y: 60.7)\n"
            "{1}Eye right outer: (x: 345.1, y: 58.6)\n"
            "{1}Nose root left: (x: 310.9, y: 54.9)\n"
            "{1}Nose root right: (x: 324.6, y: 56.6)\n"
            "{1}Nose left alar top: (x: 305.7, y: 68.5)\n"
            "{1}Nose right alar top: (x: 326.5, y: 71.6)\n"
            "{1}Nose left alar out tip: (x: 300.7, y: 74.8)\n"
            "{1}Nose right alar out tip: (x: 327.9, y: 78.6)\n"
            "{1}Upper lip top: (x: 313.7, y: 87.4)\n"
            "{1}Upper lip bottom: (x: 312.9, y: 94.3)\n"
            "{1}Under lip top: (x: 310.7, y: 99.3)\n"
            "{1}Under lip bottom: (x: 309.3, y: 108.9)",
            rtc::pretty_print::indentation{ L },
            rtc::pretty_print::indentation{ L + 1 }
        );
    }


    // Emotion
    static inline const tmcppc::face_detection::emotion emotion_1{
        .anger = 0.031,
        .contempt = 0.001,
        .disgust = 0.0,
        .fear = 0.0,
        .happiness = 0.001,
        .neutral = 0.94,
        .sadness = 0.0,
        .surprise = 0.027
    };
    static inline const tmcppc::face_detection::emotion emotion_2{
        .anger = 0.0,
        .contempt = 0.0,
        .disgust = 0.0,
        .fear = 0.001,
        .happiness = 0.0,
        .neutral = 0.886,
        .sadness = 0.0,
        .surprise = 0.112
    };
    template <size_t L = 0>
    auto get_emotion_1_output() {
        return fmt::format(
            "{0}Emotion:\n"
            "{1}Anger: 0.031\n"
            "{1}Contempt: 0.001\n"
            "{1}Disgust: 0.000\n"
            "{1}Fear: 0.000\n"
            "{1}Happiness: 0.001\n"
            "{1}Neutral: 0.940\n"
            "{1}Sadness: 0.000\n"
            "{1}Surprise: 0.027",
            rtc::pretty_print::indentation{ L },
            rtc::pretty_print::indentation{ L + 1 }
        );
    }
    template <size_t L = 0>
    auto get_emotion_2_output() {
        return fmt::format(
            "{0}Emotion:\n"
            "{1}Anger: 0.000\n"
            "{1}Contempt: 0.000\n"
            "{1}Disgust: 0.000\n"
            "{1}Fear: 0.001\n"
            "{1}Happiness: 0.000\n"
            "{1}Neutral: 0.886\n"
            "{1}Sadness: 0.000\n"
            "{1}Surprise: 0.112",
            rtc::pretty_print::indentation{ L },
            rtc::pretty_print::indentation{ L + 1 }
        );
    }


    // Face attributes
    static inline const tmcppc::face_detection::face_attributes face_attributes_1{
        .gender = "male",
        .age = 31.0,
        .emotion_ = emotion_1
    };
    static inline const tmcppc::face_detection::face_attributes face_attributes_2{
        .gender = "male",
        .age = 34.0,
        .emotion_ = emotion_2
    };
    template <size_t L = 0>
    auto get_face_attributes_1_output() {
        return fmt::format(
            "{0}Face attributes:\n"
            "{1}Gender: male\n"
            "{1}Age: 31.0\n"
            "{2}",
            rtc::pretty_print::indentation{ L },
            rtc::pretty_print::indentation{ L + 1 },
            get_emotion_1_output<L + 1>()
        );
    }
    template <size_t L = 0>
    auto get_face_attributes_2_output() {
        return fmt::format(
            "{0}Face attributes:\n"
            "{1}Gender: male\n"
            "{1}Age: 34.0\n"
            "{2}",
            rtc::pretty_print::indentation{ L },
            rtc::pretty_print::indentation{ L + 1 },
            get_emotion_2_output<L + 1>()
        );
    }


    // Face
    static inline const tmcppc::face_detection::face face_1{
        .id = "473bc81f-6c04-498d-8581-0d22184b1637",
        .bounding_box = { .top = 118, .left = 615, .width = 100, .height = 100 },
        .landmarks = face_landmarks_1,
        .attributes = face_attributes_1
    };
    static inline const tmcppc::face_detection::face face_2{
        .id = "a4834808-6727-4004-8e7a-b16d5f857694",
        .bounding_box = { .top = 29, .left = 268, .width = 94, .height = 94 },
        .landmarks = face_landmarks_2,
        .attributes = face_attributes_2
    };
    template <size_t L = 0>
    auto get_face_1_output() {
        return fmt::format(
            "{0}Face:\n"
            "{1}ID: 473bc81f-6c04-498d-8581-0d22184b1637\n"
            "{1}Bounding box: {2}\n"
            "{3}\n"
            "{4}",
            rtc::pretty_print::indentation{ L },
            rtc::pretty_print::indentation{ L + 1 },
            rectangle_output,
            get_face_landmarks_1_output<L + 1>(),
            get_face_attributes_1_output<L + 1>()
        );
    }
    template <size_t L = 0>
    auto get_face_2_output() {
        return fmt::format(
            "{0}Face:\n"
            "{1}ID: a4834808-6727-4004-8e7a-b16d5f857694\n"
            "{1}Bounding box: (top: 29.0, left: 268.0, width: 94.0, height: 94.0)\n"
            "{2}\n"
            "{3}",
            rtc::pretty_print::indentation{ L },
            rtc::pretty_print::indentation{ L + 1 },
            get_face_landmarks_2_output<L + 1>(),
            get_face_attributes_2_output<L + 1>()
        );
    }


    // Faces response
    static inline const tmcppc::face_detection::faces_response faces_response{
        .faces = { face_1, face_2 }
    };
    template <size_t L = 0>
    auto get_faces_response_output() {
        return fmt::format(
            "{}Faces:\n"
            "{}\n"
            "{}",
            rtc::pretty_print::indentation{ L },
            get_face_1_output<L + 1>(),
            get_face_2_output<L + 1>()
        );
    }
}  // namespace tmcppc::face_detection::samples
