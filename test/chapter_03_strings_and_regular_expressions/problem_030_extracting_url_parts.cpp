#include "chapter_03_strings_and_regular_expressions/problem_030_extracting_url_parts.h"
#include "chapter_03_strings_and_regular_expressions/url.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_30_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_30_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "Parsing URL \"http://user:pass@example.com:992/animal/bird?species=seagull#wings\":\n"
        "[\n"
        "\tProtocol: http\n"
        "\tLogin: user:pass\n"
        "\tDomain: example.com\n"
        "\tPort: 992\n"
        "\tPath: animal/bird\n"
        "\tQuery: species=seagull\n"
        "\tFragment: wings\n"
        "]\n"
        "\n"
        "Parsing URL \"http://example.com/animal/bird#wings\":\n"
        "[\n"
        "\tProtocol: http\n"
        "\tDomain: example.com\n"
        "\tPath: animal/bird\n"
        "\tFragment: wings\n"
        "]\n"
        "\n"
        "Error: invalid URL: \"This is not a valid URL!\"\n\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::Not(::testing::EndsWith("\n\n\n")));
}
