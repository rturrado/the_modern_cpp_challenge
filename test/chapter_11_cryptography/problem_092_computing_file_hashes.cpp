#include "chapter_11_cryptography/problem_092_computing_file_hashes.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_92_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_92_main(oss);
    EXPECT_THAT(oss.str(), ::testing::ContainsRegex(
        "Calculating SHA1, SHA256 and MD5 for file '.*res/fonts/calibri.ttf'\n"
        "\tSHA1: '649A1ED83F061C390FA87238303393C082360181'\n"
        "\tSHA256: '198E8DAC512206F27C9BDBFEB3D5B3E55A33DE9DCF58D801823EF8C5EF5A76DC'\n"
        "\tMD5: '3DEA6DA513097358F7FBB4408AACB736'\n"
    ));
}
