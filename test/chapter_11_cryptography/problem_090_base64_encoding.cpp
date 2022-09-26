#include "chapter_11_cryptography/problem_090_base64_encoding.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <sstream>  // ostringstream


TEST(problem_90_main, output) {
    std::ostringstream oss{};
    problem_90_main(oss);
    EXPECT_THAT(oss.str(), ::testing::ContainsRegex(
        "Encoding and decoding file '.*res/fonts/calibri.ttf'\n"
        "\tOK\n"
        "Encoding and decoding text ''\n"
        "\tOK\n"
        "Encoding and decoding text ''\n"
        "\tOK\n"
        "Encoding and decoding text 'M'\n"
        "\tOK\n"
        "Encoding and decoding text 'M'\n"
        "\tOK\n"
        "Encoding and decoding text 'Ma'\n"
        "\tOK\n"
        "Encoding and decoding text 'Ma'\n"
        "\tOK\n"
        "Encoding and decoding text 'Man'\n"
        "\tOK\n"
        "Encoding and decoding text 'Man'\n"
        "\tOK\n"
        "Encoding and decoding text 'Many'\n"
        "\tOK\n"
        "Encoding and decoding text 'Many'\n"
        "\tOK\n"
        "Encoding and decoding text 'Many '\n"
        "\tOK\n"
        "Encoding and decoding text 'Many '\n"
        "\tOK\n"
        "Encoding and decoding text 'Many h'\n"
        "\tOK\n"
        "Encoding and decoding text 'Many h'\n"
        "\tOK\n"
        "Encoding and decoding text 'Many hands make light work.'\n"
        "\tOK\n"
        "Encoding and decoding text 'Many hands make light work.'\n"
        "\tOK\n\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::Not(::testing::EndsWith("\n\n\n")));
}
