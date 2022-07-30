#pragma once

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <filesystem>
#include <string>


namespace tmcppc::face_detection {
    class provider_mock : public provider_adaptor {
    public:
        MOCK_METHOD((provider_response), detect, (const std::filesystem::path& path), (const, override));
    };

    namespace samples {
        static inline const std::string faces_response_text{
            R"([{"faceId":"473bc81f-6c04-498d-8581-0d22184b1637",)"
            R"("faceRectangle":{"top":118,"left":615,"width":100,"height":100},)"
            R"("faceLandmarks":{)"
            R"("pupilLeft":{"x":645.0,"y":146.8},"pupilRight":{"x":685.6,"y":144.9},)"
            R"("noseTip":{"x":662.3,"y":166.6},)"
            R"("mouthLeft":{"x":646.4,"y":194.5},"mouthRight":{"x":685.9,"y":194.2},)"
            R"("eyebrowLeftOuter":{"x":628.5,"y":135.1},"eyebrowLeftInner":{"x":658.3,"y":137.0},)"
            R"("eyeLeftOuter":{"x":638.3,"y":147.9},"eyeLeftTop":{"x":643.9,"y":144.5},)"
            R"("eyeLeftBottom":{"x":644.8,"y":149.2},"eyeLeftInner":{"x":651.3,"y":146.8},)"
            R"("eyebrowRightInner":{"x":671.9,"y":136.1},"eyebrowRightOuter":{"x":702.9,"y":137.2},)"
            R"("eyeRightInner":{"x":679.3,"y":145.2},"eyeRightTop":{"x":686.9,"y":142.7},)"
            R"("eyeRightBottom":{"x":686.2,"y":147.5},"eyeRightOuter":{"x":692.7,"y":146.1},)"
            R"("noseRootLeft":{"x":656.8,"y":146.2},"noseRootRight":{"x":671.3,"y":146.4},)"
            R"("noseLeftAlarTop":{"x":653.2,"y":160.8},"noseRightAlarTop":{"x":674.1,"y":160.8},)"
            R"("noseLeftAlarOutTip":{"x":649.7,"y":169.6},"noseRightAlarOutTip":{"x":678.9,"y":169.1},)"
            R"("upperLipTop":{"x":663.0,"y":186.7},"upperLipBottom":{"x":662.8,"y":191.8},)"
            R"("underLipTop":{"x":663.6,"y":198.3},"underLipBottom":{"x":663.4,"y":206.4}},)"
            R"("faceAttributes":{"gender":"male","age":31.0,)"
            R"("emotion":{"anger":0.031,"contempt":0.001,"disgust":0.0,"fear":0.0,)"
            R"("happiness":0.001,"neutral":0.94,"sadness":0.0,"surprise":0.027}}},)"
            R"({"faceId":"a4834808-6727-4004-8e7a-b16d5f857694",)"
            R"("faceRectangle":{"top":29,"left":268,"width":94,"height":94},)"
            R"("faceLandmarks":{)"
            R"("pupilLeft":{"x":298.6,"y":52.2},"pupilRight":{"x":337.6,"y":57.2},)"
            R"("noseTip":{"x":314.1,"y":75.0},)"
            R"("mouthLeft":{"x":293.4,"y":97.8},"mouthRight":{"x":329.8,"y":101.4},)"
            R"("eyebrowLeftOuter":{"x":282.4,"y":39.7},"eyebrowLeftInner":{"x":309.7,"y":42.4},)"
            R"("eyeLeftOuter":{"x":290.5,"y":51.6},"eyeLeftTop":{"x":297.7,"y":48.6},)"
            R"("eyeLeftBottom":{"x":296.6,"y":55.7},"eyeLeftInner":{"x":305.2,"y":53.4},)"
            R"("eyebrowRightInner":{"x":327.4,"y":45.3},"eyebrowRightOuter":{"x":356.8,"y":50.2},)"
            R"("eyeRightInner":{"x":330.7,"y":56.7},"eyeRightTop":{"x":338.9,"y":52.9},)"
            R"("eyeRightBottom":{"x":337.4,"y":60.7},"eyeRightOuter":{"x":345.1,"y":58.6},)"
            R"("noseRootLeft":{"x":310.9,"y":54.9},"noseRootRight":{"x":324.6,"y":56.6},)"
            R"("noseLeftAlarTop":{"x":305.7,"y":68.5},"noseRightAlarTop":{"x":326.5,"y":71.6},)"
            R"("noseLeftAlarOutTip":{"x":300.7,"y":74.8},"noseRightAlarOutTip":{"x":327.9,"y":78.6},)"
            R"("upperLipTop":{"x":313.7,"y":87.4},"upperLipBottom":{"x":312.9,"y":94.3},)"
            R"("underLipTop":{"x":310.7,"y":99.3},"underLipBottom":{"x":309.3,"y":108.9}},)"
            R"("faceAttributes":{"gender":"male","age":34.0,)"
            R"("emotion":{"anger":0.0,"contempt":0.0,"disgust":0.0,"fear":0.001,)"
            R"("happiness":0.0,"neutral" : 0.886,"sadness" : 0.0,"surprise" : 0.112} }}])"
        };
    }  // namespace samples
}  // namespace tmcppc::face_detection
