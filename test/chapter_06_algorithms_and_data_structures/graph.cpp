#include "chapter_06_algorithms_and_data_structures/graph.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <map>
#include <ostream>
#include <sstream>  // ostringstream
#include <stdexcept>  // out_of_range
#include <utility>  // as_const, pair

using namespace tmcppc::data_structures;


// Undirected graph
//
TEST(undirected_graph_map, DISABLED_constructor_with_empty_list) {
    undirected_graph_map<char, int> ugm{};
    EXPECT_EQ(ugm.begin(), ugm.end());
}
TEST(undirected_graph_map, DISABLED_constructor) {
    undirected_graph_map<char, int> ugm{ {{ 'A', 'B' }, 7} };
    EXPECT_EQ(std::next(ugm.begin()), ugm.end());
}
TEST(undirected_graph_map, DISABLED_contains) {
    undirected_graph_map<char, int> ugm{ {{ 'A', 'B' }, 7} };
    EXPECT_TRUE(ugm.contains({ 'A','B' }));
}
TEST(undirected_graph_map, DISABLED_operator_subscript_with_new_key) {
    undirected_graph_map<char, int> ugm{};
    ugm[{'A', 'B'}] = 7;
    EXPECT_TRUE(ugm.contains({ 'A','B' }));
    EXPECT_EQ(ugm.at({ 'A','B' }), 7);
}
TEST(undirected_graph_map, DISABLED_operator_subscript_with_existing_key) {
    undirected_graph_map<char, int> ugm{ {{ 'A', 'B' }, 7} };
    auto result{ ugm[{ 'A', 'B' }] };
    EXPECT_EQ(result, 7);
}
TEST(undirected_graph_map, DISABLED_operator_at_with_new_key) {
    undirected_graph_map<char, int> ugm{};
    EXPECT_THROW((void) ugm.at({ 'A', 'B' }), std::out_of_range);
}
TEST(undirected_graph_map, DISABLED_operator_at_with_existing_key) {
    undirected_graph_map<char, int> ugm{ {{ 'A', 'B' }, 7} };
    EXPECT_EQ(ugm.at({ 'A', 'B' }), 7);
}
TEST(undirected_graph_map, DISABLED_operator_at_with_existing_key_on_const_graph) {
    undirected_graph_map<char, int> ugm{ {{ 'A', 'B' }, 7} };
    EXPECT_EQ(std::as_const(ugm).at({ 'A', 'B' }), 7);
}
TEST(undirected_graph_map, DISABLED_begin) {
    undirected_graph_map<char, int> ugm{ { {'A', 'B' }, 7} };
    std::pair<const std::pair<char, char>, int> result{ { 'A', 'B' }, 7 };
    EXPECT_EQ(*ugm.begin(), result);
}
TEST(undirected_graph_map, DISABLED_end) {
    undirected_graph_map<char, int> ugm{ {{ 'A', 'B' }, 7} };
    EXPECT_EQ(++ugm.begin(), ugm.end());
}
TEST(undirected_graph_map, DISABLED_begin_on_const_buffer) {
    undirected_graph_map<char, int> ugm{ {{ 'A', 'B' }, 7} };
    std::pair<const std::pair<char, char>, int> result{ { 'A', 'B' }, 7 };
    EXPECT_EQ(*std::as_const(ugm).begin(), result);
}
TEST(undirected_graph_map, DISABLED_end_on_const_buffer) {
    undirected_graph_map<char, int> ugm{ {{ 'A', 'B' }, 7} };
    EXPECT_EQ(++std::as_const(ugm).begin(), std::as_const(ugm).end());
}
TEST(undirected_graph_map, DISABLED_ugmegin) {
    undirected_graph_map<char, int> ugm{ { {'A', 'B' }, 7} };
    std::pair<const std::pair<char, char>, int> result{ { 'A', 'B' }, 7 };
    EXPECT_EQ(*std::as_const(ugm).cbegin(), result);
}
TEST(undirected_graph_map, DISABLED_cend) {
    undirected_graph_map<char, int> ugm{ {{ 'A', 'B' }, 7} };
    EXPECT_EQ(++std::as_const(ugm).cbegin(), std::as_const(ugm).cend());
}


// Directed graph
//
TEST(directed_graph_map, DISABLED_constructor_with_empty_list) {
    directed_graph_map<char, int> dgm{};
    EXPECT_EQ(dgm.begin(), dgm.end());
}
TEST(directed_graph_map, DISABLED_constructor) {
    directed_graph_map<char, int> dgm{ {'A', { 'B', 7 }} };
    EXPECT_EQ(std::next(dgm.begin()), dgm.end());
}
TEST(directed_graph_map, DISABLED_contains) {
    directed_graph_map<char, int> dgm{ {'A', { 'B', 7 }} };
    EXPECT_TRUE(dgm.contains( 'A' ));
}
TEST(directed_graph_map, DISABLED_operator_subscript_with_new_key) {
    directed_graph_map<char, int> dgm{};
    dgm['A'] = { 'B', 7 };
    EXPECT_TRUE(dgm.contains('A'));
    std::pair<char, int> result{ 'B', 7 };
    EXPECT_EQ(dgm.at('A'), result);
}
TEST(directed_graph_map, DISABLED_operator_subscript_with_existing_key) {
    directed_graph_map<char, int> dgm{ {'A', { 'B', 7 }} };
    std::pair<char, int> result{ 'B', 7 };
    EXPECT_EQ(dgm['A'], result);
}
TEST(directed_graph_map, DISABLED_operator_at_with_new_key) {
    directed_graph_map<char, int> dgm{};
    EXPECT_THROW((void) dgm.at('A'), std::out_of_range);
}
TEST(directed_graph_map, DISABLED_operator_at_with_existing_key) {
    directed_graph_map<char, int> dgm{ {'A', { 'B', 7 }} };
    std::pair<char, int> result{ 'B', 7 };
    EXPECT_EQ(dgm.at('A'), result);
}
TEST(directed_graph_map, DISABLED_operator_at_with_existing_key_on_const_graph) {
    directed_graph_map<char, int> dgm{ {'A', { 'B', 7 }} };
    std::pair<char, int> result{ 'B', 7 };
    EXPECT_EQ(std::as_const(dgm).at('A'), result);
}
TEST(directed_graph_map, DISABLED_begin) {
    directed_graph_map<char, int> dgm{ {'A', { 'B', 7 }} };
    std::pair<const char, std::pair<char, int>> result{ 'A', { 'B', 7 } };
    EXPECT_EQ(*dgm.begin(), result);
}
TEST(directed_graph_map, DISABLED_end) {
    directed_graph_map<char, int> dgm{ {'A', { 'B', 7 }} };
    EXPECT_EQ(++dgm.begin(), dgm.end());
}
TEST(directed_graph_map, DISABLED_begin_on_const_buffer) {
    directed_graph_map<char, int> dgm{ { 'A', { 'B', 7 } } };
    std::pair<const char, std::pair<char, int>> result{ 'A', { 'B', 7 } };
    EXPECT_EQ(*std::as_const(dgm).begin(), result);
}
TEST(directed_graph_map, DISABLED_end_on_const_buffer) {
    directed_graph_map<char, int> dgm{ {'A', { 'B', 7 }} };
    EXPECT_EQ(++std::as_const(dgm).begin(), std::as_const(dgm).end());
}
TEST(directed_graph_map, DISABLED_dgmegin) {
    directed_graph_map<char, int> dgm{ {'A', { 'B', 7 }} };
    std::pair<const char, std::pair<char, int>> result{ 'A', { 'B', 7 } };
    EXPECT_EQ(*std::as_const(dgm).cbegin(), result);
}
TEST(directed_graph_map, DISABLED_cend) {
    directed_graph_map<char, int> dgm{ {'A', { 'B', 7 }} };
    EXPECT_EQ(++std::as_const(dgm).begin(), std::as_const(dgm).end());
}


// Get node list
//
TEST(get_node_list, DISABLED_empty_graph) {
    EXPECT_TRUE(get_node_list(undirected_graph_map<char, int>{}).empty());
}
TEST(get_node_list, DISABLED_graph) {
    undirected_graph_map<char, int> ugm{ {{ 'A', 'B' }, 7}, {{ 'A', 'C' }, 9} };
    EXPECT_THAT(get_node_list(ugm), ::testing::ElementsAre('A', 'B', 'C'));
}


// Get nearest node not in shortest paths set
//
TEST(get_nearest_node_not_in_sp_set, DISABLED_first_iteration) {
    distance_map<char, int> distances{
        { 'A', 0 },
        { 'B', std::numeric_limits<int>::max() },
        { 'C', std::numeric_limits<int>::max() }
    };
    node_set<char> ds{ 'A', 'B', 'C' };
    node_set<char> sp_set{};
    EXPECT_EQ(get_nearest_node_not_in_sp_set(distances, sp_set), 'A');
}
TEST(get_nearest_node_not_in_sp_set, DISABLED_second_iteration) {
    distance_map<char, int> distances{
        { 'A', 0 },
        { 'B', 7 },
        { 'C', 9 }
    };
    node_set<char> ds{ 'B', 'C' };
    node_set<char> sp_set{ 'A' };
    EXPECT_EQ(get_nearest_node_not_in_sp_set(distances, sp_set), 'B');
}
TEST(get_nearest_node_not_in_sp_set, DISABLED_third_iteration) {
    distance_map<char, int> distances{
        { 'A', 0 },
        { 'B', 7 },
        { 'C', 8 }
    };
    node_set<char> ds{ 'C' };
    node_set<char> sp_set{ 'A', 'B' };
    EXPECT_EQ(get_nearest_node_not_in_sp_set(distances, sp_set), 'C');
}


// Get shortest paths digraph
//
TEST(get_shortest_paths_digraph, DISABLED_closed_graph) {
    undirected_graph_map<char, int> ugm{ {{ 'A', 'B' }, 7}, {{ 'A', 'C' }, 9}, {{'B', 'C'}, 1} };
    char s{ 'A' };
    EXPECT_THAT(get_shortest_paths_digraph(ugm, s), ::testing::ElementsAre(
        std::pair<const char, std::pair<char, int>>{'A', { 'A', 0 }},
        std::pair<const char, std::pair<char, int>>{'B', { 'A', 7 }},
        std::pair<const char, std::pair<char, int>>{'C', { 'B', 1 }}
    ));
}
TEST(get_shortest_paths_digraph, DISABLED_open_graph) {
    undirected_graph_map<char, int> ugm{
        {{ 'A', 'B' }, 7},
        {{ 'A', 'D' }, 1},
        {{ 'B', 'C' }, 8},
        {{ 'D', 'E' }, 2}
    };
    char s{ 'A' };
    EXPECT_THAT(get_shortest_paths_digraph(ugm, s), ::testing::ElementsAre(
        std::pair<const char, std::pair<char, int>>{'A', { 'A', 0 }},
        std::pair<const char, std::pair<char, int>>{'B', { 'A', 7 }},
        std::pair<const char, std::pair<char, int>>{'C', { 'B', 8 }},
        std::pair<const char, std::pair<char, int>>{'D', { 'A', 1 }},
        std::pair<const char, std::pair<char, int>>{'E', { 'D', 2 }}
    ));
}


// Get shortest path distance
//
TEST(get_shortest_path_distance, DISABLED_open_graph) {
    directed_graph_map<char, int> dgm{
        {'A', { 'A', 0 }},
        {'B', { 'A', 7 }},
        {'C', { 'B', 8 }},
        {'D', { 'A', 1 }},
        {'E', { 'D', 2 }}
    };
    EXPECT_EQ(get_shortest_path_distance(dgm, 'A', 'A'), 0);
    EXPECT_EQ(get_shortest_path_distance(dgm, 'B', 'B'), 0);
    EXPECT_EQ(get_shortest_path_distance(dgm, 'C', 'C'), 0);
    EXPECT_EQ(get_shortest_path_distance(dgm, 'D', 'D'), 0);
    EXPECT_EQ(get_shortest_path_distance(dgm, 'E', 'E'), 0);
    EXPECT_EQ(get_shortest_path_distance(dgm, 'B', 'A'), 7);
    EXPECT_EQ(get_shortest_path_distance(dgm, 'C', 'A'), 15);
    EXPECT_EQ(get_shortest_path_distance(dgm, 'C', 'B'), 8);
    EXPECT_EQ(get_shortest_path_distance(dgm, 'D', 'A'), 1);
    EXPECT_EQ(get_shortest_path_distance(dgm, 'E', 'A'), 3);
    EXPECT_EQ(get_shortest_path_distance(dgm, 'E', 'D'), 2);
}


// Get shortest path string
//
TEST(get_shortest_path_string, DISABLED_open_graph) {
    directed_graph_map<char, int> dgm{
        {'A', { 'A', 0 }},
        {'B', { 'A', 7 }},
        {'C', { 'B', 8 }},
        {'D', { 'A', 1 }},
        {'E', { 'D', 2 }}
    };
    EXPECT_EQ(get_shortest_path_string(dgm, 'A', 'A'), "A");
    EXPECT_EQ(get_shortest_path_string(dgm, 'B', 'B'), "B");
    EXPECT_EQ(get_shortest_path_string(dgm, 'C', 'C'), "C");
    EXPECT_EQ(get_shortest_path_string(dgm, 'D', 'D'), "D");
    EXPECT_EQ(get_shortest_path_string(dgm, 'E', 'E'), "E");
    EXPECT_EQ(get_shortest_path_string(dgm, 'B', 'A'), "A -> B");
    EXPECT_EQ(get_shortest_path_string(dgm, 'C', 'A'), "A -> B -> C");
    EXPECT_EQ(get_shortest_path_string(dgm, 'C', 'B'), "B -> C");
    EXPECT_EQ(get_shortest_path_string(dgm, 'D', 'A'), "A -> D");
    EXPECT_EQ(get_shortest_path_string(dgm, 'E', 'A'), "A -> D -> E");
    EXPECT_EQ(get_shortest_path_string(dgm, 'E', 'D'), "D -> E");
}


// Print shortest paths digraph
//
TEST(print_shortest_paths_digraph, DISABLED_open_graph) {
    std::ostringstream oss{};
    directed_graph_map<char, int> dgm{
        {'A', { 'A', 0 }},
        {'B', { 'A', 7 }},
        {'C', { 'B', 8 }},
        {'D', { 'A', 1 }},
        {'E', { 'D', 2 }}
    };
    print_shortest_paths_digraph(oss, dgm, 'A');
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "\tA -> A : 0\tA\n"
        "\tA -> B : 7\tA -> B\n"
        "\tA -> C : 15\tA -> B -> C\n"
        "\tA -> D : 1\tA -> D\n"
        "\tA -> E : 3\tA -> D -> E\n"
    ));
}
