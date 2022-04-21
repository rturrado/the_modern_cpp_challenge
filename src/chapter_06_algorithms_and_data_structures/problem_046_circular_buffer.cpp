#include "Chapter6_AlgorithmsAndDataStructures.h"
#include "Chapter6_AlgorithmsAndDataStructures/CircularBuffer.h"
#include "RtcPrint.h"

#include <iostream>  // cout
#include <stdexcept>  // runtime_error
#include <string_view>  // literals

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
void problem_46_main()
{
    using namespace std::literals;

    auto print_circular_buffer = [](const std::string_view cb_name, const auto& cb) -> void {
        std::cout << "\t" << cb_name.data() << ": " << cb << ", capacity: " << cb.capacity() << ", size: " << cb.size();
        if (not cb.empty()) { std::cout << ", front: " << cb.front() << ", back: " << cb.back(); }
        std::cout << "\n";
    };

    // CircularBuffer<int> cb_1{};  // wrong: default constructor is private

    try
    {
        CircularBuffer<int> cb_2{ 0 };
    }
    catch (const std::runtime_error& err)
    {
        std::cout << "Error: " << err.what() << "\n";
    }
    std::cout << "\n";

    CircularBuffer<double> cb_3{ 5 };
    std::cout << "CircularBuffer<double> cb_3{ 5 };\n";
    print_circular_buffer("cb_3"sv, cb_3);
    std::cout << "\n";

    for (auto i{ 1 }; i < static_cast<int>(1.5 * cb_3.capacity()); ++i)
    {
        cb_3.push_back(i);
        std::cout << "cb_3.push_back(" << i << ");\n";
        print_circular_buffer("cb_3"sv, cb_3);
    }
    std::cout << "\n";

    cb_3.pop_front(); std::cout << "cb_3.pop_front()\n";
    print_circular_buffer("cb_3"sv, cb_3);
    cb_3.pop_back(); std::cout << "cb_3.pop_back()\n";
    print_circular_buffer("cb_3"sv, cb_3);
    std::cout << "\n";

    cb_3.clear(); std::cout << "cb_3.clear()\n";
    print_circular_buffer("cb_3"sv, cb_3);
    std::cout << "\n";
}
