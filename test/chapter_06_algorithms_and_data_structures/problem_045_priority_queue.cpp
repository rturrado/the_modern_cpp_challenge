#include "chapter_06_algorithms_and_data_structures/problem_045_priority_queue.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <sstream>  // ostringstream


TEST(problem_45_main, output) {
    std::ostringstream oss{};
    problem_45_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("v: [3, 6, 7, 2, 4, 9, 5, 1, 8, 0]\n"));
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("priority_queue<int> pq_1(cbegin(v), cend(v));\n"));
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("priority_queue<int, std::greater<int>> pq_2(cbegin(v), cend(v));\n"));
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("priority_queue<int> pq_3();\n\tpq_3: []\n"));
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("priority_queue<int> pq_5(std::move(pq_1));\n"));
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("pq_5.swap(pq_3);\n\tpq_5: []\n"));
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("pq_5.push(-20);\n\tpq_5: [-20]\n"));
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("pq_5.push(15);\n"));
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("pq_5.pop()\n\tpq_5: [-20]\n"));
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("pq_5.pop();\n\tpq_5: []\n"));
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("pq_5.size(): 0\npq_3.empty(): false\npq_5.empty(): true\n"));
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("priority_queue<int, std::greater<int>> pq_6();\n\tpq_6: []\n"));
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("pq_6.push(9);\n\tpq_6: [9]\n"));
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("pq_6.push(8);\n"));
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("pq_6.push(7);\n"));
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("pq_6.push(6);\n"));
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("pq_6.push(5);\n"));
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("pq_6.push(4);\n"));
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("pq_6.push(3);\n"));
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("pq_6.push(2);\n"));
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("pq_6.push(1);\n"));
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("pq_6.pop();\n"));
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("pq_6.pop();\n\tpq_6: [9]\n"));
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("pq_6.pop();\n\tpq_6: []\n"));
}
