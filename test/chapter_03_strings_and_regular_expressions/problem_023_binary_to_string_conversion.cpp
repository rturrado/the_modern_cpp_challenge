#include "chapter_03_strings_and_regular_expressions/problem_023_binary_to_string_conversion.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <array>
#include <list>
#include <numeric>  // iota
#include <string>
#include <vector>

using namespace tmcppc::problem_23;


TEST(to_hex_string, empty_container) {
    EXPECT_EQ(to_hex_string(std::list<uint8_t>{}), "");
}

TEST(to_hex_string, array_010203040506) {
    std::array<uint8_t, 6> a{};
    std::iota(std::begin(a), std::end(a), 1);
    EXPECT_EQ(to_hex_string(a), "010203040506");
}

TEST(to_hex_string, vector_BAADF00D) {
    std::vector<uint8_t> v{ 0xBA, 0xAD, 0xf0, 0x0d };
    EXPECT_EQ(to_hex_string(v), "baadf00d");
}

TEST(problem_23_main, output) {
    std::ostringstream oss{};
    problem_23_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "Converting vector [0xba, 0xad, 0xf0, 0xd] to string \"baadf00d\"\n"
        "Converting array [0x1, 0x2, 0x3, 0x4, 0x5, 0x6] to string \"010203040506\"\n\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::Not(::testing::EndsWith("\n\n\n")));
}
