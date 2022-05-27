#pragma once

#include "rtc/pretty_print.h"

#include <fmt/ostream.h>
#include <ostream>
#include <sstream>  // ostringstream
#include <vector>


namespace tmcppc::face_detection {
    using namespace rtc::pretty_print;

    // error
    struct error {
        std::string code{};
        std::string message{};

        void print(std::ostream& os, const indentation& indentation = {}) const {
            fmt::print(os, "{}(code: {}, message: '{}')", indentation, code, message);
        }
        void println(std::ostream& os, const indentation& indentation = {}) const {
            print(os, indentation);
            fmt::print(os, "\n");
        }
    };
    inline std::ostream& operator<<(std::ostream& os, const error& error) {
        error.print(os);
        return os;
    }

    // error_response
    struct error_response {
        error error_{};

        void print(std::ostream& os, const indentation& indentation = {}) const {
            fmt::print(os, "{}Error: ", indentation);
            error_.print(os);
        }
        void println(std::ostream& os, const indentation& indentation = {}) const {
            print(os, indentation);
            fmt::print(os, "\n");
        }
    };
    inline std::ostream& operator<<(std::ostream& os, const error_response& error_response) {
        error_response.print(os);
        return os;
    }

    // point
    struct point {
        int x{};
        int y{};

        auto operator<=>(const point& other) const = default;

        void print(std::ostream& os, const indentation& indentation = {}) const {
            fmt::print(os, "{}(x: {}, y: {})", indentation, x, y);
        }
        void println(std::ostream& os, const indentation& indentation = {}) const {
            print(os, indentation);
            fmt::print(os, "\n");
        }
    };
    inline std::ostream& operator<<(std::ostream& os, const point& point) {
        point.print(os);
        return os;
    }

    // rectangle
    struct rectangle {
        int top{};
        int left{};
        int width{};
        int height{};

        auto operator<=>(const rectangle& other) const = default;

        void print(std::ostream& os, const indentation& indentation = {}) const {
            fmt::print(os, "{}(top: {}, left: {}, width: {}, height: {})", indentation, top, left, width, height);
        }
        void println(std::ostream& os, const indentation& indentation = {}) const {
            print(os, indentation);
            fmt::print(os, "\n");
        }
    };
    inline std::ostream& operator<<(std::ostream& os, const rectangle& rectangle) {
        rectangle.print(os);
        return os;
    }

    // face_landmarks
    struct face_landmarks {
        point pupilLeft{};
        point pupilRight{};
        point noseTip{};
        point mouthLeft{};
        point mouthRight{};
        point eyebrowLeftOuter{};
        point eyebrowLeftInner{};
        point eyeLeftOuter{};
        point eyeLeftTop{};
        point eyeLeftBottom{};
        point eyeLeftInner{};
        point eyebrowRightInner{};
        point eyebrowRightOuter{};
        point eyeRightInner{};
        point eyeRightTop{};
        point eyeRightBottom{};
        point eyeRightOuter{};
        point noseRootLeft{};
        point noseRootRight{};
        point noseLeftAlarTop{};
        point noseRightAlarTop{};
        point noseLeftAlarOutTip{};
        point noseRightAlarOutTip{};
        point upperLipTop{};
        point upperLipBottom{};
        point underLipTop{};
        point underLipBottom{};

        auto operator<=>(const face_landmarks& other) const = default;

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
    inline std::ostream& operator<<(std::ostream& os, const face_landmarks& face_landmarks) {
        face_landmarks.print(os);
        return os;
    }

    // emotion
    struct emotion {
        double anger{};
        double contempt{};
        double disgust{};
        double fear{};
        double happiness{};
        double neutral{};
        double sadness{};
        double surprise{};

        auto operator<=>(const emotion& other) const = default;

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
    inline std::ostream& operator<<(std::ostream& os, const emotion& emotion) {
        emotion.print(os);
        return os;
    }

    // face_attributes
    struct face_attributes {
        std::string gender{};
        double age{};
        emotion emotion_{};

        auto operator<=>(const face_attributes& other) const = default;

        void print(std::ostream& os, const indentation& indentation = {}) const {
            fmt::print(os, "{}{}:\n", indentation, "Face attributes");
            fmt::print(os, "{}{}: {}\n", indentation + 1, "gender", gender);
            fmt::print(os, "{}{}: {:.1f}\n", indentation + 1, "age", age);
            emotion_.print(os, indentation + 1);
        }
        void println(std::ostream& os, const indentation& indentation = {}) const {
            print(os, indentation);
            fmt::print(os, "\n");
        }
    };
    inline std::ostream& operator<<(std::ostream& os, const face_attributes& face_attributes) {
        face_attributes.print(os);
        return os;
    }

    // face
    struct face {
        std::string id{};
        rectangle rectangle{};
        face_landmarks landmarks{};
        face_attributes attributes{};

        auto operator<=>(const face& other) const = default;

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
    inline std::ostream& operator<<(std::ostream& os, const face& face) {
        face.print(os);
        return os;
    }

    // faces_response
    struct faces_response {
        std::vector<face> faces{};

        auto operator<=>(const faces_response& other) const = default;

        void print(std::ostream& os, const indentation& indentation = {}) const {
            fmt::print(os, "{}{}:\n", indentation, "Faces");
            for (auto&& face : faces) {
                face.println(os, indentation + 1);
            }
        }
    };
    inline std::ostream& operator<<(std::ostream& os, const faces_response& faces_response) {
        faces_response.print(os);
        return os;
    }
}  // namespace tmcppc::face_detection


template <>
struct fmt::formatter<tmcppc::face_detection::error> {
    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const tmcppc::face_detection::error& error, FormatContext& ctx) const -> decltype(ctx.out()) {
        std::ostringstream oss{};
        error.print(oss);
        return fmt::format_to(ctx.out(), "{}", oss.str());
    }
};


template <>
struct fmt::formatter<tmcppc::face_detection::error_response> {
    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const tmcppc::face_detection::error_response& error_response, FormatContext& ctx) const -> decltype(ctx.out()) {
        std::ostringstream oss{};
        error_response.print(oss);
        return fmt::format_to(ctx.out(), "{}", oss.str());
    }
};


template <>
struct fmt::formatter<tmcppc::face_detection::point> {
    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const tmcppc::face_detection::point& point, FormatContext& ctx) const -> decltype(ctx.out()) {
        std::ostringstream oss{};
        point.print(oss);
        return fmt::format_to(ctx.out(), "{}", oss.str());
    }
};


template <>
struct fmt::formatter<tmcppc::face_detection::rectangle> {
    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const tmcppc::face_detection::rectangle& rectangle, FormatContext& ctx) const -> decltype(ctx.out()) {
        std::ostringstream oss{};
        rectangle.print(oss);
        return fmt::format_to(ctx.out(), "{}", oss.str());
    }
};


template <>
struct fmt::formatter<tmcppc::face_detection::face_landmarks> {
    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const tmcppc::face_detection::face_landmarks& face_landmarks, FormatContext& ctx) const -> decltype(ctx.out()) {
        std::ostringstream oss{};
        face_landmarks.print(oss);
        return fmt::format_to(ctx.out(), "{}", oss.str());
    }
};


template <>
struct fmt::formatter<tmcppc::face_detection::emotion> {
    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const tmcppc::face_detection::emotion& emotion, FormatContext& ctx) const -> decltype(ctx.out()) {
        std::ostringstream oss{};
        emotion.print(oss);
        return fmt::format_to(ctx.out(), "{}", oss.str());
    }
};


template <>
struct fmt::formatter<tmcppc::face_detection::face_attributes> {
    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const tmcppc::face_detection::face_attributes& face_attributes, FormatContext& ctx) const -> decltype(ctx.out()) {
        std::ostringstream oss{};
        face_attributes.print(oss);
        return fmt::format_to(ctx.out(), "{}", oss.str());
    }
};


template <>
struct fmt::formatter<tmcppc::face_detection::face> {
    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const tmcppc::face_detection::face& face, FormatContext& ctx) const -> decltype(ctx.out()) {
        std::ostringstream oss{};
        face.print(oss);
        return fmt::format_to(ctx.out(), "{}", oss.str());
    }
};


template <>
struct fmt::formatter<tmcppc::face_detection::faces_response> {
    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const tmcppc::face_detection::faces_response& faces_response, FormatContext& ctx) const -> decltype(ctx.out()) {
        std::ostringstream oss{};
        faces_response.print(oss);
        return fmt::format_to(ctx.out(), "{}", oss.str());
    }
};
