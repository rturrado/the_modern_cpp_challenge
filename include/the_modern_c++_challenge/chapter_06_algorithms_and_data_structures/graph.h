#pragma once

#include <algorithm>  // for_each, minmax, transform
#include <fmt/format.h>
#include <fmt/ostream.h>
#include <initializer_list>
#include <iterator>  // inserter
#include <limits>  // numeric_limits
#include <map>
#include <ostream>
#include <ranges>
#include <set>
#include <string>
#include <utility>  // initializer_list, make_pair, pair


namespace tmcppc::data_structures {
    // Undirected graph
    //
    // The graph is a map where the key is a pair of nodes, and the mapped value the distance between them
    template <typename Node, typename Distance>
    class undirected_graph_map {
    public:
        using key_type = std::pair<Node, Node>;
        using mapped_type = Distance;
        using value_type = std::pair<const key_type, Distance>;
        using iterator = std::map<key_type, mapped_type>::iterator;
        using const_iterator = std::map<key_type, mapped_type>::const_iterator;

        undirected_graph_map(std::initializer_list<value_type> init) : data_{ init } { }

        [[nodiscard]] bool contains(const key_type& key) const { return data_.contains(std::minmax(key.first, key.second)); }
        [[nodiscard]] mapped_type& operator[](const key_type& key) { return data_[std::minmax(key.first, key.second)]; }
        [[nodiscard]] mapped_type& at(const key_type& key) { return data_.at(std::minmax(key.first, key.second)); }
        [[nodiscard]] const mapped_type& at(const key_type& key) const { return data_.at(std::minmax(key.first, key.second)); }

        constexpr iterator begin() noexcept { return data_.begin(); }
        constexpr iterator end() noexcept { return data_.end(); }
        constexpr const_iterator begin() const noexcept { return data_.begin(); }
        constexpr const_iterator end() const noexcept { return data_.end(); }
        constexpr const_iterator cbegin() const noexcept { return data_.cbegin(); }
        constexpr const_iterator cend() const noexcept { return data_.cend(); }

    private:
        std::map<key_type, mapped_type> data_{};
    };


    // Directed graph
    //
    // The digraph is a map where the key is a source node, and the mapped value is a pair of destination node and distance between the nodes
    template <typename Node, typename Distance>
    class directed_graph_map {
    public:
        using key_type = Node;
        using mapped_type = std::pair<Node, Distance>;
        using value_type = std::pair<const key_type, mapped_type>;
        using iterator = std::map<key_type, mapped_type>::iterator;
        using const_iterator = std::map<key_type, mapped_type>::const_iterator;

        directed_graph_map(std::initializer_list<value_type> init) : data_{ init } { }

        [[nodiscard]] bool contains(const key_type& key) const { return data_.contains(key); }
        [[nodiscard]] mapped_type& operator[](const key_type& key) { return data_[key]; }
        [[nodiscard]] mapped_type& at(const key_type& key) { return data_.at(key); }
        [[nodiscard]] const mapped_type& at(const key_type& key) const { return data_.at(key); }

        constexpr iterator begin() noexcept { return data_.begin(); }
        constexpr iterator end() noexcept { return data_.end(); }
        constexpr const_iterator begin() const noexcept { return data_.begin(); }
        constexpr const_iterator end() const noexcept { return data_.end(); }
        constexpr const_iterator cbegin() const noexcept { return data_.cbegin(); }
        constexpr const_iterator cend() const noexcept { return data_.cend(); }

    private:
        std::map<key_type, mapped_type> data_{};
    };


    // Distance map associating a node to a distance
    template <typename Node, typename Distance>
    using distance_map = std::map<Node, Distance>;


    // Set of nodes
    template <typename Node>
    using node_set = std::set<Node>;


    template <typename Node, typename Distance>
    node_set<Node> get_node_list(const undirected_graph_map<Node, Distance>& graph) {
        node_set<Node> ret{};

        std::ranges::for_each(graph, [&ret](const auto& kvp) {
            const auto& p{ kvp.first };
            ret.merge(std::set{ p.first, p.second });
        });

        return ret;
    }


    // Precondition: there are nodes in distances that are not in sp_set
    template <typename Node, typename Distance>
    Node get_nearest_node_not_in_sp_set(const distance_map<Node, Distance>& distances, const node_set<Node>& sp_set) {
        auto is_not_in_sp_set = [&sp_set](const auto& kvp) { return not sp_set.contains(kvp.first); };

        // From the map of distances,
        // filter out the destination nodes already in shortest paths set,
        // and return the nearest of them
        auto distances_to_nodes_not_in_sp_set{ distances | std::ranges::views::filter(is_not_in_sp_set) };
        return std::ranges::min_element(
            distances_to_nodes_not_in_sp_set,
            std::less<Distance>{},
            [](const auto& kvp) { return kvp.second; }
        )->first;
    }


    // Precondition: node s is part of the graph
    template <typename Node, typename Distance>
    directed_graph_map<Node, Distance> get_shortest_paths_digraph(const undirected_graph_map<Node, Distance>& graph, const Node& s) {
        // Return a directed graph with the shortest paths towards the source node
        // Initialize it with a zero distance from the source node to itself
        directed_graph_map<Node, Distance> sp_digraph{ {s, {s, 0}} };

        // Set of destination nodes, i.e. all nodes except source
        node_set<Node> ds{ get_node_list(graph) };
        ds.erase(s);

        // Set of nodes for which we already know the shortest path
        node_set<Node> sp_set{};

        // Map of distances between the source node and all the other nodes
        distance_map<Node, Distance> distances{};

        // Start with infinite distances between the source node and all the other nodes
        std::ranges::transform(ds, std::inserter(distances, end(distances)), [](const auto& d) {
            return std::make_pair(d, std::numeric_limits<Distance>::max());
        });

        // And zero distance from source to itself
        distances[s] = static_cast<Distance>(0);

        // Loop destination nodes
        while (not ds.empty()) {
            // Get destination node nearest to source and not already in the shortest path set
            Node u{ get_nearest_node_not_in_sp_set(distances, sp_set) };

            // Remove it from the list of destination nodes
            ds.erase(u);

            // Add it to the shortest path set of nodes
            sp_set.insert(u);

            // Helper lambdas
            auto is_not_in_sp_set = [&sp_set](const auto& d) { return not sp_set.contains(d); };
            auto are_adjacent = [&graph](const auto& u, const auto& d) { return graph.contains({ u, d }); };
            auto is_closer_through_u = [&graph, &distances, &u](const auto& d) {
                return
                    distances[u] != std::numeric_limits<Distance>::max() and
                    distances[u] + graph.at({ u, d }) < distances[d];
            };
            auto update_shortest_path_through_u = [&graph, &sp_digraph, &distances, &u](const auto& d) {
                sp_digraph[d] = std::make_pair(u, graph.at({ u, d }));  // adding (d -> u) connection to shortest path (u -> ... -> s)

                distances[d] = distances[u] + graph.at({ u, d });  // setting (d -> ... -> s) distance as (d -> u) + (u -> ... -> s)
            };

            // Update distances[d] if
            // - d is not in shortest path set, and
            // - there is an edge from u to d, and
            // - the path from s to d is shorter through u
            for (auto& kvp : distances) {
                const Node& d{ kvp.first };

                if (is_not_in_sp_set(d) and are_adjacent(u, d) and is_closer_through_u(d)) {
                    update_shortest_path_through_u(d);
                }
            }
        }

        return sp_digraph;
    }



    // Note:
    // In a digraph we store distances from a given node (source) to a destination (pair destination/distance)
    // The functions below print the shortest paths from a given node (destination) to the rest of the nodes in a graph
    // The printout, thus, follows the form: destination -> source : destination -> ... -> source
    template <typename Node, typename Distance>
    Distance get_shortest_path_distance(const directed_graph_map<Node, Distance>& graph, const Node& s, const Node& d) {
        Distance ret{};
        for (auto n{ s }; n != d; n = graph.at(n).first) {
            ret += graph.at(n).second;
        }
        return ret;
    }


    template <typename Node, typename Distance>
    std::string get_shortest_path_string(const directed_graph_map<Node, Distance>& graph, const Node& s, const Node& d) {
        if (s == d) {
            return fmt::format("{}", s);
        } else {
            return fmt::format("{} -> {}", get_shortest_path_string(graph, graph.at(s).first, d), s);
        };
    }


    template <typename Node, typename Distance>
    void print_shortest_paths_digraph(std::ostream& os, const directed_graph_map<Node, Distance>& graph, const Node& d) {
        for (auto& kvp : graph) {
            Node s{ kvp.first };

            fmt::print(os, "\t{} -> {} : {}\t{}\n",
                d, s, get_shortest_path_distance(graph, s, d), get_shortest_path_string(graph, s, d));
        }
    }
}  // namespace tmcppc::data_structures
