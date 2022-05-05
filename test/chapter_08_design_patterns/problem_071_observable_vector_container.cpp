#include "chapter_08_design_patterns/problem_071_observable_vector_container.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_71_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_71_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "Creating the observable vectors:\n"
        "\tov_0: []\n"
        "\tov_1: [0, 3.14, 6.28, 9.42, 12.56]\n"
        "\tov_2: [1.5, 1.5, 1.5]\n"
        "\tov_3: ['o', ',', ' ', 'u']\n"
        "\tov_4: []\n"
        "\n"
        "Pushing back to ov_0:\n"
        "\t[observer 0] received notification: <id : 0, type : push_back(0)>\n"
        "\t[observer 0] observable vector 0: [\"Tush! Never tell me;\"]\n"
        "\t[observer 0] received notification: <id : 1, type : push_back(1)>\n"
        "\t[observer 0] observable vector 0: [\"Tush! Never tell me;\", \"I take it much unkindly.\"]\n"
        "\n"
        "Copy assigning from ov_3:\n"
        "Popping back from the copied-to vector:\n"
        "\n"
        "Move assigning from ov_1:\n"
        "Pushing back to the moved-to vector:\n"
        "\n"
        "Copy assigning to ov_3:\n"
        "\t[observer 3] received notification: <id : 2, type : copy_assignment()>\n"
        "\t[observer 3] observable vector 3: ['o', ',', ' ']\n"
        "\n"
        "Move assigning to ov_4:\n"
        "\t[observer 4] received notification: <id : 3, type : move_assignment()>\n"
        "\t[observer 4] sum of elements of observable vector 4: 12\n"
        "\n"
        "Detaching from ov_0:\n"
        "Pushing back to ov_0:\n"
    ));
}
