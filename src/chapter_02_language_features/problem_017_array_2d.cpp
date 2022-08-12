#include "chapter_02_language_features/array_2d.h"
#include "chapter_02_language_features/problem_017_array_2d.h"

#include <algorithm>  // transform
#include <exception>
#include <fmt/ostream.h>
#include <fmt/ranges.h>
#include <iostream>  // cout
#include <numeric>  // iota
#include <ostream>


void problem_17_main(std::ostream& os) {
    using namespace tmcppc::data_structures;

    try {
        // Array of ints initialized with width and height
        // Then modified using iota()
        array_2d<int> arr1(3, 3);
        std::iota(arr1.begin(), arr1.end(), 1);
        fmt::print(os, "arr1:\n{}\n\n", arr1);

        // Array of floats initialized with width and height
        // Then modified using at()
        array_2d<float> arr2(3, 3);
        float f{ 2.37f };
        for (auto row{ 0 }; row < arr2.height(); ++row) {
            for (auto col{ 0 }; col < arr2.width(); ++col) {
                arr2.at(row, col) = f;
                f *= 2;
            }
        }
        fmt::print(os, "arr2:\n{}\n\n", arr2);

        // Array initialized with a initializer list of initializer lists
        array_2d<std::string> arr3{
            { "En", "un", "lugar", "de" },
            { "la", "Mancha", "de", "cuyo" },
            { "nombre", "no", "quiero", "acordarme" },
            { "no", "ha", "mucho", "que" }
        };
        fmt::print(os, "arr3:\n{}\n\n", arr3);

        // Array initialized with move constructor
        auto arr4{ std::move(arr2) };
        fmt::print(os, "arr4 = move(arr2):\n{}\n\n", arr4);

        // Array initialized with copy constructor
        // Then modified using transform()
        // transform() uses difference_type operator-()
        auto arr5{ arr1 };
        std::transform(arr1.cbegin(), arr1.cend(), arr5.begin(), [](auto n) { return n + 1; });
        fmt::print(os, "arr5 = arr1 + 1:\n{}\n\n", arr5);
        fmt::print(os, "arr1:\n{}\n\n", arr1);

        // Swapping of elements
        arr5.swap(0, 0, 2, 2);
        fmt::print(os, "arr5 swapping (0, 0) with (2, 2):\n{}\n\n", arr5);

        // Sub arrays
        auto arr6{ arr3.sub_array(1, 1, 1, 2) };
        fmt::print(os, "subarr5 from (1, 1) to (1, 2):\n{}\n\n", arr6);

        // Rows and columns as vectors
        auto row2{ arr3.row_as_vector(2) };
        fmt::print(os, "row2 of arr3:\n{}\n\n", row2);
        auto col3{ arr3.column_as_vector(3) };
        fmt::print(os, "col3 of arr3:\n{}\n\n", col3);

        // Reverse iterators
        std::transform(arr1.crbegin(), arr1.crend(), arr5.begin(), [](auto n) { return n + 1; });
        fmt::print(os, "reverse arr5:\n{}\n\n", arr5);

        // Test out of range access
        arr5.swap(3, 0, 2, 2);
        fmt::print(os, "arr5 swapping (3, 0) with (2, 2):\n{}\n\n", arr5);
    } catch (const std::exception& err) {
        fmt::print(os, "Error: {}\n\n", err.what());
    }
}


// Creating a 2D array with basic operations
//
// Write a class template that represents a two-dimensional array container with methods for
// element access (at() and data()), capacity querying, iterators, filling, and swapping.
// It should be possible to move objects of this type.
void problem_17_main() {
    problem_17_main(std::cout);
}
