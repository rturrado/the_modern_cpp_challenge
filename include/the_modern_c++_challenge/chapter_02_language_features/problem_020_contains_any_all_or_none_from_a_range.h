#pragma once

#include <algorithm>  // find
#include <iosfwd>
#include <ranges>


namespace tmcppc::problem_20 {
    template <typename R, typename... Args>
    bool contains_any(R&& r, Args&&... args) {
        return (... or (std::ranges::find(r, std::forward<Args>(args)) != r.end()));
    }

    template <typename R, typename... Args>
    bool contains_all(R&& r, Args&&... args) {
        return (... and (std::ranges::find(r, std::forward<Args>(args)) != r.end()));
    }

    template <typename R, typename... Args>
    bool contains_none(R&& r, Args&&... args) {
        return (... and (std::ranges::find(r, std::forward<Args>(args)) == r.end()));
    }
}  // namespace tmcppc::problem_20


void problem_20_main(std::ostream& os);
void problem_20_main();
