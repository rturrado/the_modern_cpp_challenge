#include "chapter_06_algorithms_and_data_structures/double_buffer.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <stdexcept>  // out_of_range

using tmcppc::data_structures::double_buffer;
template<typename T>
using container = double_buffer<T>::container;


TEST(double_buffer, size) {
    EXPECT_EQ(double_buffer<int>{ 5 }.size(), 5);
}
TEST(double_buffer, write_on_zero_capacity_buffer) {
    EXPECT_THROW(double_buffer<int>{ 0 }.write(0, container<int>{ 1, 2, 3 }), std::out_of_range);
}
TEST(double_buffer, read_on_zero_capacity_buffer) {
    EXPECT_THROW((void) double_buffer<int>{ 0 }.read(0, 3), std::out_of_range);
}
TEST(double_buffer, read_after_no_write) {
    double_buffer<int> db{ 5 };
    EXPECT_THAT(db.read(0, 5), ::testing::ElementsAre(0, 0, 0, 0, 0));
}
TEST(double_buffer, read_after_write) {
    double_buffer<int> db{ 5 };
    db.write(0, container<int>{ 1, 2, 3, 4, 5 });
    EXPECT_THAT(db.read(0, 5), ::testing::ElementsAre(1, 2, 3, 4, 5));
}
TEST(double_buffer, read_after_two_writes) {
    double_buffer<int> db{ 5 };
    db.write(0, container<int>{ 1, 2, 3, 4, 5 });
    db.write(0, container<int>{ 6, 7, 8, 9, 10 });
    EXPECT_THAT(db.read(0, 5), ::testing::ElementsAre(6, 7, 8, 9, 10));
}
TEST(double_buffer, read_after_three_writes) {
    double_buffer<int> db{ 5 };
    db.write(0, container<int>{ 1, 2, 3, 4, 5 });
    db.write(0, container<int>{ 6, 7, 8, 9, 10 });
    db.write(3, container<int>{ 11, 12 });
    EXPECT_THAT(db.read(0, 5), ::testing::ElementsAre(1, 2, 3, 11, 12));
}
