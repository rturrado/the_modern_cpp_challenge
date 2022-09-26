#include "chapter_06_algorithms_and_data_structures/problem_055_zip_algorithm.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <sstream>  // ostringstream

using namespace tmcppc::problem_55;


TEST(zip, empty_ranges_with_empty_range) {
    EXPECT_TRUE(zip(std::vector<int>{}, std::vector<int>{}).empty());
}
TEST(zip, empty_range_with_one_element_range) {
    EXPECT_TRUE(zip(std::vector<int>{}, std::vector<int>{ 1 }).empty());
}
TEST(zip, one_element_range_with_one_element_range) {
    EXPECT_THAT(zip(std::vector<int>{ 1 }, std::vector<char>{ 'a' }), ::testing::ElementsAre(
        std::pair<int, char>{ 1, 'a' }
    ));
}
TEST(zip, one_element_range_with_two_elements_range) {
    EXPECT_THAT(zip(std::vector<int>{ 1 }, std::vector<char>{ 'a', 'b' }), ::testing::ElementsAre(
        std::pair<int, char>{ 1, 'a' }
    ));
}
TEST(zip, two_elements_range_with_two_elements_range) {
    EXPECT_THAT(zip(std::vector<int>{ 1, 2 }, std::vector<char>{ 'a', 'b' }), ::testing::ElementsAre(
        std::pair<int, char>{ 1, 'a' },
        std::pair<int, char>{ 2, 'b' }
    ));
}


TEST(problem_55_main, output) {
    std::ostringstream oss{};
    problem_55_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "Zipping [1, 2, 3, 4, 5, 6, 7, 8, 9, 10] and [1, 1, 3, 5, 8, 13, 21]:\n"
        "\t[(1, 1), (2, 1), (3, 3), (4, 5), (5, 8), (6, 13), (7, 21)]\n"
        "\n"
        "Zipping [1, 2, 3, 4, 5, 6, 7, 8, 9, 10] and [a, b, c, d, e]:\n"
        "\t[(1, 'a'), (2, 'b'), (3, 'c'), (4, 'd'), (5, 'e')]\n\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::Not(::testing::EndsWith("\n\n\n")));
}
