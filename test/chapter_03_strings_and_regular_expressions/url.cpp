#include "chapter_03_strings_and_regular_expressions/url.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <fmt/ostream.h>
#include <sstream>  // ostringstream

using namespace tmcppc::network;


TEST(url, DISABLED_constructor_empty_string) { EXPECT_THROW(url{ "" }, invalid_url_error); }
TEST(url, DISABLED_constructor_invalid_url) { EXPECT_THROW(url{ "This is not a valid URL!" }, invalid_url_error); }
TEST(url, DISABLED_valid_url) {
    url url{ "http://user:pass@example.com:992/animal/bird?species=seagull#wings" };
    EXPECT_EQ(url.get_protocol(), "http");
    EXPECT_EQ(*url.get_login(), "user:pass");
    EXPECT_EQ(url.get_domain(), "example.com");
    EXPECT_EQ(*url.get_port(), 992);
    EXPECT_EQ(*url.get_path(), "animal/bird");
    EXPECT_EQ(*url.get_query(), "species=seagull");
    EXPECT_EQ(*url.get_fragment(), "wings");
}

TEST(url, DISABLED_fmt_print) {
    std::ostringstream oss{};
    url url{ "http://user:pass@example.com:992/animal/bird?species=seagull#wings" };
    fmt::print(oss, "{}\n", url);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "[\n"
        "\tProtocol: http\n"
        "\tLogin: user:pass\n"
        "\tDomain: example.com\n"
        "\tPort: 992\n"
        "\tPath: animal/bird\n"
        "\tQuery: species=seagull\n"
        "\tFragment: wings\n"
        "]\n"
    ));
}
TEST(url, DISABLED_operator_insertion) {
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
