#pragma once

#include "../faces.h"

#include <nlohmann/json.hpp>
#include <vector>


namespace tmcppc::face_detection {
    // Error
    inline void to_json(nlohmann::json& j, const error& error) {
        j = nlohmann::json{ {"code", error.code}, {"message", error.message} };
    }
    inline void from_json(const nlohmann::json& j, error& error) {
        j.at("code").get_to(error.code);
        j.at("message").get_to(error.message);
    }

    // Error response
    inline void to_json(nlohmann::json& j, const error_response& error_response) {
        j = nlohmann::json{ {"error", error_response.error_} };
    }
    inline void from_json(const nlohmann::json& j, error_response& error_response) {
        j.at("error").get_to(error_response.error_);
    }

    // Point
    inline void to_json(nlohmann::json& j, const point& point) {
        j = nlohmann::json{ {"x", point.x}, {"y", point.y} };
    }
    inline void from_json(const nlohmann::json& j, point& point) {
        j.at("x").get_to(point.x);
        j.at("y").get_to(point.y);
    }

    // Rectangle
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

    // Face landmarks
    inline void to_json(nlohmann::json& j, const face_landmarks& face_landmarks) {
        j = nlohmann::json{
            { "pupilLeft", face_landmarks.pupil_left },
            { "pupilRight", face_landmarks.pupil_right },
            { "noseTip", face_landmarks.nose_tip },
            { "mouthLeft", face_landmarks.mouth_left },
            { "mouthRight", face_landmarks.mouth_right },
            { "eyebrowLeftOuter", face_landmarks.eyebrow_left_outer },
            { "eyebrowLeftInner", face_landmarks.eyebrow_left_inner },
            { "eyeLeftOuter", face_landmarks.eye_left_outer },
            { "eyeLeftTop", face_landmarks.eye_left_top },
            { "eyeLeftBottom", face_landmarks.eye_left_bottom },
            { "eyeLeftInner", face_landmarks.eye_left_inner },
            { "eyebrowRightInner", face_landmarks.eyebrow_right_inner },
            { "eyebrowRightOuter", face_landmarks.eyebrow_right_outer },
            { "eyeRightInner", face_landmarks.eye_right_inner },
            { "eyeRightTop", face_landmarks.eye_right_top },
            { "eyeRightBottom", face_landmarks.eye_right_bottom },
            { "eyeRightOuter", face_landmarks.eye_right_outer },
            { "noseRootLeft", face_landmarks.nose_root_left },
            { "noseRootRight", face_landmarks.nose_root_right },
            { "noseLeftAlarTop", face_landmarks.nose_left_alar_top },
            { "noseRightAlarTop", face_landmarks.nose_right_alar_top },
            { "noseLeftAlarOutTip", face_landmarks.nose_left_alar_out_tip },
            { "noseRightAlarOutTip", face_landmarks.nose_right_alar_out_tip },
            { "upperLipTop", face_landmarks.upper_lip_top },
            { "upperLipBottom", face_landmarks.upper_lip_bottom },
            { "underLipTop", face_landmarks.under_lip_top },
            { "underLipBottom", face_landmarks.under_lip_bottom }
        };
    }
    inline void from_json(const nlohmann::json& j, face_landmarks& face_landmarks) {
        j.at("pupilLeft").get_to(face_landmarks.pupil_left);
        j.at("pupilRight").get_to(face_landmarks.pupil_right);
        j.at("noseTip").get_to(face_landmarks.nose_tip);
        j.at("mouthLeft").get_to(face_landmarks.mouth_left);
        j.at("mouthRight").get_to(face_landmarks.mouth_right);
        j.at("eyebrowLeftOuter").get_to(face_landmarks.eyebrow_left_outer);
        j.at("eyebrowLeftInner").get_to(face_landmarks.eyebrow_left_inner);
        j.at("eyeLeftOuter").get_to(face_landmarks.eye_left_outer);
        j.at("eyeLeftTop").get_to(face_landmarks.eye_left_top);
        j.at("eyeLeftBottom").get_to(face_landmarks.eye_left_bottom);
        j.at("eyeLeftInner").get_to(face_landmarks.eye_left_inner);
        j.at("eyebrowRightInner").get_to(face_landmarks.eyebrow_right_inner);
        j.at("eyebrowRightOuter").get_to(face_landmarks.eyebrow_right_outer);
        j.at("eyeRightInner").get_to(face_landmarks.eye_right_inner);
        j.at("eyeRightTop").get_to(face_landmarks.eye_right_top);
        j.at("eyeRightBottom").get_to(face_landmarks.eye_right_bottom);
        j.at("eyeRightOuter").get_to(face_landmarks.eye_right_outer);
        j.at("noseRootLeft").get_to(face_landmarks.nose_root_left);
        j.at("noseRootRight").get_to(face_landmarks.nose_root_right);
        j.at("noseLeftAlarTop").get_to(face_landmarks.nose_left_alar_top);
        j.at("noseRightAlarTop").get_to(face_landmarks.nose_right_alar_top);
        j.at("noseLeftAlarOutTip").get_to(face_landmarks.nose_left_alar_out_tip);
        j.at("noseRightAlarOutTip").get_to(face_landmarks.nose_right_alar_out_tip);
        j.at("upperLipTop").get_to(face_landmarks.upper_lip_top);
        j.at("upperLipBottom").get_to(face_landmarks.upper_lip_bottom);
        j.at("underLipTop").get_to(face_landmarks.under_lip_top);
        j.at("underLipBottom").get_to(face_landmarks.under_lip_bottom);
    }

    // Emotion
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

    // Face attributes
    inline void to_json(nlohmann::json& j, const face_attributes& face_attributes) {
        j = nlohmann::json{
            { "gender", face_attributes.gender },
            { "age", face_attributes.age },
            { "emotion", face_attributes.emotion_ }
        };
    }
    inline void from_json(const nlohmann::json& j, face_attributes& face_attributes) {
        j.at("gender").get_to(face_attributes.gender);
        j.at("age").get_to(face_attributes.age);
        j.at("emotion").get_to(face_attributes.emotion_);
    }

    // Face
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

    // Faces response
    inline void to_json(nlohmann::json& j, const faces_response& faces_response) {
        j = faces_response.faces;
    }
    inline void from_json(const nlohmann::json& j, faces_response& faces_response) {
        faces_response.faces = j.get<std::vector<face>>();
    }
}  // namespace tmcppc::face_detection
