#include "chapter_06_algorithms_and_data_structures/graph.h"
#include "chapter_06_algorithms_and_data_structures/problem_058_shortest_path_between_two_nodes.h"

#include "fmt/ostream.h"
#include "fmt/ranges.h"

#include <iostream>  // cout


void problem_58_main(std::ostream& os) {
    using namespace tmcppc::data_structures;

    const undirected_graph_map<char, int> graph{
        {{ 'A', 'B' }, 7},
        {{ 'A', 'C' }, 9},
        {{ 'A', 'F' }, 14},
        {{ 'B', 'C' }, 10},
        {{ 'B', 'D' }, 15},
        {{ 'C', 'D' }, 11},
        {{ 'C', 'F' }, 2},
        {{ 'D', 'E' }, 6},
        {{ 'E', 'F' }, 9}
    };

    fmt::print(os, "Network of nodes:\n\t{}\n", graph);

    for (auto node : get_node_list(graph)) {
        fmt::print(os, "Shortest distance from node '{}' to all the others:\n", node);
        print_shortest_paths_digraph(os, get_shortest_paths_digraph(graph, node), node);
    }

    fmt::print(os, "\n");
}


// The shortest path between two nodes
//
// Write a program that, given a network of nodes and the distances between them,
// computes and displays the shortest distance from a specified node to all the others,
// as well as the path between the start and end node.
//
// As input, consider the following undirected graph:
//
//     [A, B] = 7, [A, C] = 9, [A, F] = 14
//     [B, C] = 10, [B, D] = 15
//     [C, D] = 11, [C, F] = 2
//     [D, E] = 6
//     [E, F] = 9
//
// The program output for this graph should be the following:
//
// A -> A : 0     A
// A -> B : 7     A -> B
// A -> C : 9     A -> C
// A -> D : 20    A -> C -> D
// A -> E : 20    A -> C -> F -> E
// A -> F : 11    A -> C -> F
void problem_58_main() {
    problem_58_main(std::cout);
}
