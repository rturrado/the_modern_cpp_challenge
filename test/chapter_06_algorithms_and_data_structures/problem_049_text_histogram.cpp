#include "chapter_06_algorithms_and_data_structures/problem_049_text_histogram.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

using namespace tmcppc::problem_49;


TEST(count_letters, empty_text) {
    EXPECT_TRUE(count_letters("").empty());
}
TEST(count_letters, text) {
    auto result{ count_letters("We find ourselves only by looking to what we're not.") };
    EXPECT_THAT(result, ::testing::UnorderedElementsAre(
        std::pair<char, size_t>{ 'W', 1 },
        std::pair<char, size_t>{ 'a', 1 },
        std::pair<char, size_t>{ 'b', 1 },
        std::pair<char, size_t>{ 'd', 1 },
        std::pair<char, size_t>{ 'e', 5 },
        std::pair<char, size_t>{ 'f', 1 },
        std::pair<char, size_t>{ 'g', 1 },
        std::pair<char, size_t>{ 'h', 1 },
        std::pair<char, size_t>{ 'i', 2 },
        std::pair<char, size_t>{ 'k', 1 },
        std::pair<char, size_t>{ 'l', 3 },
        std::pair<char, size_t>{ 'n', 4 },
        std::pair<char, size_t>{ 'o', 6 },
        std::pair<char, size_t>{ 'r', 2 },
        std::pair<char, size_t>{ 's', 2 },
        std::pair<char, size_t>{ 't', 3 },
        std::pair<char, size_t>{ 'u', 1 },
        std::pair<char, size_t>{ 'v', 1 },
        std::pair<char, size_t>{ 'w', 2 },
        std::pair<char, size_t>{ 'y', 2 }
    ));
}


TEST(print_histogram, empty_counts) {
    std::ostringstream oss{};
    print_histogram(oss, letter_counts{});
    EXPECT_TRUE(oss.str().empty());
}
TEST(print_histogram, counts_has_only_one_entry) {
    std::ostringstream oss{};
    letter_counts counts{ { 'a', 1 } };
    print_histogram(oss, counts);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "a (100.00 %) "
        "===================================================================================================="
        "===================================================================================================="
        "======================================================================================>\n"
    ));
}
TEST(print_histogram, counts_has_three_entries) {
    std::ostringstream oss{};
    letter_counts counts{ { 'a', 1 }, { 'b', 1 }, { 'c', 1 } };
    print_histogram(oss, counts);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "a ( 33.33 %) "
        "==============================================================================================>\n"
        "b ( 33.33 %) "
        "==============================================================================================>\n"
        "c ( 33.33 %) "
        "==============================================================================================>\n"
    ));
}
TEST(print_histogram, counts_has_four_entries) {
    std::ostringstream oss{};
    letter_counts counts{ { 'H', 1 }, { 'e', 1 }, { 'l', 2 }, { 'o', 1 } };
    print_histogram(oss, counts);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "H ( 20.00 %) ========================================================>\n"
        "e ( 20.00 %) ========================================================>\n"
        "l ( 40.00 %) ========================================================="
                     "========================================================>\n"
        "o ( 20.00 %) ========================================================>\n"
    ));
}


TEST(problem_49_main, output) {
    std::ostringstream oss{};
    problem_49_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "A (  0.21 %) >\n"
        "B (  0.09 %) >\n"
        "D (  0.01 %) >\n"
        "E (  0.03 %) >\n"
        "F (  0.01 %) >\n"
        "H (  0.20 %) >\n"
        "I (  0.29 %) >\n"
        "J (  0.01 %) >\n"
        "L (  0.01 %) >\n"
        "M (  0.13 %) >\n"
        "N (  0.07 %) >\n"
        "O (  0.04 %) >\n"
        "P (  0.09 %) >\n"
        "Q (  0.32 %) >\n"
        "S (  0.01 %) >\n"
        "T (  0.23 %) >\n"
        "W (  0.45 %) >\n"
        "Y (  0.08 %) >\n"
        "a (  7.67 %) =====================>\n"
        "b (  1.56 %) ===>\n"
        "c (  1.84 %) ====>\n"
        "d (  3.89 %) ==========>\n"
        "e ( 13.27 %) =====================================>\n"
        "f (  2.21 %) =====>\n"
        "g (  1.93 %) ====>\n"
        "h (  7.09 %) ===================>\n"
        "i (  6.85 %) ==================>\n"
        "j (  0.01 %) >\n"
        "k (  0.92 %) =>\n"
        "l (  4.20 %) ===========>\n"
        "m (  2.52 %) ======>\n"
        "n (  7.84 %) =====================>\n"
        "o (  7.23 %) ===================>\n"
        "p (  1.27 %) ==>\n"
        "q (  0.11 %) >\n"
        "r (  4.91 %) =============>\n"
        "s (  5.62 %) ===============>\n"
        "t (  9.04 %) ========================>\n"
        "u (  2.48 %) ======>\n"
        "v (  1.13 %) ==>\n"
        "w (  2.54 %) ======>\n"
        "x (  0.15 %) >\n"
        "y (  1.41 %) ===>\n"
        "z (  0.01 %) >\n"
    ));
}
