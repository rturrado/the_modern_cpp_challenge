#pragma once

#include "faces.h"

#include "nlohmann/json.hpp"

#include <vector>


namespace tmcppc::face_detection {
    // error
    inline void to_json(nlohmann::json& j, const error& error) {
        j = nlohmann::json{ {"code", error.code}, {"message", error.message} };
    }
    inline void from_json(const nlohmann::json& j, error& error) {
        j.at("code").get_to(error.code);
        j.at("message").get_to(error.message);
    }

    // error_response
    inline void to_json(nlohmann::json& j, const error_response& error_response) {
        j = nlohmann::json{ {"error", error_response.error} };
    }
    inline void from_json(const nlohmann::json& j, error_response& error_response) {
        j.at("error").get_to(error_response.error);
    }

    // point
    inline void to_json(nlohmann::json& j, const point& point) {
        j = nlohmann::json{ {"x", point.x}, {"y", point.y} };
    }
    inline void from_json(const nlohmann::json& j, point& point) {
        j.at("x").get_to(point.x);
        j.at("y").get_to(point.y);
    }

    // rectangle
    inline void to_json(nlohmann::json& j, const rectangle& rectangle) {
        j = nlohmann::json{
            { "top", rectangle.top },
            { "left", rectangle.left },
            { "width", rectangle.width },
            { "height", rectangle.height }
        };
    }
    inline void from_json(const nlohmann::json& j, rectangle& rectangle) {
        j.at("top").get_to(rectangle.top);
        j.at("left").get_to(rectangle.left);
        j.at("width").get_to(rectangle.width);
        j.at("height").get_to(rectangle.height);
    }

    // face_landmarks
    inline void to_json(nlohmann::json& j, const face_landmarks& face_landmarks) {
        j = nlohmann::json{
            { "pupilLeft", face_landmarks.pupilLeft },
            { "pupilRight", face_landmarks.pupilRight },
            { "noseTip", face_landmarks.noseTip },
            { "mouthLeft", face_landmarks.mouthLeft },
            { "mouthRight", face_landmarks.mouthRight },
            { "eyebrowLeftOuter", face_landmarks.eyebrowLeftOuter },
            { "eyebrowLeftInner", face_landmarks.eyebrowLeftInner },
            { "eyeLeftOuter", face_landmarks.eyeLeftOuter },
            { "eyeLeftTop", face_landmarks.eyeLeftTop },
            { "eyeLeftBottom", face_landmarks.eyeLeftBottom },
            { "eyeLeftInner", face_landmarks.eyeLeftInner },
            { "eyebrowRightInner", face_landmarks.eyebrowRightInner },
            { "eyebrowRightOuter", face_landmarks.eyebrowRightOuter },
            { "eyeRightInner", face_landmarks.eyeRightInner },
            { "eyeRightTop", face_landmarks.eyeRightTop },
            { "eyeRightBottom", face_landmarks.eyeRightBottom },
            { "eyeRightOuter", face_landmarks.eyeRightOuter },
            { "noseRootLeft", face_landmarks.noseRootLeft },
            { "noseRootRight", face_landmarks.noseRootRight },
            { "noseLeftAlarTop", face_landmarks.noseLeftAlarTop },
            { "noseRightAlarTop", face_landmarks.noseRightAlarTop },
            { "noseLeftAlarOutTip", face_landmarks.noseLeftAlarOutTip },
            { "noseRightAlarOutTip", face_landmarks.noseRightAlarOutTip },
            { "upperLipTop", face_landmarks.upperLipTop },
            { "upperLipBottom", face_landmarks.upperLipBottom },
            { "underLipTop", face_landmarks.underLipTop },
            { "underLipBottom", face_landmarks.underLipBottom }
        };
    }
    inline void from_json(const nlohmann::json& j, face_landmarks& face_landmarks) {
        j.at("pupilLeft").get_to(face_landmarks.pupilLeft);
        j.at("pupilRight").get_to(face_landmarks.pupilRight);
        j.at("noseTip").get_to(face_landmarks.noseTip);
        j.at("mouthLeft").get_to(face_landmarks.mouthLeft);
        j.at("mouthRight").get_to(face_landmarks.mouthRight);
        j.at("eyebrowLeftOuter").get_to(face_landmarks.eyebrowLeftOuter);
        j.at("eyebrowLeftInner").get_to(face_landmarks.eyebrowLeftInner);
        j.at("eyeLeftOuter").get_to(face_landmarks.eyeLeftOuter);
        j.at("eyeLeftTop").get_to(face_landmarks.eyeLeftTop);
        j.at("eyeLeftBottom").get_to(face_landmarks.eyeLeftBottom);
        j.at("eyeLeftInner").get_to(face_landmarks.eyeLeftInner);
        j.at("eyebrowRightInner").get_to(face_landmarks.eyebrowRightInner);
        j.at("eyebrowRightOuter").get_to(face_landmarks.eyebrowRightOuter);
        j.at("eyeRightInner").get_to(face_landmarks.eyeRightInner);
        j.at("eyeRightTop").get_to(face_landmarks.eyeRightTop);
        j.at("eyeRightBottom").get_to(face_landmarks.eyeRightBottom);
        j.at("eyeRightOuter").get_to(face_landmarks.eyeRightOuter);
        j.at("noseRootLeft").get_to(face_landmarks.noseRootLeft);
        j.at("noseRootRight").get_to(face_landmarks.noseRootRight);
        j.at("noseLeftAlarTop").get_to(face_landmarks.noseLeftAlarTop);
        j.at("noseRightAlarTop").get_to(face_landmarks.noseRightAlarTop);
        j.at("noseLeftAlarOutTip").get_to(face_landmarks.noseLeftAlarOutTip);
        j.at("noseRightAlarOutTip").get_to(face_landmarks.noseRightAlarOutTip);
        j.at("upperLipTop").get_to(face_landmarks.upperLipTop);
        j.at("upperLipBottom").get_to(face_landmarks.upperLipBottom);
        j.at("underLipTop").get_to(face_landmarks.underLipTop);
        j.at("underLipBottom").get_to(face_landmarks.underLipBottom);
    }

    // emotion
    inline void to_json(nlohmann::json& j, const emotion& emotion) {
        j = nlohmann::json{
            { "anger", emotion.anger },
            { "contempt", emotion.contempt },
            { "disgust", emotion.disgust },
            { "fear", emotion.fear },
            { "happiness", emotion.happiness },
            { "neutral", emotion.neutral },
            { "sadness", emotion.sadness },
            { "surprise", emotion.surprise }
        };
    }
    inline void from_json(const nlohmann::json& j, emotion& emotion) {
        j.at("anger").get_to(emotion.anger);
        j.at("contempt").get_to(emotion.contempt);
        j.at("disgust").get_to(emotion.disgust);
        j.at("fear").get_to(emotion.fear);
        j.at("happiness").get_to(emotion.happiness);
        j.at("neutral").get_to(emotion.neutral);
        j.at("sadness").get_to(emotion.sadness);
        j.at("surprise").get_to(emotion.surprise);
    }

    // face_attributes
    inline void to_json(nlohmann::json& j, const face_attributes& face_attributes) {
        j = nlohmann::json{
            { "gender", face_attributes.gender },
            { "age", face_attributes.age },
            { "emotion", face_attributes.emotion }
        };
    }
    inline void from_json(const nlohmann::json& j, face_attributes& face_attributes) {
        j.at("gender").get_to(face_attributes.gender);
        j.at("age").get_to(face_attributes.age);
        j.at("emotion").get_to(face_attributes.emotion);
    }

    // face
    inline void to_json(nlohmann::json& j, const face& face) {
        j = nlohmann::json{
            { "faceId", face.id },
            { "faceRectangle", face.rectangle },
            { "faceLandmarks", face.landmarks },
            { "faceAttributes", face.attributes }
        };
    }
    inline void from_json(const nlohmann::json& j, face& face) {
        j.at("faceId").get_to(face.id);
        j.at("faceRectangle").get_to(face.rectangle);
        j.at("faceLandmarks").get_to(face.landmarks);
        j.at("faceAttributes").get_to(face.attributes);
    }

    // faces_response
    inline void to_json(nlohmann::json& j, const faces_response& faces_response) {
        j = faces_response.faces;
    }
    inline void from_json(const nlohmann::json& j, faces_response& faces_response) {
        faces_response.faces = j.get<std::vector<face>>();
    }
}  // namespace tmcppc::face_detection
