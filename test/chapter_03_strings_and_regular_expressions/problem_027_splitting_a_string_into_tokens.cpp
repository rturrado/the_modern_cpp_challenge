#include "chapter_03_strings_and_regular_expressions/problem_027_splitting_a_string_into_tokens.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <string>
#include <vector>

using namespace tmcppc::problem_27;


TEST(split, empty_string) {
    std::vector<std::string> result{};
    EXPECT_EQ(split("", " "), result);
}
TEST(split, delimiter_not_found) {
    EXPECT_THAT(split("a;b;c", "-"), ::testing::ElementsAre("a;b;c"));
}
TEST(split, delimiter_found) {
    EXPECT_THAT(split("a;b;c", ";"), ::testing::ElementsAre("a", "b", "c"));
}
TEST(split, many_delimiters) {
    EXPECT_THAT(split("a;b\tc", ";\t"), ::testing::ElementsAre("a", "b", "c"));
}

TEST(problem_27_main, output) {
    std::ostringstream oss{};
    problem_27_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "Splitting string \"this,is.a sample!!\" using any delimiter of \",.! \" into: [this, is, a, sample]\n"
        "Splitting string \"this,is.a sample!!\" using any delimiter of \"#\" into: [this,is.a sample!!]\n\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::Not(::testing::EndsWith("\n\n\n")));
}
