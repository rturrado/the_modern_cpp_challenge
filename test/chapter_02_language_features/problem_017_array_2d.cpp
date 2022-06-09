#include "chapter_02_language_features/problem_017_array_2d.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_17_main, DISABLED_array_2d_basic_operations) {
    std::ostringstream oss{};
    problem_17_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "arr1:\n"
        "[ 1, 2, 3 ]\n"
        "[ 4, 5, 6 ]\n"
        "[ 7, 8, 9 ]\n"
        "\n"
        "arr2:\n"
        "[   2.37,   4.74,   9.48 ]\n"
        "[  18.96,  37.92,  75.84 ]\n"
        "[ 151.68, 303.36, 606.72 ]\n"
        "\n"
        "arr3:\n"
        "[     En,     un,  lugar,        de ]\n"
        "[     la, Mancha,     de,      cuyo ]\n"
        "[ nombre,     no, quiero, acordarme ]\n"
        "[     no,     ha,  mucho,       que ]\n"
        "\n"
        "arr4 = move(arr2):\n"
        "[   2.37,   4.74,   9.48 ]\n"
        "[  18.96,  37.92,  75.84 ]\n"
        "[ 151.68, 303.36, 606.72 ]\n"
        "\n"
        "arr5 = arr1 + 1:\n"
        "[ 2, 3,  4 ]\n"
        "[ 5, 6,  7 ]\n"
        "[ 8, 9, 10 ]\n"
        "\n"
        "arr1:\n"
        "[ 1, 2, 3 ]\n"
        "[ 4, 5, 6 ]\n"
        "[ 7, 8, 9 ]\n"
        "\n"
        "arr5 swapping (0, 0) with (2, 2):\n"
        "[ 10, 3, 4 ]\n"
        "[  5, 6, 7 ]\n"
        "[  8, 9, 2 ]\n"
        "\n"
        "subarr5 from (1, 1) to (1, 2):\n"
        "[ Mancha ]\n"
        "[     no ]\n"
        "\n"
        "row2 of arr3:\n"
        "[\"nombre\", \"no\", \"quiero\", \"acordarme\"]\n"
        "\n"
        "col3 of arr3:\n"
        "[\"de\", \"cuyo\", \"acordarme\", \"que\"]\n"
        "\n"
        "reverse arr5:\n"
        "[ 10, 9, 8 ]\n"
        "[  7, 6, 5 ]\n"
        "[  4, 3, 2 ]\n"
        "\n"
        "Error: left_row (zero based index) = 3 and height = 3.\n"
    ));
}
