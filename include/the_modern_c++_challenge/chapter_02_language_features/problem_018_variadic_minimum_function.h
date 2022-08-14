#pragma once

#include <fmt/format.h>
#include <fmt/ostream.h>
#include <fmt/ranges.h>
#include <ostream>
#include <string>
#include <utility>  // forward


namespace tmcppc::problem_18 {
    // Comparison function
    //
    template <typename T>
    bool more_than(T left, T right) {
        return (left > right) ? true : false;
    };


    // Variadic template for printing the elements of a list with a given string separator
    //
    template <typename T>
    std::string to_string(const std::string& separator, T&& t) {
        return fmt::format("{}", t);
    }

    template <typename T, typename... Args>
    std::string to_string(const std::string& separator, T t1, T t2, Args&&... args) {
        return fmt::format("{}{}{}", t1, separator, to_string(separator, t2, args...));
    }


    // Variadic template for getting the minimum of a list using operator<
    //
    template <typename T>
    T minimum(T&& left, T&& right) {
        return (left < right) ? left : right;
    }

    template <typename T, typename... Args>
    T minimum(T&& head, Args&&... args) {
        return minimum(std::forward<T>(head), minimum(std::forward<Args>(args)...));
    }


    // Template specialization for string literals
    //
    template <typename = void>
    const char* minimum(const char* left, const char* right) {
        return (std::string(left) < std::string(right)) ? left : right;
    }

    template <typename... Args>
    const char* minimum(const char* head, Args&&... args) {
        return minimum(head, minimum(std::forward<Args>(args)...));
    }


    // Variadic template for getting the element of a list that best satisfies a comparison function
    //
    template <typename Compare, typename T>
    T compare_with(Compare cmp, T&& left, T&& right) {
        return cmp(left, right) ? left : right;
    }

    template <typename Compare, typename T, typename... Args>
    T compare_with(Compare cmp, T&& head, Args&&... args) {
        return compare_with(cmp, std::forward<T>(head), compare_with(cmp, std::forward<Args>(args)...));
    }


    // Helper functions
    //
    template <typename... Args>
    void test_minimum(std::ostream& os, Args&&... args) {
        fmt::print(os, "minimum({}) = {}\n", to_string(", ", args...), minimum(args...));
    }

    template <typename Compare, typename... Args>
    void test_compare_with(std::ostream& os, const std::string& cmp_name, Compare cmp, Args&&... args) {
        fmt::print(os, "compare_with({}, {}) = {}\n", cmp_name, to_string(", ", args...), compare_with(cmp, args...));
    }
}  // namespace tmcppc::problem_18


void problem_18_main(std::ostream& os);
void problem_18_main();
