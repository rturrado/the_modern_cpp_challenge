#include "chapter_06_algorithms_and_data_structures/problem_048_most_frequent_element_in_a_range.h"
#include "rtc/print.h"

#include <algorithm>  // copy_if, max_element
#include <format>
#include <functional>  // greater
#include <map>  // multimap
#include <iostream>  // cout
#include <iterator>  // back_inserter
#include <ostream>
#include <utility>  // pair
#include <vector>


template <typename T>
struct ElementCount
{
    T element{};
    size_t count{};
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const ElementCount<T>& ec)
{
    return os << std::format("[e={}, c={}]", ec.element, ec.count);
}

template <typename T>
using ElementCountList = std::vector<ElementCount<T>>;


// v1: my solution
template <typename T>
ElementCountList<T> most_frequent_elements_v1(const std::vector<T>& v)
{
    using count = size_t;
    std::map<T, count> count_for_a_given_element{};
    std::multimap<count, T, std::greater<>> elements_with_a_given_count{};

    // Build maps of counts for a given element and elements with a given count
    for (const auto& e : v)
    {
        count_for_a_given_element[e]++;
        auto count = count_for_a_given_element[e];
        elements_with_a_given_count.insert({ count, e });
    }

    // Build return list of elements and counts
    // Since the map is sorted from highest to lowest, we stop walking once an element is smaller than a previous one
    ElementCountList<T> ret{};
    for (const auto& [current_count, current_element] : elements_with_a_given_count)
    {
        if ((not ret.empty()) and (current_count < begin(ret)->count)) { break; }
        ret.push_back({ current_element, current_count });
    }

    return ret;
}


// v2: much nicer book's solution
template <typename T>
std::vector<std::pair<T, size_t>> most_frequent_elements_v2(const std::vector<T>& v)
{
    // Build map of counts
    std::map<T, size_t> counts{};
    for (const auto& e : v) { counts[e]++; }

    // Get iterator to element with greatest count
    auto element_with_highest_count_it{ std::max_element(cbegin(counts), cend(counts),
        [](const auto& kvp1, const auto& kvp2) { return kvp1.second < kvp2.second; }) };

    // Build return list of elements and counts
    std::vector<std::pair<T, size_t>> ret{};
    std::copy_if(cbegin(counts), cend(counts), std::back_inserter(ret),
        [&element_with_highest_count_it](const auto& kvp) { return kvp.second == element_with_highest_count_it->second; });
    
    return ret;
}


// The most frequent element in a range
//
// Write a function that, given a range, returns the most frequent element and the number of times it appears in the range.
// If more than one element appears the same maximum number of times then the function should return all the elements.
// For instance, for the range {1, 1, 3, 5, 8, 13, 3, 5, 8, 8, 5}, it should return {5, 3} and {8, 3}.
void problem_48_main()
{
    std::vector<int> v_i{ 1, 1, 3, 5, 8, 13, 3, 5, 8, 8, 5 };
    std::vector<char> v_c{ '0', 'a', 'A', '@', '0', 'A', '@', '@' };
    std::vector<double> v_d{};

    std::cout << "Most frequent elements in\n";
    std::cout << "\t" << v_i << "\n";
    std::cout << "\t\t(using v1): " << most_frequent_elements_v1(v_i) << "\n";
    std::cout << "\t\t(using v2): " << most_frequent_elements_v2(v_i) << "\n\n";
    std::cout << "\t" << v_c << "\n";
    std::cout << "\t\t(using v1): " << most_frequent_elements_v1(v_c) << "\n";
    std::cout << "\t\t(using v2): " << most_frequent_elements_v2(v_c) << "\n\n";
    std::cout << "\t" << v_d << "\n";
    std::cout << "\t\t(using v1): " << most_frequent_elements_v1(v_d) << "\n";
    std::cout << "\t\t(using v2): " << most_frequent_elements_v2(v_d) << "\n\n";
}
