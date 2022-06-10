#include "chapter_07_concurrency/logger.h"
#include "chapter_07_concurrency/problem_066_customer_service_system.h"

#include <chrono>  // milliseconds
#include <iostream>  // cout
#include <ostream>
#include <random>  // default_random_engine, random_device, uniform_int_distribution
#include <stop_token>
#include <thread>  // jthread, sleep_for
#include <vector>


void problem_66_main(std::ostream& os) {
    using namespace tmcppc::logging::v2;
    using namespace tmcppc::office;

    auto sleep_for = [](int min, int max) {
        std::default_random_engine random_engine{ std::random_device{}() };
        std::uniform_int_distribution<int> uniform_dist{ min, max };
        std::chrono::milliseconds t{ uniform_dist(random_engine) };
        std::this_thread::sleep_for(t);
    };

    auto customer = [&os, &sleep_for](int id) {
        office& office{ office::get_instance() };
        logger& logger{ logger::get_instance() };

        logger.log(os, "\tCustomer ", id, ": started\n");

        sleep_for(100, 1200);  // time to get to the office
        logger.log(os, "\tCustomer ", id, ": got to the office\n");

        auto ticket_number{ office.customer_gets_ticket_number() };
        logger.log(os, "\tCustomer ", id, ": got ticket number ", ticket_number, "\n");

        logger.log(os, "\tCustomer ", id, ": waiting for service number\n");
        office.customer_waits_for_service_number(id, ticket_number);

        logger.log(os, "\tCustomer ", id, ": is being served\n");
        office.customer_waits_until_end_of_service(id);

        logger.log(os, "\tCustomer ", id, ": finished\n");
    };

    auto desk = [&os, &sleep_for](std::stop_token stoken, int id) {
        office& office{ office::get_instance() };
        logger& logger{ logger::get_instance() };

        logger.log(os, "Desk ", id, ": started\n");

        for (;;) {
            auto customer_id{ office.desk_waits_until_customer_is_ready_to_be_served(stoken) };
            if (stoken.stop_requested()) {
                break;
            }
            logger.log(os, "Desk ", id, ": about to serve customer ", customer_id, "\n");
            sleep_for(50, 200);  // time to serve the customer
            logger.log(os, "Desk ", id, ": just served customer ", customer_id, "\n");
            office.desk_notifies_a_customer_has_been_served(customer_id);
        }

        logger.log(os, "Desk ", id, ": finished\n");
    };

    std::vector<std::jthread> customers{};
    std::vector<std::jthread> desks{};
    office& office{ office::get_instance() };
    for (auto i{ 1 }; i <= office.get_number_of_desks(); ++i) {
        desks.emplace_back(desk, i);
    }
    for (auto i{ 1 }; i <= office.get_number_of_customers(); ++i) {
        customers.emplace_back(customer, i);
    }
    std::for_each(std::begin(customers), std::end(customers), [](auto& t) { t.join(); });
    std::for_each(std::begin(desks), std::end(desks), [](auto& t) { t.request_stop(); });
    std::for_each(std::begin(desks), std::end(desks), [](auto& t) { t.join(); });

    os << "\n";
}


// Customer service system
//
// Write a program that simulates the way customers are served in an office.
// The office has three desks where customers can be served at the same time.
// Customers can enter the office at any time.
// They take a ticket with a service number from a ticketing machine and
// wait until their number is next for service at one of the desks.
// Customers are served in the order they entered the office, or more precisely,
// in the order given by their ticket.
// Every time a service desk finishes serving a customer, the next customer in order is served.
// The simulation should stop after a particular number of customers have been issued tickets and served.
void problem_66_main() {
    problem_66_main(std::cout);
}
