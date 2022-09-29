#include "chapter_06_algorithms_and_data_structures/problem_058_shortest_path_between_two_nodes.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <sstream>  // ostringstream


TEST(problem_58_main, output) {
    std::ostringstream oss{};
    problem_58_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "Network of nodes:\n"
        "\t{('A', 'B'): 7, ('A', 'C'): 9, ('A', 'F'): 14, ('B', 'C'): 10, ('B', 'D'): 15, ('C', 'D'): 11, ('C', 'F'): 2, ('D', 'E'): 6, ('E', 'F'): 9}\n"
        "Shortest distance from node 'A' to all the others:\n"
        "\tA -> A : 0\tA\n"
        "\tA -> B : 7\tA -> B\n"
        "\tA -> C : 9\tA -> C\n"
        "\tA -> D : 20\tA -> C -> D\n"
        "\tA -> E : 20\tA -> C -> F -> E\n"
        "\tA -> F : 11\tA -> C -> F\n"
        "Shortest distance from node 'B' to all the others:\n"
        "\tB -> A : 7\tB -> A\n"
        "\tB -> B : 0\tB\n"
        "\tB -> C : 10\tB -> C\n"
        "\tB -> D : 15\tB -> D\n"
        "\tB -> E : 21\tB -> C -> F -> E\n"
        "\tB -> F : 12\tB -> C -> F\n"
        "Shortest distance from node 'C' to all the others:\n"
        "\tC -> A : 9\tC -> A\n"
        "\tC -> B : 10\tC -> B\n"
        "\tC -> C : 0\tC\n"
        "\tC -> D : 11\tC -> D\n"
        "\tC -> E : 11\tC -> F -> E\n"
        "\tC -> F : 2\tC -> F\n"
        "Shortest distance from node 'D' to all the others:\n"
        "\tD -> A : 20\tD -> C -> A\n"
        "\tD -> B : 15\tD -> B\n"
        "\tD -> C : 11\tD -> C\n"
        "\tD -> D : 0\tD\n"
        "\tD -> E : 6\tD -> E\n"
        "\tD -> F : 13\tD -> C -> F\n"
        "Shortest distance from node 'E' to all the others:\n"
        "\tE -> A : 20\tE -> F -> C -> A\n"
        "\tE -> B : 21\tE -> D -> B\n"
        "\tE -> C : 11\tE -> F -> C\n"
        "\tE -> D : 6\tE -> D\n"
        "\tE -> E : 0\tE\n"
        "\tE -> F : 9\tE -> F\n"
        "Shortest distance from node 'F' to all the others:\n"
        "\tF -> A : 11\tF -> C -> A\n"
        "\tF -> B : 12\tF -> C -> B\n"
        "\tF -> C : 2\tF -> C\n"
        "\tF -> D : 13\tF -> C -> D\n"
        "\tF -> E : 9\tF -> E\n"
        "\tF -> F : 0\tF\n\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::Not(::testing::EndsWith("\n\n\n")));
}
