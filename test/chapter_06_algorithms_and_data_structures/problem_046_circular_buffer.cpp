#include "chapter_06_algorithms_and_data_structures/problem_046_circular_buffer.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <sstream>  // ostringstream


TEST(problem_46_main, output) {
    std::ostringstream oss{};
    problem_46_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "Error: trying to create a circular_buffer with a fixed size of 0.\n"
        "\n"
        "circular_buffer<double> cb_3(5);\n"
        "\tcb_3: [0, 0, 0, 0, 0], capacity: 5, size: 0\n"
        "\n"
        "cb_3.push_back(1);\n"
        "\tcb_3: [1, 0, 0, 0, 0], capacity: 5, size: 1, front: 1, back: 1\n"
        "cb_3.push_back(2);\n"
        "\tcb_3: [1, 2, 0, 0, 0], capacity: 5, size: 2, front: 1, back: 2\n"
        "cb_3.push_back(3);\n"
        "\tcb_3: [1, 2, 3, 0, 0], capacity: 5, size: 3, front: 1, back: 3\n"
        "cb_3.push_back(4);\n"
        "\tcb_3: [1, 2, 3, 4, 0], capacity: 5, size: 4, front: 1, back: 4\n"
        "cb_3.push_back(5);\n"
        "\tcb_3: [1, 2, 3, 4, 5], capacity: 5, size: 5, front: 1, back: 5\n"
        "cb_3.push_back(6);\n"
        "\tcb_3: [6, 2, 3, 4, 5], capacity: 5, size: 5, front: 2, back: 6\n"
        "\n"
        "cb_3.pop_front();\n"
        "\tcb_3: [6, 2, 3, 4, 5], capacity: 5, size: 4, front: 3, back: 6\n"
        "cb_3.pop_back();\n"
        "\tcb_3: [6, 2, 3, 4, 5], capacity: 5, size: 3, front: 3, back: 5\n"
        "\n"
        "cb_3.clear();\n"
        "\tcb_3: [6, 2, 3, 4, 5], capacity: 5, size: 0\n"
    ));
}
