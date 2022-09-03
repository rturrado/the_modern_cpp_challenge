#include "chapter_03_strings_and_regular_expressions/problem_025_capitalizing_an_article_title.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream
#include <string>

using namespace tmcppc::problem_25;


TEST(capitalize, empty_string) {
    std::string result{};
    EXPECT_EQ(capitalize(""), result);
}
TEST(capitalize, all_lowercase) {
    EXPECT_THAT(capitalize("the c++ challenger"), ::testing::StrEq("The C++ Challenger"));
}
TEST(capitalize, all_uppercase) {
    EXPECT_THAT(capitalize("THE C++ CHALLENGER"), ::testing::StrEq("The C++ Challenger"));
}
TEST(capitalize, uppercase_and_lowercase) {
    EXPECT_THAT(capitalize("THIS IS an ExamplE, should wORk!"), ::testing::StrEq("This Is An Example, Should Work!"));
}
TEST(capitalize, all_letters) {
    EXPECT_THAT(capitalize("SUPERCalIfragiListicoeSPialiDOSo"), ::testing::StrEq("Supercalifragilisticoespialidoso"));
}

TEST(problem_25_main, output) {
    std::ostringstream oss{};
    problem_25_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "Capitalizing word \"the c++ challenger\": \"The C++ Challenger\"\n"
        "Capitalizing word \"THIS IS an ExamplE, should wORk!\": \"This Is An Example, Should Work!\"\n\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::Not(::testing::EndsWith("\n\n\n")));
}
