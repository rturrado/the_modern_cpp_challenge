#include "chapter_02_language_features/array_2d.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <fmt/ostream.h>
#include <fmt/ranges.h>
#include <sstream>  // ostringstream
#include <stdexcept>  // out_of_range
#include <string>
#include <vector>


TEST(array_2d, DISABLED_default_constructor) {
    tmcppc::array_2d<int> arr{};
    EXPECT_TRUE(arr.empty());
    EXPECT_EQ(arr.width(), static_cast<size_t>(0));
    EXPECT_EQ(arr.height(), static_cast<size_t>(0));
}
TEST(array_2d, DISABLED_width_height_constructor) {
    tmcppc::array_2d<int> arr{3, 3};
    EXPECT_FALSE(arr.empty());
    EXPECT_EQ(arr.width(), static_cast<size_t>(3));
    EXPECT_EQ(arr.height(), static_cast<size_t>(3));
}
TEST(array_2d, DISABLED_initializer_list_constructor) {
    tmcppc::array_2d<int> arr{ { 0, 1 }, { 2, 3 }, { 4, 5 } };
    EXPECT_FALSE(arr.empty());
    EXPECT_EQ(arr.width(), static_cast<size_t>(2));
    EXPECT_EQ(arr.height(), static_cast<size_t>(3));
}
TEST(array_2d, DISABLED_copy_constructor) {
    tmcppc::array_2d<int> arr1{ { 0, 1 }, { 2, 3 }, { 4, 5 } };
    auto arr2{ arr1 };
    EXPECT_EQ(arr1, arr2);
    EXPECT_NE(arr1.data(), arr2.data());
}
TEST(array_2d, DISABLED_copy_assignment_operator) {
    tmcppc::array_2d<int> arr1{ { 0, 1 }, { 2, 3 }, { 4, 5 } };
    tmcppc::array_2d<int> arr2{};
    arr2 = arr1;
    EXPECT_EQ(arr1, arr2);
    EXPECT_NE(arr1.data(), arr2.data());
}
TEST(array_2d, DISABLED_move_constructor) {
    tmcppc::array_2d<int> arr1{ { 0, 1 }, { 2, 3 }, { 4, 5 } };
    auto arr2{ std::move(arr1) };
    EXPECT_FALSE(arr2.empty());
    EXPECT_EQ(arr2.width(), static_cast<size_t>(2));
    EXPECT_EQ(arr2.height(), static_cast<size_t>(3));
    EXPECT_TRUE(arr1.empty());
    EXPECT_EQ(arr1.width(), static_cast<size_t>(0));
    EXPECT_EQ(arr1.height(), static_cast<size_t>(0));
}
TEST(array_2d, DISABLED_move_assignment_operator) {
    tmcppc::array_2d<int> arr1{ { 0, 1 }, { 2, 3 }, { 4, 5 } };
    tmcppc::array_2d<int> arr2{};
    arr2 = std::move(arr1);
    EXPECT_FALSE(arr2.empty());
    EXPECT_EQ(arr2.width(), static_cast<size_t>(2));
    EXPECT_EQ(arr2.height(), static_cast<size_t>(3));
    EXPECT_TRUE(arr1.empty());
    EXPECT_EQ(arr1.width(), static_cast<size_t>(0));
    EXPECT_EQ(arr1.height(), static_cast<size_t>(0));
}

TEST(array_2d, DISABLED_at) {
    tmcppc::array_2d<int> arr{ { 0, 1 }, { 2, 3 }, { 4, 5 } };
    EXPECT_EQ(arr.at(0, 0), 0);
    EXPECT_EQ(arr.at(0, 1), 1);
    EXPECT_EQ(arr.at(2, 1), 5);
    EXPECT_THROW((void) arr.at(0, 2), std::out_of_range);
    EXPECT_THROW((void) arr.at(3, 0), std::out_of_range);
}

TEST(array_2d, DISABLED_data) {
    tmcppc::array_2d<int> arr1{};
    EXPECT_EQ(arr1.data(), nullptr);
}
TEST(array_2d, DISABLED_const_data) {
    const tmcppc::array_2d<int> arr2{};
    EXPECT_EQ(arr2.data(), nullptr);
}

TEST(array_2d, DISABLED_empty) {
    tmcppc::array_2d<int> arr1{};
    EXPECT_TRUE(arr1.empty());
    tmcppc::array_2d<int> arr2{ { 0 } };
    EXPECT_FALSE(arr2.empty());
}
TEST(array_2d, DISABLED_height) {
    tmcppc::array_2d<int> arr1{};
    EXPECT_EQ(arr1.height(), 0);
    tmcppc::array_2d<int> arr2{ { 0 }, { 1 }, { 2 } };
    EXPECT_EQ(arr2.height(), 3);
}
TEST(array_2d, DISABLED_width) {
    tmcppc::array_2d<int> arr1{};
    EXPECT_EQ(arr1.width(), 0);
    tmcppc::array_2d<int> arr2{ { 0, 1, 2 } };
    EXPECT_EQ(arr2.width(), 3);
}

TEST(array_2d, DISABLED_begin) {
    tmcppc::array_2d<int> arr1{};
    EXPECT_EQ(arr1.begin(), arr1.end());
    tmcppc::array_2d<int> arr2{ { 0, 1 }, { 2, 3 }, { 4, 5 } };
    auto it{ arr2.begin() };
    EXPECT_EQ(*it, 0);
    *it = 5;
    EXPECT_EQ(*it, 5);
}
TEST(array_2d, DISABLED_end) {
    tmcppc::array_2d<int> arr{ { 0, 1 }, { 2, 3 }, { 4, 5 } };
    auto it{ arr.end() };
    EXPECT_EQ(*--it, 5);
}
TEST(array_2d, DISABLED_const_begin) {
    const tmcppc::array_2d<int> arr1{};
    EXPECT_EQ(arr1.begin(), arr1.end());
    const tmcppc::array_2d<int> arr2{ { 0, 1 }, { 2, 3 }, { 4, 5 } };
    auto it{ arr2.begin() };
    EXPECT_EQ(*it, 0);
}
TEST(array_2d, DISABLED_const_end) {
    const tmcppc::array_2d<int> arr{ { 0, 1 }, { 2, 3 }, { 4, 5 } };
    auto it{ arr.end() };
    EXPECT_EQ(*--it, 5);
}
TEST(array_2d, DISABLED_cbegin) {
    tmcppc::array_2d<int> arr1{};
    EXPECT_EQ(arr1.cbegin(), arr1.cend());
    tmcppc::array_2d<int> arr2{ { 0, 1 }, { 2, 3 }, { 4, 5 } };
    auto it{ arr2.cbegin() };
    EXPECT_EQ(*it, 0);
}
TEST(array_2d, DISABLED_cend) {
    tmcppc::array_2d<int> arr{ { 0, 1 }, { 2, 3 }, { 4, 5 } };
    auto it{ arr.cend() };
    EXPECT_EQ(*--it, 5);
}
TEST(array_2d, DISABLED_const_cbegin) {
    const tmcppc::array_2d<int> arr1{};
    EXPECT_EQ(arr1.cbegin(), arr1.cend());
    const tmcppc::array_2d<int> arr2{ { 0, 1 }, { 2, 3 }, { 4, 5 } };
    auto it{ arr2.cbegin() };
    EXPECT_EQ(*it, 0);
}
TEST(array_2d, DISABLED_const_cend) {
    const tmcppc::array_2d<int> arr{ { 0, 1 }, { 2, 3 }, { 4, 5 } };
    auto it{ arr.cend() };
    EXPECT_EQ(*--it, 5);
}

TEST(array_2d, DISABLED_rbegin) {
    tmcppc::array_2d<int> arr1{};
    EXPECT_EQ(arr1.rbegin(), arr1.rend());
    tmcppc::array_2d<int> arr2{ { 0, 1 }, { 2, 3 }, { 4, 5 } };
    auto it{ arr2.rbegin() };
    EXPECT_EQ(*it, 5);
    *it = 6;
    EXPECT_EQ(*it, 6);
}
TEST(array_2d, DISABLED_rend) {
    tmcppc::array_2d<int> arr{ { 0, 1 }, { 2, 3 }, { 4, 5 } };
    auto it{ arr.rend() };
    EXPECT_EQ(*--it, 0);
}
TEST(array_2d, DISABLED_const_rbegin) {
    const tmcppc::array_2d<int> arr1{};
    EXPECT_EQ(arr1.rbegin(), arr1.rend());
    const tmcppc::array_2d<int> arr2{ { 0, 1 }, { 2, 3 }, { 4, 5 } };
    auto it{ arr2.rbegin() };
    EXPECT_EQ(*it, 5);
}
TEST(array_2d, DISABLED_const_rend) {
    const tmcppc::array_2d<int> arr{ { 0, 1 }, { 2, 3 }, { 4, 5 } };
    auto it{ arr.rend() };
    EXPECT_EQ(*--it, 0);
}
TEST(array_2d, DISABLED_crbegin) {
    tmcppc::array_2d<int> arr1{};
    EXPECT_EQ(arr1.crbegin(), arr1.crend());
    tmcppc::array_2d<int> arr2{ { 0, 1 }, { 2, 3 }, { 4, 5 } };
    auto it{ arr2.crbegin() };
    EXPECT_EQ(*it, 5);
}
TEST(array_2d, DISABLED_crend) {
    tmcppc::array_2d<int> arr{ { 0, 1 }, { 2, 3 }, { 4, 5 } };
    auto it{ arr.crend() };
    EXPECT_EQ(*--it, 0);
}
TEST(array_2d, DISABLED_const_crbegin) {
    const tmcppc::array_2d<int> arr1{};
    EXPECT_EQ(arr1.crbegin(), arr1.crend());
    const tmcppc::array_2d<int> arr2{ { 0, 1 }, { 2, 3 }, { 4, 5 } };
    auto it{ arr2.crbegin() };
    EXPECT_EQ(*it, 5);
}
TEST(array_2d, DISABLED_const_crend) {
    const tmcppc::array_2d<int> arr{ { 0, 1 }, { 2, 3 }, { 4, 5 } };
    auto it{ arr.crend() };
    EXPECT_EQ(*--it, 0);
}

TEST(array_2d, DISABLED_operator_spaceship) {
    const tmcppc::array_2d<int> arr1{ { 0, 1 }, { 2, 3 }, { 4, 5 } };
    const tmcppc::array_2d<int> arr2{ { 0, 1 }, { 2, 3 }, { 4, 5 } };
    const tmcppc::array_2d<int> arr3{ { 0, 1 }, { 7, 8 }, { 4, 5 } };
    EXPECT_TRUE(arr1 == arr2);
    EXPECT_TRUE(arr1 != arr3);
    EXPECT_TRUE(arr1 < arr3);
    EXPECT_TRUE(arr3 > arr1);
    EXPECT_TRUE(arr1 <= arr2);
    EXPECT_TRUE(arr1 <= arr3);
    EXPECT_TRUE(arr2 >= arr1);
    EXPECT_TRUE(arr3 >= arr1);
}

TEST(array_2d, DISABLED_swap) {
    tmcppc::array_2d<int> arr{ { 0, 1 }, { 2, 3 }, { 4, 5 } };
    arr.swap(1, 0, 1, 1);
    EXPECT_EQ(arr.at(1, 0), 3);
    EXPECT_EQ(arr.at(1, 1), 2);
    EXPECT_THROW(arr.swap(1, 2, 1, 1), std::out_of_range);
    EXPECT_THROW(arr.swap(3, 0, 1, 1), std::out_of_range);
}

TEST(array_2d, DISABLED_sub_array) {
    tmcppc::array_2d<int> arr{
        { 0, 1 },
        { 2, 3 },
        { 4, 5 }
    };
    tmcppc::array_2d<int> subarr{ { 2, 3 } };
    EXPECT_EQ(arr.sub_array(1, 0, 2, 1), subarr);
    EXPECT_THROW((void) arr.sub_array(1, 2, 2, 1), std::out_of_range);
    EXPECT_THROW((void) arr.sub_array(3, 0, 2, 1), std::out_of_range);
}

TEST(array_2d, DISABLED_row_as_vector) {
    const tmcppc::array_2d<int> arr{ { 0, 1 }, { 2, 3 }, { 4, 5 } };
    auto row{ std::vector<int>{2, 3} };
    EXPECT_EQ(arr.row_as_vector(1), row);
    EXPECT_THROW((void) arr.row_as_vector(3), std::out_of_range);
}
TEST(array_2d, DISABLED_column_as_vector) {
    const tmcppc::array_2d<int> arr{ { 0, 1 }, { 2, 3 }, { 4, 5 } };
    auto col{ std::vector<int>{1, 3, 5} };
    EXPECT_EQ(arr.column_as_vector(1), col);
    EXPECT_THROW((void) arr.column_as_vector(2), std::out_of_range);
}

TEST(array_2d, DISABLED_get_column_width) {
    const tmcppc::array_2d<std::string> arr{ { "En", "un", "lugar" }, { "de", "la", "Mancha" } };
    EXPECT_EQ(get_column_width(arr, 0), 2);
    EXPECT_EQ(get_column_width(arr, 2), 6);
    EXPECT_THROW((void) get_column_width(arr, 3), std::out_of_range);
}
TEST(array_2d, DISABLED_get_column_widths) {
    const tmcppc::array_2d<std::string> arr{ { "En", "un", "lugar" }, { "de", "la", "Mancha" } };
    auto ws{ get_column_widths(arr) };
    EXPECT_EQ(ws[0], 2);
    EXPECT_EQ(ws[2], 6);
    EXPECT_THROW((void) ws.at(3), std::out_of_range);
}

TEST(array_2d, DISABLED_operator_insertion) {
    const tmcppc::array_2d<std::string> arr{ { "En", "un", "lugar" }, { "de", "la", "Mancha" } };
    std::ostringstream oss{};
    oss << arr;
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "[ En, un,  lugar ]\n"
        "[ de, la, Mancha ]"
    ));
}
TEST(array_2d, DISABLED_fmt_print) {
    const tmcppc::array_2d<std::string> arr{ { "En", "un", "lugar" }, { "de", "la", "Mancha" } };
    std::ostringstream oss{};
    fmt::print(oss, "{}", arr);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "[ En, un,  lugar ]\n"
        "[ de, la, Mancha ]"
    ));
}
