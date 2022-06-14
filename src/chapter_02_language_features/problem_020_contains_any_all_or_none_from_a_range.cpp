#include "chapter_02_language_features/problem_020_contains_any_all_or_none_from_a_range.h"

#include <array>
#include <cassert>  // assert
#include <fmt/ostream.h>
#include <iostream>  // cout
#include <list>
#include <vector>


void problem_20_main(std::ostream& os) {
    using namespace tmcppc::problem_20;

    std::vector<int> v{ 1, 2, 3, 4, 5, 6 };
    fmt::print(os, "{}", "Checking std::vector<int> v{1, 2, 3, 4, 5, 6} contains_any of (0, 3, 30)\n");
    assert(contains_any(v, 0, 3, 30));

    std::array<int, 6> a{ { 1, 2, 3, 4, 5, 6 } };
    fmt::print(os, "{}", "Checking std::array<int, 6> a{1, 2, 3, 4, 5, 6} contains_all of (1, 3, 5, 6)\n");
    assert(contains_all(a, 1, 3, 5, 6));

    std::list<int> l{ 1, 2, 3, 4, 5, 6 };
    fmt::print(os, "{}", "Checking std::list<int> l{1, 2, 3, 4, 5, 6} not contains_none of (0, 6)\n");
    assert(not contains_none(l, 0, 6));

    fmt::print(os, "\n");
}


// Container any, all, none
//
// Write a set of general-purpose functions that enable checking whether any, all, or none
// of the specified arguments are present in a given container.
void problem_20_main() {
    problem_20_main(std::cout);
}
