#include "chapter_07_concurrency/problem_066_customer_service_system.h"

#include <fmt/format.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // istringstream, ostringstream

using namespace tmcppc::office;


TEST(ticketing_machine, DISABLED_get_ticket_number) {
    ticketing_machine tm{};
    EXPECT_EQ(tm.get_ticket_number(), 1);
    EXPECT_EQ(tm.get_ticket_number(), 2);
    EXPECT_EQ(tm.get_ticket_number(), 3);
}

TEST(office_simulator, DISABLED_one_client_one_desk) {
    office_simulator office_simulator{ 1, 1 };
    std::ostringstream oss{};
    office_simulator.run(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(fmt::format("Desk 1: started\n")));
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(fmt::format("Desk 1: finished\n")));
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(fmt::format("Customer 1: started\n")));
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(fmt::format("Customer 1: got to the office\n")));
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(fmt::format("Customer 1: got ticket number 1\n")));
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(fmt::format("Customer 1: waiting for service number\n")));
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(fmt::format("Customer 1: is being served\n")));
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(fmt::format("Desk 1: about to serve customer 1\n")));
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(fmt::format("Desk 1: just served customer 1\n")));
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(fmt::format("Customer 1: finished\n")));
}

TEST(office_simulator, DISABLED_ten_clients_one_desk) {
    size_t number_of_customers{ 10 };
    size_t number_of_desks{ 1 };
    office_simulator office_simulator{ number_of_customers, number_of_desks };
    std::ostringstream oss{};
    office_simulator.run(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(fmt::format("Desk 1: started\n")));
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(fmt::format("Desk 1: finished\n")));
    for (auto i{ 1 }; i <= number_of_customers; ++i) {
        EXPECT_THAT(oss.str(), ::testing::HasSubstr(fmt::format("Customer {}: started\n", i)));
        EXPECT_THAT(oss.str(), ::testing::HasSubstr(fmt::format("Customer {}: got to the office\n", i)));
        EXPECT_THAT(oss.str(), ::testing::ContainsRegex(fmt::format("Customer {}: got ticket number \\d+\n", i)));
        EXPECT_THAT(oss.str(), ::testing::HasSubstr(fmt::format("Customer {}: waiting for service number\n", i)));
        EXPECT_THAT(oss.str(), ::testing::HasSubstr(fmt::format("Customer {}: is being served\n", i)));
        EXPECT_THAT(oss.str(), ::testing::HasSubstr(fmt::format("Desk 1: about to serve customer {}\n", i)));
        EXPECT_THAT(oss.str(), ::testing::HasSubstr(fmt::format("Desk 1: just served customer {}\n", i)));
        EXPECT_THAT(oss.str(), ::testing::HasSubstr(fmt::format("Customer {}: finished\n", i)));
    }
}

TEST(problem_66_main, DISABLED_output) {
    size_t number_of_customers{ 7 };
    size_t number_of_desks{ 3 };
    std::istringstream iss{ "7\n3\n" };
    std::ostringstream oss{};
    problem_66_main(iss, oss);
    for (auto i{ 1 }; i <= number_of_desks; ++i) {
        EXPECT_THAT(oss.str(), ::testing::HasSubstr(fmt::format("Desk {}: started\n", i)));
        EXPECT_THAT(oss.str(), ::testing::HasSubstr(fmt::format("Desk {}: finished\n", i)));
    }
    for (auto i{ 1 }; i <= number_of_customers; ++i) {
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
