#pragma once

#include <algorithm>  // for_each
#include <iosfwd>
#include <string>


namespace tmcppc::problem_26 {
    template <typename Container>
    std::string join(const Container& c, const std::string& delimiter) {
        std::string ret{};
        std::for_each(cbegin(c), cend(c), [first = true, &ret, &delimiter](const std::string& s) mutable {
            ret += (first ? "" : delimiter); first = false; ret += s;
        });
        return ret;
    }
}  // namespace tmcppc::problem_26


void problem_26_main(std::ostream& os);
void problem_26_main();
