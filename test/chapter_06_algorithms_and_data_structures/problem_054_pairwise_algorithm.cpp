#include "chapter_06_algorithms_and_data_structures/problem_054_pairwise_algorithm.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream
#include <utility>  // pair
#include <vector>

using namespace tmcppc::problem_54;


TEST(zip_with_next, DISABLED_empty_vector) {
    EXPECT_TRUE(zip_with_next(std::vector<int>{}).empty());
}
TEST(zip_with_next, DISABLED_one_element_vector) {
    EXPECT_TRUE(zip_with_next(std::vector<int>{ 1 }).empty());
}
TEST(zip_with_next, DISABLED_two_elements_vector) {
    EXPECT_THAT(zip_with_next(std::vector<int>{ 1, 2 }), ::testing::ElementsAre(
        std::pair<int, int>{ 1, 2 }
    ));
}
TEST(zip_with_next, DISABLED_three_elements_vector) {
    EXPECT_THAT(zip_with_next(std::vector<int>{ 1, 2, 3 }), ::testing::ElementsAre(
        std::pair<int, int>{ 1, 2 }
    ));
}
TEST(zip_with_next, DISABLED_four_elements_vector) {
    EXPECT_THAT(zip_with_next(std::vector<int>{ 1, 2, 3, 4 }), ::testing::ElementsAre(
        std::pair<int, int>{ 1, 2 },
        std::pair<int, int>{ 3, 4 }
    ));
}


TEST(problem_54_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_54_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "Zipping [1, 1, 2, 3, 5, 8] with next: [(1, 1), (2, 3), (5, 8)]\n"
        "Zipping [1, 1, 2, 3, 5, 8, 13] with next: [(1, 1), (2, 3), (5, 8)]\n"
    ));
}
