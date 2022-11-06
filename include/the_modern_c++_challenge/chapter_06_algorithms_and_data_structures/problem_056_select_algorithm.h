#pragma once

#include <algorithm>  // transform
#include <fmt/format.h>
#include <fmt/ostream.h>
#include <iterator>  // back_inserter
#include <ostream>
#include <string>
#include <type_traits>  // invoke_result_t, remove_cvref
#include <utility>  // forward
#include <vector>


namespace tmcppc::problem_56 {
    struct book {
        int id{};
        std::string title;
        std::string author;

        friend std::ostream& operator<<(std::ostream& os, const book& b) {
            return os << fmt::format("(id = {}, title = {}, author = {})", b.id, b.title, b.author);
        }
    };

    template <typename T, typename F>
        requires requires (T&& t, F&& f) { f(t); }
    auto select(const std::vector<T>& v, F&& f) {
        std::vector<std::remove_cvref_t<std::invoke_result_t<F, const T&>>> ret{};
        std::ranges::transform(v, std::back_inserter(ret), std::forward<F>(f));
        return ret;
    }
}  // namespace tmcppc::problem_56


// fmt formatter
template <>
struct fmt::formatter<tmcppc::problem_56::book> : fmt::ostream_formatter {};


void problem_56_main(std::ostream& os);
