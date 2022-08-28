#include "chapter_02_language_features/problem_019_adding_a_range_of_values_to_a_container.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream
#include <vector>

using namespace tmcppc::problem_19;


TEST(push_back_list, push_back_list_empty_container_t) {
    std::vector<char> v{};
    push_back_list(v, 'a');
    EXPECT_EQ(v, std::vector<char>{'a'});
}
TEST(push_back_list, push_back_list_empty_container_args) {
    std::vector<char> v{};
    push_back_list(v, 'a', 'b', 'c');
    EXPECT_EQ(v, (std::vector<char>{ 'a', 'b', 'c' }));
}
TEST(push_back_list, push_back_list_non_empty_container_t) {
    std::vector<char> v{ 'a' };
    push_back_list(v, 'b');
    EXPECT_EQ(v, (std::vector<char>{ 'a', 'b' }));
}
TEST(push_back_list, push_back_list_non_empty_container_args) {
    std::vector<char> v{ 'a' };
    push_back_list(v, 'b', 'c', 'd');
    EXPECT_EQ(v, (std::vector<char>{ 'a', 'b', 'c', 'd' }));
}

TEST(push_back_list, push_back_list_v2_empty_container_t) {
    std::vector<char> v{};
    push_back_list_v2(v, 'a');
    EXPECT_EQ(v, std::vector<char>{ 'a' });
}
TEST(push_back_list, push_back_list_v2_empty_container_args) {
    std::vector<char> v{};
    push_back_list_v2(v, 'a', 'b', 'c');
    EXPECT_EQ(v, (std::vector<char>{ 'a', 'b', 'c' }));
}
TEST(push_back_list, push_back_list_v2_non_empty_container_t) {
    std::vector<char> v{ 'a' };
    push_back_list_v2(v, 'b');
    EXPECT_EQ(v, (std::vector<char>{ 'a', 'b' }));
}
TEST(push_back_list, push_back_list_v2_non_empty_container_args) {
    std::vector<char> v{ 'a' };
    push_back_list_v2(v, 'b', 'c', 'd');
    EXPECT_EQ(v, (std::vector<char>{ 'a', 'b', 'c', 'd' }));
}

TEST(problem_19_main, output) {
    std::ostringstream oss{};
    problem_19_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "Adding 10, 20, and 30 to an empty vector of ints: [10, 20, 30]\n"
        "Adding \"Hey\", \"Joe!\", and \"Voodoo\" to an empty vector of strings: [\"Hey\", \"Joe!\", \"Voodoo\"]\n"
        "Adding 3.14f, 0.99f, and -273.0f ot an empty list of floats: [3.14, 0.99, -273]\n\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::Not(::testing::EndsWith("\n\n\n")));
}
