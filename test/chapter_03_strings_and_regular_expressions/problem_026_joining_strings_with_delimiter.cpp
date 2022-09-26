#include "chapter_03_strings_and_regular_expressions/problem_026_joining_strings_with_delimiter.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <array>
#include <list>
#include <string>
#include <vector>

using namespace tmcppc::problem_26;


TEST(join, empty_array) {
    std::string result{};
    EXPECT_EQ(join(std::array<std::string, 0>{}, " "), result);
}
TEST(join, one_element_array_with_pound_delimiter) {
    EXPECT_THAT(join(std::array<std::string, 1>{ "Joe" }, "#"), ::testing::StrEq("Joe"));
}
TEST(join, vector_with_space_delimiter) {
    EXPECT_THAT(join(std::vector<std::string>{ "this", "is", "an", "example" }, " "), ::testing::StrEq("this is an example"));
}
TEST(join, list_with_dashes_delimiter) {
    EXPECT_THAT(join(std::list<std::string>{ "yet", "another", "one!" }, "---"), ::testing::StrEq("yet---another---one!"));
}

TEST(problem_26_main, output) {
    std::ostringstream oss{};
    problem_26_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "Joining [] with delimiter \"#\": \n"
        "Joining [Joe] with delimiter \"#\": Joe\n"
        "Joining [this, is, an, example] with delimiter \" \": this is an example\n"
        "Joining [yet, another, one!] with delimiter \"---\": yet---another---one!\n\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::Not(::testing::EndsWith("\n\n\n")));
}
