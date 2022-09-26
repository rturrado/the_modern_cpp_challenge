#include "chapter_06_algorithms_and_data_structures/problem_048_most_frequent_element_in_a_range.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <sstream>  // ostringstream
#include <utility>  // pair
#include <vector>

using namespace tmcppc::problem_48;
using tmcppc::data_structures::element_count;
using tmcppc::data_structures::element_count_list;


TEST(most_frequent_elements_v1, empty_vector) {
    EXPECT_TRUE(most_frequent_elements_v1(std::vector<int>{}).empty());
}
TEST(most_frequent_elements_v1, vector_1_1_1) {
    EXPECT_THAT(most_frequent_elements_v1(std::vector<int>{ 1, 1, 1 }), ::testing::ElementsAre(element_count<int>{ 1, 3 }));
}
TEST(most_frequent_elements_v1, vector_1_1_2) {
    EXPECT_THAT(most_frequent_elements_v1(std::vector<int>{ 1, 1, 2 }), ::testing::ElementsAre(element_count<int>{ 1, 2 }));
}
TEST(most_frequent_elements_v1, vector_1_1_2_2) {
    EXPECT_THAT(most_frequent_elements_v1(std::vector<int>{ 1, 1, 2, 2 }), ::testing::ElementsAre(
        element_count<int>{ 1, 2 },
        element_count<int>{ 2, 2 }
    ));
}
TEST(most_frequent_elements_v1, vector_1_2_3) {
    EXPECT_THAT(most_frequent_elements_v1(std::vector<int>{ 1, 2, 3 }), ::testing::ElementsAre(
        element_count<int>{ 1, 1 },
        element_count<int>{ 2, 1 },
        element_count<int>{ 3, 1 }
    ));
}


TEST(most_frequent_elements_v2, empty_vector) {
    EXPECT_TRUE(most_frequent_elements_v2(std::vector<int>{}).empty());
}
TEST(most_frequent_elements_v2, vector_1_1_1) {
    EXPECT_THAT(most_frequent_elements_v2(std::vector<int>{ 1, 1, 1 }), ::testing::ElementsAre(std::pair<int, size_t>{ 1, 3 }));
}
TEST(most_frequent_elements_v2, vector_1_1_2) {
    EXPECT_THAT(most_frequent_elements_v2(std::vector<int>{ 1, 1, 2 }), ::testing::ElementsAre(std::pair<int, size_t>{ 1, 2 }));
}
TEST(most_frequent_elements_v2, vector_1_1_2_2) {
    EXPECT_THAT(most_frequent_elements_v2(std::vector<int>{ 1, 1, 2, 2 }), ::testing::ElementsAre(
        std::pair<int, size_t>{ 1, 2 },
        std::pair<int, size_t>{ 2, 2 }
    ));
}
TEST(most_frequent_elements_v2, vector_1_2_3) {
    EXPECT_THAT(most_frequent_elements_v2(std::vector<int>{ 1, 2, 3 }), ::testing::ElementsAre(
        std::pair<int, size_t>{ 1, 1 },
        std::pair<int, size_t>{ 2, 1 },
        std::pair<int, size_t>{ 3, 1 }
    ));
}


TEST(problem_48_main, output) {
    std::ostringstream oss{};
    problem_48_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "Most frequent elements in:\n"
        "\t[1, 1, 3, 5, 8, 13, 3, 5, 8, 8, 5]\n"
        "\t\t(using v1): [[e=8, c=3], [e=5, c=3]]\n"
        "\t\t(using v2): [(5, 3), (8, 3)]\n"
        "\n"
        "\t[0, a, A, @, 0, A, @, @]\n"
        "\t\t(using v1): [[e=@, c=3]]\n"
        "\t\t(using v2): [('@', 3)]\n"
        "\n"
        "\t[]\n"
        "\t\t(using v1): []\n"
        "\t\t(using v2): []\n"
    ));
}
