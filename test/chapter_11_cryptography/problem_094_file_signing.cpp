#include "chapter_11_cryptography/problem_094_file_signing.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_94_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_94_main(oss);
    EXPECT_THAT(oss.str(), ::testing::ContainsRegex(
        "Generating private and public key files\n"
        "\tPrivate key file: '.*private_key.txt'\n"
        "\tPublic key file: '.*public_key.txt'\n"
        "Signing file with private key\n"
        "\tInput file: '.*res/fonts/calibri.ttf'\n"
        "\tSignature file: '.*signature.txt'\n"
        "Verifying file with public key\n"
        "\tOK\n"
    ));
}
