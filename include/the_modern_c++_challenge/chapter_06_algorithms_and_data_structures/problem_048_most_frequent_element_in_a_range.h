#pragma once

#include <algorithm>  // copy_if, max_element
#include <fmt/format.h>
#include <fmt/ostream.h>
#include <functional>  // greater
#include <iterator>  // back_inserter
#include <map>  // multimap
#include <ostream>
#include <utility>  // pair
#include <vector>


template <typename T>
struct element_count {
    T element{};
    size_t count{};
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const element_count<T>& ec) {
    fmt::print(os, "{}", ec);
    return os;
}

template <typename T>
struct fmt::formatter<element_count<T>> {
    template<typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const element_count<T>& ec, FormatContext& ctx) const -> decltype(ctx.out()) {
        return fmt::format_to(ctx.out(), "[e={}, c={}]", ec.element, ec.count);
    }
};

template <typename T>
using element_count_list = std::vector<element_count<T>>;


// v1: my solution
template <typename T>
element_count_list<T> most_frequent_elements_v1(const std::vector<T>& v) {
    using count = size_t;
    std::map<T, count> count_for_a_given_element{};
    std::multimap<count, T, std::greater<>> elements_with_a_given_count{};

    // Build maps of counts for a given element and elements with a given count
    for (const auto& e : v) {
        count_for_a_given_element[e]++;
        auto count = count_for_a_given_element[e];
        elements_with_a_given_count.insert({ count, e });
    }

    // Build return list of elements and counts
    // Since the map is sorted from highest to lowest, we stop walking once an element is smaller than a previous one
    element_count_list<T> ret{};
    for (const auto& [current_count, current_element] : elements_with_a_given_count) {
        if ((not ret.empty()) and (current_count < begin(ret)->count)) { break; }
        ret.push_back({ current_element, current_count });
    }

    return ret;
}


// v2: book's solution (much nicer)
template <typename T>
std::vector<std::pair<T, size_t>> most_frequent_elements_v2(const std::vector<T>& v) {
    // Build map of counts
    std::map<T, size_t> counts{};
    for (const auto& e : v) {
        counts[e]++;
    }

    // Get iterator to element with greatest count
    auto element_with_highest_count_it{ std::max_element(cbegin(counts), cend(counts),
        [](const auto& kvp1, const auto& kvp2) { return kvp1.second < kvp2.second; }) };

    // Build return list of elements and counts
    std::vector<std::pair<T, size_t>> ret{};
    std::copy_if(cbegin(counts), cend(counts), std::back_inserter(ret),
        [&element_with_highest_count_it](const auto& kvp) { return kvp.second == element_with_highest_count_it->second; });

    return ret;
}


void problem_48_main(std::ostream& os);
void problem_48_main();
