#include "chapter_07_concurrency/problem_066_customer_service_system.h"

#include <fmt/format.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream

using namespace tmcppc::office;


TEST(problem_66_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_66_main(oss);
    for (auto i{ 1 }; i <= office::get_instance().get_number_of_desks(); ++i) {
        EXPECT_THAT(oss.str(), ::testing::HasSubstr(fmt::format("Desk {}: started\n", i)));
        EXPECT_THAT(oss.str(), ::testing::HasSubstr(fmt::format("Desk {}: finished\n", i)));
    }
    for (auto i{ 1 }; i <= office::get_instance().get_number_of_customers(); ++i) {
        EXPECT_THAT(oss.str(), ::testing::HasSubstr(fmt::format("Customer {}: started\n", i)));
        EXPECT_THAT(oss.str(), ::testing::HasSubstr(fmt::format("Customer {}: got to the office\n", i)));
        EXPECT_THAT(oss.str(), ::testing::ContainsRegex(fmt::format("Customer {}: got ticket number \\d\n", i)));
        EXPECT_THAT(oss.str(), ::testing::HasSubstr(fmt::format("Customer {}: waiting for service number\n", i)));
        EXPECT_THAT(oss.str(), ::testing::HasSubstr(fmt::format("Customer {}: is being served\n", i)));
        EXPECT_THAT(oss.str(), ::testing::ContainsRegex(fmt::format("Desk \\d: about to serve customer {}\n", i)));
        EXPECT_THAT(oss.str(), ::testing::ContainsRegex(fmt::format("Desk \\d: just served customer {}\n", i)));
        EXPECT_THAT(oss.str(), ::testing::HasSubstr(fmt::format("Customer {}: finished\n", i)));
    }
}
