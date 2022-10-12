#include "chapter_06_algorithms_and_data_structures/problem_046_circular_buffer.h"
#include "chapter_06_algorithms_and_data_structures/circular_buffer.h"

#include <fmt/ostream.h>
#include <fmt/ranges.h>
#include <stdexcept>  // runtime_error
#include <string_view>


// Create a data structure that represents a circular buffer of a fixed size.
// A circular buffer overwrites existing elements when the buffer is being filled beyond its fixed size.
//
// The class you must write should:
//
// - Prohibit default construction.
// - Support the creation of objects with a specified size.
// - Allow checking of the buffer capacity and status (empty(), full(), size(), capacity())
// - Add a new element, an operation that could potentially overwrite the oldest element in the buffer.
// - Remove the oldest element from the buffer.
// - Support iteration through its elements.
void problem_46_main(std::ostream& os) {
    using tmcppc::data_structures::circular_buffer;

    auto print_circular_buffer = [&os](const std::string_view cb_name, const auto& cb) -> void {
        fmt::print(os, "\t{}: {}, capacity: {}, size: {}{}\n",
            cb_name,
            cb,
            cb.capacity(),
            cb.size(),
            (cb.empty())
                ? ""
                : fmt::format(", front: {}, back: {}", cb.front(), cb.back())
        );
    };

    // circular_buffer<int> cb_1{};  // wrong: default constructor is private

    try {
        circular_buffer<int> cb_2{ 0 };
    } catch (const std::runtime_error& err) {
        fmt::print(os, "Error: {}\n", err.what());
    }
    fmt::print(os, "\n");

    circular_buffer<double> cb_3{ 5 };
    fmt::print(os, "circular_buffer<double> cb_3(5);\n");
    print_circular_buffer("cb_3", cb_3);
    fmt::print(os, "\n");

    for (auto i{ 1 }; i < static_cast<int>(1.5 * static_cast<double>(cb_3.capacity())); ++i) {
        cb_3.push_back(i);
        fmt::print(os, "cb_3.push_back({});\n", i);
        print_circular_buffer("cb_3", cb_3);
    }
    fmt::print(os, "\n");

    cb_3.pop_front();
    fmt::print(os, "cb_3.pop_front();\n");
    print_circular_buffer("cb_3", cb_3);
    cb_3.pop_back();
    fmt::print(os, "cb_3.pop_back();\n");
    print_circular_buffer("cb_3", cb_3);
    fmt::print(os, "\n");

    cb_3.clear();
    fmt::print(os, "cb_3.clear();\n");
    print_circular_buffer("cb_3", cb_3);
    fmt::print(os, "\n");
}
