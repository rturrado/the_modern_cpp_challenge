#pragma once

#include "fmt/format.h"

#include <string>


namespace tmcppc::face_detection::samples::provider_response_text {
    static inline const std::string error_code{ "401" };
    static inline const std::string error_message{
        R"(Access denied due to invalid subscription key or wrong API endpoint. )"
        R"(Make sure to provide a valid key for an active subscription and )"
        R"(use a correct regional API endpoint for your resource.)"
    };
    static inline const std::string error{ fmt::format(
        "{}\"code\":\"{}\",\"message\":\"{}\"{}",
        '{', error_code, error_message, '}'
    ) };
    static inline const std::string error_response{
        fmt::format("{}\"error\":{}{}", '{', error, '}')
    };
    static inline const std::string point{
        R"({"x":645.0,"y":146.8})"
    };
    static inline const std::string rectangle{
        R"({"height":100.0,"left":615.0,"top":118.0,"width":100.0})"
    };
    static inline const std::string face_id_1{
        R"("473bc81f-6c04-498d-8581-0d22184b1637")"
    };
    static inline const std::string face_id_2{
        R"("a4834808-6727-4004-8e7a-b16d5f857694")"
    };
    static inline const std::string face_rectangle_1{
        R"({"height":100.0,"left":615.0,"top":118.0,"width":100.0})"
    };
    static inline const std::string face_rectangle_2{
        R"({"height":94.0,"left":268.0,"top":29.0,"width":94.0})"
    };
    static inline const std::string face_landmarks_1{
        R"({)"
        R"("eyeLeftBottom":{"x":644.8,"y":149.2},)"
        R"("eyeLeftInner":{"x":651.3,"y":146.8},)"
        R"("eyeLeftOuter":{"x":638.3,"y":147.9},)"
        R"("eyeLeftTop":{"x":643.9,"y":144.5},)"
        R"("eyeRightBottom":{"x":686.2,"y":147.5},)"
        R"("eyeRightInner":{"x":679.3,"y":145.2},)"
        R"("eyeRightOuter":{"x":692.7,"y":146.1},)"
        R"("eyeRightTop":{"x":686.9,"y":142.7},)"
        R"("eyebrowLeftInner":{"x":658.3,"y":137.0},)"
        R"("eyebrowLeftOuter":{"x":628.5,"y":135.1},)"
        R"("eyebrowRightInner":{"x":671.9,"y":136.1},)"
        R"("eyebrowRightOuter":{"x":702.9,"y":137.2},)"
        R"("mouthLeft":{"x":646.4,"y":194.5},)"
        R"("mouthRight":{"x":685.9,"y":194.2},)"
        R"("noseLeftAlarOutTip":{"x":649.7,"y":169.6},)"
        R"("noseLeftAlarTop":{"x":653.2,"y":160.8},)"
        R"("noseRightAlarOutTip":{"x":678.9,"y":169.1},)"
        R"("noseRightAlarTop":{"x":674.1,"y":160.8},)"
        R"("noseRootLeft":{"x":656.8,"y":146.2},)"
        R"("noseRootRight":{"x":671.3,"y":146.4},)"
        R"("noseTip":{"x":662.3,"y":166.6},)"
        R"("pupilLeft":{"x":645.0,"y":146.8},)"
        R"("pupilRight":{"x":685.6,"y":144.9},)"
        R"("underLipBottom":{"x":663.4,"y":206.4},)"
        R"("underLipTop":{"x":663.6,"y":198.3},)"
        R"("upperLipBottom":{"x":662.8,"y":191.8},)"
        R"("upperLipTop":{"x":663.0,"y":186.7})"
        R"(})"
    };
    static inline const std::string face_landmarks_2{
        R"({)"
        R"("eyeLeftBottom":{"x":296.6,"y":55.7},)"
        R"("eyeLeftInner":{"x":305.2,"y":53.4},)"
        R"("eyeLeftOuter":{"x":290.5,"y":51.6},)"
        R"("eyeLeftTop":{"x":297.7,"y":48.6},)"
        R"("eyeRightBottom":{"x":337.4,"y":60.7},)"
        R"("eyeRightInner":{"x":330.7,"y":56.7},)"
        R"("eyeRightOuter":{"x":345.1,"y":58.6},)"
        R"("eyeRightTop":{"x":338.9,"y":52.9},)"
        R"("eyebrowLeftInner":{"x":309.7,"y":42.4},)"
        R"("eyebrowLeftOuter":{"x":282.4,"y":39.7},)"
        R"("eyebrowRightInner":{"x":327.4,"y":45.3},)"
        R"("eyebrowRightOuter":{"x":356.8,"y":50.2},)"
        R"("mouthLeft":{"x":293.4,"y":97.8},)"
        R"("mouthRight":{"x":329.8,"y":101.4},)"
        R"("noseLeftAlarOutTip":{"x":300.7,"y":74.8},)"
        R"("noseLeftAlarTop":{"x":305.7,"y":68.5},)"
        R"("noseRightAlarOutTip":{"x":327.9,"y":78.6},)"
        R"("noseRightAlarTop":{"x":326.5,"y":71.6},)"
        R"("noseRootLeft":{"x":310.9,"y":54.9},)"
        R"("noseRootRight":{"x":324.6,"y":56.6},)"
        R"("noseTip":{"x":314.1,"y":75.0},)"
        R"("pupilLeft":{"x":298.6,"y":52.2},)"
        R"("pupilRight":{"x":337.6,"y":57.2},)"
        R"("underLipBottom":{"x":309.3,"y":108.9},)"
        R"("underLipTop":{"x":310.7,"y":99.3},)"
        R"("upperLipBottom":{"x":312.9,"y":94.3},)"
        R"("upperLipTop":{"x":313.7,"y":87.4})"
        R"(})"
    };
    static inline const std::string emotion_1{
        R"({"anger":0.031,"contempt":0.001,"disgust":0.0,"fear":0.0,)"
        R"("happiness":0.001,"neutral":0.94,"sadness":0.0,"surprise":0.027})"
    };
    static inline const std::string emotion_2{
        R"({"anger":0.0,"contempt":0.0,"disgust":0.0,"fear":0.001,)"
        R"("happiness":0.0,"neutral":0.886,"sadness":0.0,"surprise":0.112})"
    };
    static inline const std::string face_attributes_1{ fmt::format(
        "{}\"age\":31.0,\"emotion\":{},\"gender\":\"male\"{}",
        '{', emotion_1, '}'
    ) };
    static inline const std::string face_attributes_2{ fmt::format(
        "{}\"age\":34.0,\"emotion\":{},\"gender\":\"male\"{}",
        '{', emotion_2, '}'
    ) };
    static inline const std::string face_1{ fmt::format(
        "{}\"faceAttributes\":{},\"faceId\":{},\"faceLandmarks\":{},\"faceRectangle\":{}{}",
        '{', face_attributes_1, face_id_1, face_landmarks_1, face_rectangle_1, '}'
    ) };
    static inline const std::string face_2{ fmt::format(
        "{}\"faceAttributes\":{},\"faceId\":{},\"faceLandmarks\":{},\"faceRectangle\":{}{}",
        '{', face_attributes_2, face_id_2, face_landmarks_2, face_rectangle_2, '}'
    ) };
    static inline const std::string faces_response{ fmt::format("[{},{}]", face_1, face_2) };
}  // namespace tmcppc::face_detection::samples::provider_response_text
