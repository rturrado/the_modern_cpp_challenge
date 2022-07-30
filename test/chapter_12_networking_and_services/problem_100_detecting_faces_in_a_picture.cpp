#include "chapter_12_networking_and_services/face_detection.h"
#include "chapter_12_networking_and_services/faces.h"
#include "chapter_12_networking_and_services/problem_100_detecting_faces_in_a_picture.h"
#include "env.h"
#include "face_detection_mock.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <filesystem>
#include <sstream>  // ostringstream
#include <variant>

using namespace tmcppc::face_detection;


TEST(test_face_detection, output) {
    provider_mock provider{};
    EXPECT_CALL(provider, detect(tmcppc::env::get_instance().get_resource_folder_path() / "faces.jpg"))
        .WillOnce(::testing::Return(provider_response{ 200, samples::faces_response_text }));

    std::ostringstream oss{};
    tmcppc::problem_100::test_face_detection(oss, provider);

    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "    Faces:\n"
        "        Face:\n"
        "            id: 473bc81f-6c04-498d-8581-0d22184b1637\n"
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
        "            id: a4834808-6727-4004-8e7a-b16d5f857694\n"
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
