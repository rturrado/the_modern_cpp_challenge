#pragma once

#include <algorithm>  // transform
#include <fmt/format.h>
#include <fmt/ostream.h>
#include <iterator>  // back_inserter
#include <ostream>
#include <string>
#include <type_traits>  // invoke_result_t
#include <utility>  // forward
#include <vector>


struct book {
    int id{};
    std::string title;
    std::string author;
};

inline std::ostream& operator<<(std::ostream& os, const book& b) {
    fmt::print(os, "{}", b);
    return os;
}


template <>
struct fmt::formatter<book> {
    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const book& b, FormatContext& ctx) const -> decltype(ctx.out()) {
        return fmt::format_to(ctx.out(), "(id = {}, title = {}, author = {})", b.id, b.title, b.author);
    }
};


template <typename T, typename F>
    requires requires (T&& t, F f) { f(t); }
auto select(const std::vector<T>& v, F&& f) {
    std::vector<std::invoke_result_t<F, const T&>> ret{};
    std::transform(cbegin(v), cend(v), std::back_inserter(ret), std::forward<F>(f));
    return ret;
}


void problem_56_main(std::ostream& os);
void problem_56_main();
