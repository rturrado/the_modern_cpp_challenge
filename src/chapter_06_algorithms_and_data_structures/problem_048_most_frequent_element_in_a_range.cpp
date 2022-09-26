#include "chapter_06_algorithms_and_data_structures/problem_048_most_frequent_element_in_a_range.h"

#include "fmt/ostream.h"
#include "fmt/ranges.h"

#include <iostream>  // cout
#include <ostream>
#include <vector>


void problem_48_main(std::ostream& os) {
    using namespace tmcppc::data_structures;
    using namespace tmcppc::problem_48;

    std::vector<int> v_i{ 1, 1, 3, 5, 8, 13, 3, 5, 8, 8, 5 };
    std::vector<char> v_c{ '0', 'a', 'A', '@', '0', 'A', '@', '@' };
    std::vector<double> v_d{};

    fmt::print(os, "Most frequent elements in:\n");
    fmt::print(os, "\t{}\n", v_i);
    fmt::print(os, "\t\t(using v1): [{}]\n", fmt::join(most_frequent_elements_v1(v_i), ", "));
    fmt::print(os, "\t\t(using v2): [{}]\n\n", fmt::join(most_frequent_elements_v2(v_i), ", "));
    fmt::print(os, "\t[{}]\n", fmt::join(v_c, ", "));
    fmt::print(os, "\t\t(using v1): [{}]\n", fmt::join(most_frequent_elements_v1(v_c), ", "));
    fmt::print(os, "\t\t(using v2): [{}]\n\n", fmt::join(most_frequent_elements_v2(v_c), ", "));
    fmt::print(os, "\t{}\n", v_d);
    fmt::print(os, "\t\t(using v1): [{}]\n", fmt::join(most_frequent_elements_v1(v_d), ", "));
    fmt::print(os, "\t\t(using v2): [{}]\n\n", fmt::join(most_frequent_elements_v2(v_d), ", "));
}


// The most frequent element in a range
//
// Write a function that, given a range, returns the most frequent element and the number of times it appears in the range.
// If more than one element appears the same maximum number of times then the function should return all the elements.
// For instance, for the range {1, 1, 3, 5, 8, 13, 3, 5, 8, 8, 5}, it should return {5, 3} and {8, 3}.
void problem_48_main() {
    problem_48_main(std::cout);
}
