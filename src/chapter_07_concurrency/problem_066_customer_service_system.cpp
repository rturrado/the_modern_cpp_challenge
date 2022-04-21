#include "Chapter7_Concurrency.h"
#include "RtcPrint.h"  // printable

#include <chrono>  // milliseconds
#include <condition_variable>  // condition_variable_any
#include <mutex>
#include <iostream>  // cout
#include <queue>
#include <random>  // default_random_engine, random_device, uniform_int_distribution
#include <thread>  // lock_guard, sleep_for, unique_lock
#include <vector>


class Logger
{
public:
    static Logger& get_instance()
    {
        static Logger instance;
        return instance;
    }

    Logger(const Logger& rhs) = delete;
    Logger(Logger&& rhs) = delete;
    Logger& operator=(const Logger& rhs) = delete;
    Logger& operator=(Logger&& rhs) = delete;

    // Let's print a variadic list of printable arguments instead
    void log(printable auto ... messages)
    {
        std::lock_guard<std::mutex> lock(m_);
        (std::cout << ... << messages);
    }

private:
    std::mutex m_{};

    Logger() {}
};


class TicketingMachine
{
public:
    TicketingMachine(const TicketingMachine& other) = delete;
    TicketingMachine& operator=(const TicketingMachine& other) = delete;

    static TicketingMachine& get_instance() { static TicketingMachine instance; return instance; }

    auto get_ticket_number() { std::lock_guard<std::mutex> lock{ m_ }; return ticket_number_++; }

protected:
    TicketingMachine() {}

private:
    size_t ticket_number_{ 1 };
    std::mutex m_{};
};


class Office
{
private:

public:
    Office(const Office& other) = delete;
    Office& operator=(const Office& other) = delete;

    static Office& get_instance() { static Office instance; return instance; }

    constexpr size_t get_number_of_customers() { return number_of_customers_; }
    constexpr size_t get_number_of_desks() { return number_of_desks_; }

    // Ticket number
    auto customer_gets_ticket_number() { return ticketing_machine_.get_ticket_number(); }

    // Service number
    void customer_waits_for_service_number(size_t customer_id, size_t ticket_number)
    {
        std::unique_lock<std::mutex> lock{ m_service_number_ };
        cv_service_number_.wait(lock, [this, ticket_number] { return service_number_ == ticket_number; });

        lock.unlock();
        add_customer_ready_to_be_served(customer_id);
    }

    // Customers ready to be served
    auto desk_waits_until_customer_is_ready_to_be_served(std::stop_token stoken)
    {
        std::unique_lock<std::mutex> lock{ m_customers_ready_to_be_served_ };
        cva_customers_ready_to_be_served_.wait(lock, stoken, [this] { return not customers_ready_to_be_served_.empty(); });
        if (stoken.stop_requested()) { return size_t{}; }

        lock.unlock();
        increment_service_number();

        auto ret{ customers_ready_to_be_served_.front() };
        customers_ready_to_be_served_.pop();
        return ret;
    }

    // Customers served
    void desk_notifies_a_customer_has_been_served(size_t customer_id)
    {
        std::unique_lock<std::mutex> lock{ m_customers_served_ };
        customers_served_.push_back(customer_id);
        cv_customers_served_.notify_all();  // notify all customers
    }
    void customer_waits_until_end_of_service(size_t customer_id)
    {
        std::unique_lock<std::mutex> lock{ m_customers_served_ };
        cv_customers_served_.wait(lock, [this, customer_id] {
            return std::binary_search(std::begin(customers_served_), std::end(customers_served_), customer_id); });
        customers_served_.erase(std::find(std::begin(customers_served_), std::end(customers_served_), customer_id));
    }

protected:
    Office() {}

private:
    const size_t number_of_customers_{ 7 };
    const size_t number_of_desks_{ 3 };

    TicketingMachine& ticketing_machine_{ TicketingMachine::get_instance() };

    // Service number
    size_t service_number_{ 1 };
    std::condition_variable cv_service_number_{};
    std::mutex m_service_number_{};

    // Customers ready to be served
    std::queue<size_t> customers_ready_to_be_served_{};
    std::condition_variable_any cva_customers_ready_to_be_served_{};
    std::mutex m_customers_ready_to_be_served_{};

    // Customers served
    std::vector<size_t> customers_served_{};
    std::condition_variable cv_customers_served_{};
    std::mutex m_customers_served_{};

private:
    // Service number
    void increment_service_number()
    {
        std::unique_lock<std::mutex> lock{ m_service_number_ };
        service_number_++;
        cv_service_number_.notify_all();  // notify all customers
    }

    // Customers ready to be served
    void add_customer_ready_to_be_served(size_t customer_id)
    {
        std::unique_lock<std::mutex> lock{ m_customers_ready_to_be_served_ };
        customers_ready_to_be_served_.push(customer_id);
        cva_customers_ready_to_be_served_.notify_one();  // notify one desk
    }
};


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
void problem_66_main()
{
    auto sleep_for = [](int min, int max) {
        std::default_random_engine random_engine{ std::random_device{}() }; 
        std::uniform_int_distribution<int> uniform_dist{ min, max };
        std::chrono::milliseconds t{ uniform_dist(random_engine) };
        std::this_thread::sleep_for(t);
    };

    auto customer = [&sleep_for](int id) {
        Office& office{ Office::get_instance() };
        Logger& logger{ Logger::get_instance() };

        logger.log("\tCustomer ", id, ": started\n");

        sleep_for(100, 1200);  // time to get to the office
        logger.log("\tCustomer ", id, ": got to the office\n");

        auto ticket_number{ office.customer_gets_ticket_number() };
        logger.log("\tCustomer ", id, ": got ticket number ", ticket_number, "\n");

        logger.log("\tCustomer ", id, ": waiting for service number\n");
        office.customer_waits_for_service_number(id, ticket_number);

        logger.log("\tCustomer ", id, ": is being served\n");
        office.customer_waits_until_end_of_service(id);

        logger.log("\tCustomer ", id, ": finished\n");
    };

    auto desk = [&sleep_for](std::stop_token stoken, int id) {
        Office& office{ Office::get_instance() };
        Logger& logger{ Logger::get_instance() };

        logger.log("Desk ", id, ": started\n");

        for (;;)
        {
            auto customer_id{ office.desk_waits_until_customer_is_ready_to_be_served(stoken) };
            if (stoken.stop_requested()) { break; }
            logger.log("Desk ", id, ": about to serve customer ", customer_id, "\n");
            sleep_for(50, 200);  // time to serve the customer
            logger.log("Desk ", id, ": just served customer ", customer_id, "\n");
            office.desk_notifies_a_customer_has_been_served(customer_id);
        }

        logger.log("Desk ", id, ": finished\n");
    };

    std::vector<std::jthread> customers{};
    std::vector<std::jthread> desks{};
    Office& office{ Office::get_instance() };
    for (auto i{ 1 }; i <= office.get_number_of_desks(); ++i) { desks.emplace_back(desk, i); }
    for (auto i{ 1 }; i <= office.get_number_of_customers(); ++i) { customers.emplace_back(customer, i); }
    std::for_each(std::begin(customers), std::end(customers), [](auto& t) { t.join(); });
    std::for_each(std::begin(desks), std::end(desks), [](auto& t) { t.request_stop(); });
    std::for_each(std::begin(desks), std::end(desks), [](auto& t) { t.join(); });

    std::cout << "\n";
}
