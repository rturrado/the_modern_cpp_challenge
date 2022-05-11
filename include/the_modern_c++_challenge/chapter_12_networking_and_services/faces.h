#pragma once

#include "rtc/pretty_print.h"

#include <fmt/ostream.h>
#include <ostream>
#include <vector>


namespace tmcppc::face_detection {
    struct Error {
        std::string code{};
        std::string message{};

        void print(std::ostream& os) const {
            fmt::print(os, "(code: {}, message: '{}')", code, message);
        }
        void println(std::ostream& os, const indentation& indentation = {}) const {
            print(os, indentation);
            fmt::print(os, "\n");
        }
    };
    inline std::ostream& operator<<(std::ostream& os, const Error& error) {
        error.print(os);
        return os;
    }


    struct ErrorResponse {
        Error error{};

        void print(std::ostream& os, const indentation& indentation = {}) const {
            fmt::print(os, "{}Error: ", indentation);
            error.print(os);
        }
        void println(std::ostream& os, const indentation& indentation = {}) const {
            print(os, indentation);
            fmt::print(os, "\n");
        }
    };
    inline std::ostream& operator<<(std::ostream& os, const ErrorResponse& error_response) {
        error_response.print(os);
        return os;
    }


    struct Point {
        int x{};
        int y{};

        auto operator<=>(const Point& other) const = default;

        void print(std::ostream& os) const {
            fmt::print(os, "(x: {}, y: {})", x, y);
        }
        void println(std::ostream& os, const indentation& indentation = {}) const {
            print(os, indentation);
            fmt::print(os, "\n");
        }
    };
    inline std::ostream& operator<<(std::ostream& os, const Point& point) {
        point.print(os);
        return os;
    }

    
    struct Rectangle {
        int top{};
        int left{};
        int width{};
        int height{};

        auto operator<=>(const Rectangle& other) const = default;

        void print(std::ostream& os) const {
            fmt::print(os, "(top: {}, left: {}, width: {}, height: {})", top, left, width, height);
        }
        void println(std::ostream& os, const indentation& indentation = {}) const {
            print(os, indentation);
            fmt::print(os, "\n");
        }
    };
    inline std::ostream& operator<<(std::ostream& os, const Rectangle& rectangle) {
        rectangle.print(os);
        return os;
    }


    struct FaceLandmarks {
        Point pupilLeft{};
        Point pupilRight{};
        Point noseTip{};
        Point mouthLeft{};
        Point mouthRight{};
        Point eyebrowLeftOuter{};
        Point eyebrowLeftInner{};
        Point eyeLeftOuter{};
        Point eyeLeftTop{};
        Point eyeLeftBottom{};
        Point eyeLeftInner{};
        Point eyebrowRightInner{};
        Point eyebrowRightOuter{};
        Point eyeRightInner{};
        Point eyeRightTop{};
        Point eyeRightBottom{};
        Point eyeRightOuter{};
        Point noseRootLeft{};
        Point noseRootRight{};
        Point noseLeftAlarTop{};
        Point noseRightAlarTop{};
        Point noseLeftAlarOutTip{};
        Point noseRightAlarOutTip{};
        Point upperLipTop{};
        Point upperLipBottom{};
        Point underLipTop{};
        Point underLipBottom{};

        auto operator<=>(const FaceLandmarks& other) const = default;

        void print(std::ostream& os, const indentation& indentation = {}) const {
            fmt::print(os, "{}{}:\n", indentation, "Face landmarks");
            fmt::print(os, "{}{}: ", indentation + 1, "pupilLeft");
            pupilLeft.println(os);
            fmt::print(os, "{}{}: ", indentation + 1, "pupilRight");
            pupilRight.println(os);
            fmt::print(os, "{}{}: ", indentation + 1, "noseTip");
            noseTip.println(os);
            fmt::print(os, "{}{}: ", indentation + 1, "mouthLeft");
            mouthLeft.println(os);
            fmt::print(os, "{}{}: ", indentation + 1, "mouthRight");
            mouthRight.println(os);
            fmt::print(os, "{}{}: ", indentation + 1, "eyebrowLeftOuter");
            eyebrowLeftOuter.println(os);
            fmt::print(os, "{}{}: ", indentation + 1, "eyebrowLeftInner");
            eyebrowLeftInner.println(os);
            fmt::print(os, "{}{}: ", indentation + 1, "eyeLeftOuter");
            eyeLeftOuter.println(os);
            fmt::print(os, "{}{}: ", indentation + 1, "eyeLeftTop");
            eyeLeftTop.println(os);
            fmt::print(os, "{}{}: ", indentation + 1, "eyeLeftBottom");
            eyeLeftBottom.println(os);
            fmt::print(os, "{}{}: ", indentation + 1, "eyeLeftInner");
            eyeLeftInner.println(os);
            fmt::print(os, "{}{}: ", indentation + 1, "eyebrowRightInner");
            eyebrowRightInner.println(os);
            fmt::print(os, "{}{}: ", indentation + 1, "eyebrowRightOuter");
            eyebrowRightOuter.println(os);
            fmt::print(os, "{}{}: ", indentation + 1, "eyeRightInner");
            eyeRightInner.println(os);
            fmt::print(os, "{}{}: ", indentation + 1, "eyeRightTop");
            eyeRightTop.println(os);
            fmt::print(os, "{}{}: ", indentation + 1, "eyeRightBottom");
            eyeRightBottom.println(os);
            fmt::print(os, "{}{}: ", indentation + 1, "eyeRightOuter");
            eyeRightOuter.println(os);
            fmt::print(os, "{}{}: ", indentation + 1, "noseRootLeft");
            noseRootLeft.println(os);
            fmt::print(os, "{}{}: ", indentation + 1, "noseRootRight");
            noseRootRight.println(os);
            fmt::print(os, "{}{}: ", indentation + 1, "noseLeftAlarTop");
            noseLeftAlarTop.println(os);
            fmt::print(os, "{}{}: ", indentation + 1, "noseRightAlarTop");
            noseRightAlarTop.println(os);
            fmt::print(os, "{}{}: ", indentation + 1, "noseLeftAlarOutTip");
            noseLeftAlarOutTip.println(os);
            fmt::print(os, "{}{}: ", indentation + 1, "noseRightAlarOutTip");
            noseRightAlarOutTip.println(os);
            fmt::print(os, "{}{}: ", indentation + 1, "upperLipTop");
            upperLipTop.println(os);
            fmt::print(os, "{}{}: ", indentation + 1, "upperLipBottom");
            upperLipBottom.println(os);
            fmt::print(os, "{}{}: ", indentation + 1, "underLipTop");
            underLipTop.println(os);
            fmt::print(os, "{}{}: ", indentation + 1, "underLipBottom");
            underLipBottom.print(os);
        }
        void println(std::ostream& os, const indentation& indentation = {}) const {
            print(os, indentation);
            fmt::print(os, "\n");
        }
    };
    inline std::ostream& operator<<(std::ostream& os, const FaceLandmarks& face_landmarks) {
        face_landmarks.print(os);
        return os;
    }


    struct Emotion {
        double anger{};
        double contempt{};
        double disgust{};
        double fear{};
        double happiness{};
        double neutral{};
        double sadness{};
        double surprise{};

        auto operator<=>(const Emotion& other) const = default;

        void print(std::ostream& os, const indentation& indentation = {}) const {
            fmt::print(os, "{}{}:\n", indentation, "Emotion");
            fmt::print(os, "{}{}: {:.3f}\n", indentation + 1, "anger", anger);
            fmt::print(os, "{}{}: {:.3f}\n", indentation + 1, "contempt", contempt);
            fmt::print(os, "{}{}: {:.3f}\n", indentation + 1, "disgust", disgust);
            fmt::print(os, "{}{}: {:.3f}\n", indentation + 1, "fear", fear);
            fmt::print(os, "{}{}: {:.3f}\n", indentation + 1, "happiness", happiness);
            fmt::print(os, "{}{}: {:.3f}\n", indentation + 1, "neutral", neutral);
            fmt::print(os, "{}{}: {:.3f}\n", indentation + 1, "sadness", sadness);
            fmt::print(os, "{}{}: {:.3f}", indentation + 1, "surprise", surprise);
        }
    };
    inline std::ostream& operator<<(std::ostream& os, const Emotion& emotion) {
        emotion.print(os);
        return os;
    }


    struct FaceAttributes {
        std::string gender{};
        double age{};
        Emotion emotion{};

        auto operator<=>(const FaceAttributes& other) const = default;

        void print(std::ostream& os, const indentation& indentation = {}) const {
            fmt::print(os, "{}{}:\n", indentation, "Face attributes");
            fmt::print(os, "{}{}: {}\n", indentation + 1, "gender", gender);
            fmt::print(os, "{}{}: {:.1f}\n", indentation + 1, "age", age);
            emotion.print(os, indentation + 1);
        }
        void println(std::ostream& os, const indentation& indentation = {}) const {
            print(os, indentation);
            fmt::print(os, "\n");
        }
    };
    inline std::ostream& operator<<(std::ostream& os, const FaceAttributes& face_attributes) {
        face_attributes.print(os);
        return os;
    }


    struct Face {
        std::string id{};
        Rectangle rectangle{};
        FaceLandmarks landmarks{};
        FaceAttributes attributes{};

        auto operator<=>(const Face& other) const = default;

        void print(std::ostream& os, const indentation& indentation = {}) const {
            fmt::print(os, "{}{}:\n", indentation, "Face");
            fmt::print(os, "{}{}: {}\n", indentation + 1, "id", id);
            fmt::print(os, "{}{}: ", indentation + 1, "rectangle");
            rectangle.println(os);
            landmarks.println(os, indentation + 1);
            attributes.print(os, indentation + 1);
        }
        void println(std::ostream& os, const indentation& indentation = {}) const {
            print(os, indentation);
            fmt::print(os, "\n");
        }
    };
    inline std::ostream& operator<<(std::ostream& os, const Face& face) {
        face.print(os);
        return os;
    }


    struct FacesResponse {
        std::vector<Face> faces{};

        auto operator<=>(const FacesResponse& other) const = default;

        void print(std::ostream& os, const indentation& indentation = {}) const {
            fmt::print(os, "{}{}:\n", indentation, "Faces");
            for (auto&& face : faces) {
                face.println(os, indentation + 1);
            }
        }
    };
    inline std::ostream& operator<<(std::ostream& os, const FacesResponse& faces_response) {
        faces_response.print(os);
        return os;
    }

}  // namespace tmcppc::face_detection
