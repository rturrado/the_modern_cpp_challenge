#include "chapter_03_strings_and_regular_expressions/url.h"

#include <fmt/format.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <sstream>  // ostringstream

using namespace tmcppc::network;


TEST(url, constructor_empty_string) { EXPECT_THROW(url{ "" }, invalid_url_error); }
TEST(url, constructor_invalid_url) { EXPECT_THROW(url{ "This is not a valid URL!" }, invalid_url_error); }
TEST(url, valid_url) {
    url url{ "http://user:pass@example.com:992/animal/bird?species=seagull#wings" };
    EXPECT_EQ(url.protocol(), "http");
    EXPECT_EQ(*url.login(), "user:pass");
    EXPECT_EQ(url.domain(), "example.com");
    EXPECT_EQ(*url.port(), 992);
    EXPECT_EQ(*url.path(), "animal/bird");
    EXPECT_EQ(*url.query(), "species=seagull");
    EXPECT_EQ(*url.fragment(), "wings");
}

TEST(url, fmt_format) {
    url url{ "http://user:pass@example.com:992/animal/bird?species=seagull#wings" };
    EXPECT_EQ(fmt::format("{}\n", url),
        "[\n"
        "\tProtocol: http\n"
        "\tLogin: user:pass\n"
        "\tDomain: example.com\n"
        "\tPort: 992\n"
        "\tPath: animal/bird\n"
        "\tQuery: species=seagull\n"
        "\tFragment: wings\n"
        "]\n"
    );
}
TEST(url, operator_insertion) {
    std::ostringstream oss{};
    url u{ "http://user:pass@example.com:992/animal/bird?species=seagull#wings" };
    oss << u << "\n";
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "[\n"
        "\tProtocol: http\n"
        "\tLogin: user:pass\n"
        "\tDomain: example.com\n"
        "\tPort: 992\n"
        "\tPath: animal/bird\n"
        "\tQuery: species=seagull\n"
        "\tFragment: wings\n"
        "]"
    ));
}
