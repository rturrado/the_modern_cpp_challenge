#include "chapter_12_networking_and_services/face_detection.h"
#include "chapter_12_networking_and_services/faces.h"
#include "chapter_12_networking_and_services/problem_100_detecting_faces_in_a_picture.h"
#include "env.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <filesystem>
#include <iosfwd>
#include <sstream>  // ostringstream
#include <variant>

using namespace tmcppc::face_detection;
namespace fs = std::filesystem;


namespace tmcppc::face_detection {
    class detector_mock : public detector_adaptor {
    public:
        MOCK_METHOD((std::variant<faces_response, error_response>), detect,
            (const fs::path& path), (const, override));
    };
}  // namespace tmcppc::face_detection


TEST(test_face_detection, DISABLED_output) {
    detector_mock detector{};
    EXPECT_CALL(detector, detect(tmcppc::env::get_instance().get_resource_folder_path() / "faces.jpg"))
        .WillOnce(::testing::Return(
            faces_response{{
                face{
                    "01234567-89ab-cdef-0123-456789abcdef",
                    rectangle{118, 615, 100, 100},
                    face_landmarks{
                        point{645, 146},
                        point{685, 144},
                        point{662, 166},
                        point{646, 194},
                        point{685, 194},
                        point{628, 135},
                        point{658, 137},
                        point{638, 147},
                        point{643, 144},
                        point{644, 149},
                        point{651, 146},
                        point{671, 136},
                        point{702, 137},
                        point{679, 145},
                        point{686, 142},
                        point{686, 147},
                        point{692, 146},
                        point{656, 146},
                        point{671, 146},
                        point{653, 160},
                        point{674, 160},
                        point{649, 169},
                        point{678, 169},
                        point{663, 186},
                        point{662, 191},
                        point{663, 198},
                        point{663, 206}
                    },
                    face_attributes{
                        "male",
                        31.0,
                        emotion{0.031, 0.001, 0.000, 0.000, 0.001, 0.940, 0.000, 0.027}
                    }
                },
                face{
                    "12345678-9abc-def0-1234-56789abcdef0",
                    rectangle{29, 268, 94, 94},
                    face_landmarks{
                        point{298, 52},
                        point{337, 57},
                        point{314, 75},
                        point{293, 97},
                        point{329, 101},
                        point{282, 39},
                        point{309, 42},
                        point{290, 51},
                        point{297, 48},
                        point{296, 55},
                        point{305, 53},
                        point{327, 45},
                        point{356, 50},
                        point{330, 56},
                        point{338, 52},
                        point{337, 60},
                        point{345, 58},
                        point{310, 54},
                        point{324, 56},
                        point{305, 68},
                        point{326, 71},
                        point{300, 74},
                        point{327, 78},
                        point{313, 87},
                        point{312, 94},
                        point{310, 99},
                        point{309, 108},
                    },
                    face_attributes{
                        "male",
                        34.0,
                        emotion{0.000, 0.000, 0.000, 0.001, 0.000, 0.886, 0.000, 0.112}
                    }
                }
            }}
    ));

    std::ostringstream oss{};
    tmcppc::problem_100::test_face_detection(oss, &detector);

    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "    Faces:\n"
        "        Face:\n"
        "            id: 01234567-89ab-cdef-0123-456789abcdef\n"
        "            rectangle: (top: 118, left: 615, width: 100, height: 100)\n"
        "            Face landmarks:\n"
        "                pupilLeft: (x: 645, y: 146)\n"
        "                pupilRight: (x: 685, y: 144)\n"
        "                noseTip: (x: 662, y: 166)\n"
        "                mouthLeft: (x: 646, y: 194)\n"
        "                mouthRight: (x: 685, y: 194)\n"
        "                eyebrowLeftOuter: (x: 628, y: 135)\n"
        "                eyebrowLeftInner: (x: 658, y: 137)\n"
        "                eyeLeftOuter: (x: 638, y: 147)\n"
        "                eyeLeftTop: (x: 643, y: 144)\n"
        "                eyeLeftBottom: (x: 644, y: 149)\n"
        "                eyeLeftInner: (x: 651, y: 146)\n"
        "                eyebrowRightInner: (x: 671, y: 136)\n"
        "                eyebrowRightOuter: (x: 702, y: 137)\n"
        "                eyeRightInner: (x: 679, y: 145)\n"
        "                eyeRightTop: (x: 686, y: 142)\n"
        "                eyeRightBottom: (x: 686, y: 147)\n"
        "                eyeRightOuter: (x: 692, y: 146)\n"
        "                noseRootLeft: (x: 656, y: 146)\n"
        "                noseRootRight: (x: 671, y: 146)\n"
        "                noseLeftAlarTop: (x: 653, y: 160)\n"
        "                noseRightAlarTop: (x: 674, y: 160)\n"
        "                noseLeftAlarOutTip: (x: 649, y: 169)\n"
        "                noseRightAlarOutTip: (x: 678, y: 169)\n"
        "                upperLipTop: (x: 663, y: 186)\n"
        "                upperLipBottom: (x: 662, y: 191)\n"
        "                underLipTop: (x: 663, y: 198)\n"
        "                underLipBottom: (x: 663, y: 206)\n"
        "            Face attributes:\n"
        "                gender: male\n"
        "                age: 31.0\n"
        "                Emotion:\n"
        "                    anger: 0.031\n"
        "                    contempt: 0.001\n"
        "                    disgust: 0.000\n"
        "                    fear: 0.000\n"
        "                    happiness: 0.001\n"
        "                    neutral: 0.940\n"
        "                    sadness: 0.000\n"
        "                    surprise: 0.027\n"
        "        Face:\n"
        "            id: 12345678-9abc-def0-1234-56789abcdef0\n"
        "            rectangle: (top: 29, left: 268, width: 94, height: 94)\n"
        "            Face landmarks:\n"
        "                pupilLeft: (x: 298, y: 52)\n"
        "                pupilRight: (x: 337, y: 57)\n"
        "                noseTip: (x: 314, y: 75)\n"
        "                mouthLeft: (x: 293, y: 97)\n"
        "                mouthRight: (x: 329, y: 101)\n"
        "                eyebrowLeftOuter: (x: 282, y: 39)\n"
        "                eyebrowLeftInner: (x: 309, y: 42)\n"
        "                eyeLeftOuter: (x: 290, y: 51)\n"
        "                eyeLeftTop: (x: 297, y: 48)\n"
        "                eyeLeftBottom: (x: 296, y: 55)\n"
        "                eyeLeftInner: (x: 305, y: 53)\n"
        "                eyebrowRightInner: (x: 327, y: 45)\n"
        "                eyebrowRightOuter: (x: 356, y: 50)\n"
        "                eyeRightInner: (x: 330, y: 56)\n"
        "                eyeRightTop: (x: 338, y: 52)\n"
        "                eyeRightBottom: (x: 337, y: 60)\n"
        "                eyeRightOuter: (x: 345, y: 58)\n"
        "                noseRootLeft: (x: 310, y: 54)\n"
        "                noseRootRight: (x: 324, y: 56)\n"
        "                noseLeftAlarTop: (x: 305, y: 68)\n"
        "                noseRightAlarTop: (x: 326, y: 71)\n"
        "                noseLeftAlarOutTip: (x: 300, y: 74)\n"
        "                noseRightAlarOutTip: (x: 327, y: 78)\n"
        "                upperLipTop: (x: 313, y: 87)\n"
        "                upperLipBottom: (x: 312, y: 94)\n"
        "                underLipTop: (x: 310, y: 99)\n"
        "                underLipBottom: (x: 309, y: 108)\n"
        "            Face attributes:\n"
        "                gender: male\n"
        "                age: 34.0\n"
        "                Emotion:\n"
        "                    anger: 0.000\n"
        "                    contempt: 0.000\n"
        "                    disgust: 0.000\n"
        "                    fear: 0.001\n"
        "                    happiness: 0.000\n"
        "                    neutral: 0.886\n"
        "                    sadness: 0.000\n"
        "                    surprise: 0.112\n"
    ));
}
