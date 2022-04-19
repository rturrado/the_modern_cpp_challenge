#pragma once

#include <algorithm>  // for_each
#include <ostream>
#include <string>


template <typename Container>
std::string join(const Container& c, const std::string& delimiter) {
    std::string ret{};
    std::for_each(cbegin(c), cend(c), [first = true, &ret, &delimiter](const std::string& s) mutable {
        ret += (first ? "" : delimiter); first = false; ret += s;
    });
    return ret;
}


void problem_26_main(std::ostream& os);
void problem_26_main();
