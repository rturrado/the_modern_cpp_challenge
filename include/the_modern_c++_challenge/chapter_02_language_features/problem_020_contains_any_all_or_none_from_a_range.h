#pragma once

#include <algorithm>  // find
#include <iosfwd>


template <typename C, typename... Args>
bool contains_any(C& c, Args&&... args) {
    return (... or (std::find(cbegin(c), cend(c), args) != cend(c)));
}

template <typename C, typename... Args>
bool contains_all(C& c, Args&&... args) {
    return (... and (std::find(cbegin(c), cend(c), args) != cend(c)));
}

template <typename C, typename... Args>
bool contains_none(C& c, Args&&... args) {
    return (... and (std::find(cbegin(c), cend(c), args) == cend(c)));
}


void problem_20_main(std::ostream& os);
void problem_20_main();
