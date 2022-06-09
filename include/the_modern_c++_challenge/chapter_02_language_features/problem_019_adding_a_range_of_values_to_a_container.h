#pragma once

#include <iosfwd>
#include <utility>  // forward


namespace tmcppc::problem_19 {
    template <typename C, typename T>
    concept ContainerWithPushBack = requires (C c, T t) { c.push_back(t); };

    template <typename ContainerWithPushBack, typename T, typename = void>
    void push_back_list(ContainerWithPushBack& c, T&& t) {
        c.push_back(std::forward<T>(t));
    }

    template <typename ContainerWithPushBack, typename T, typename... Args>
    void push_back_list(ContainerWithPushBack& c, T&& t, Args&&... args) {
        c.push_back(std::forward<T>(t));
        push_back_list(c, std::forward<Args>(args)...);
    }

    // Using a fold expression as in the book
    template <typename ContainerWithPushBack, typename... Args>
    void push_back_list_v2(ContainerWithPushBack& c, Args... args) {
        (c.push_back(args), ...);
    }
}  // namespace tmcppc::problem_19


void problem_19_main(std::ostream& os);
void problem_19_main();
