#include "chapter_07_concurrency/problem_066_customer_service_system.h"

#include "rtc/console.h"  // read_positive_number

#include "fmt/ostream.h"

#include <iostream>  // cin, cout
#include <ostream>


void problem_66_main(std::istream& is, std::ostream& os) {
    using namespace rtc::console;
    using namespace tmcppc::office;

    size_t number_of_customers{ static_cast<size_t>(
        read_positive_number(is, os, "Please enter the number of customers (between 1 and 100): ", 1, 101)
    ) };
    size_t number_of_desks{ static_cast<size_t>(
        read_positive_number(is, os, "Please enter the number of desks (between 1 and 10): ", 1, 11)
    ) };

    office_simulator office_simulator{ number_of_customers, number_of_desks };
    office_simulator.run(os);

    fmt::print(os, "\n");
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
    problem_66_main(std::cin, std::cout);
}
