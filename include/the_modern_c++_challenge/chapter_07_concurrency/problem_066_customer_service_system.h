#pragma once

#include "chapter_07_concurrency/logger.h"

#include <chrono>  // milliseconds
#include <condition_variable>  // condition_variable_any
#include <iosfwd>
#include <mutex>  // lock_guard, unique_lock
#include <ostream>
#include <queue>
#include <rtc/random.h>  // random_int
#include <stop_token>
#include <thread>  // jthread, sleep_for
#include <vector>


namespace tmcppc::office {
    using tmcppc::logging::v2::logger;


    // Ticketing machine
    //
    class ticketing_machine {
    public:
        ticketing_machine() = default;
        ticketing_machine(const ticketing_machine& other) = delete;
        ticketing_machine& operator=(const ticketing_machine& other) = delete;

        auto get_ticket_number() {
            std::lock_guard<std::mutex> lock{ m_ };
            return ticket_number_++;
        }

    private:
        size_t ticket_number_{ 1 };
        std::mutex m_{};
    };


    // Office
    //
    class office {
    public:
        office(size_t number_of_customers, size_t number_of_desks)
            : number_of_customers_{ number_of_customers }
            , number_of_desks_{ number_of_desks }
        {}
        office(const office& other) = delete;
        office& operator=(const office& other) = delete;

        [[nodiscard]] constexpr size_t get_number_of_customers() const { return number_of_customers_; }
        [[nodiscard]] constexpr size_t get_number_of_desks() const { return number_of_desks_; }

        // Ticket number
        auto customer_gets_ticket_number() { return ticketing_machine_.get_ticket_number(); }

        // Service number
        void customer_waits_for_service_number(size_t customer_id, size_t ticket_number) {
            std::unique_lock<std::mutex> lock{ m_service_number_ };
            cv_service_number_.wait(lock, [this, ticket_number] {
                return service_number_ == ticket_number;
            });

            lock.unlock();
            add_customer_ready_to_be_served(customer_id);
        }

        // Customers ready to be served
        auto desk_waits_until_customer_is_ready_to_be_served(std::stop_token stoken) {
            std::unique_lock<std::mutex> lock{ m_customers_ready_to_be_served_ };
            cva_customers_ready_to_be_served_.wait(lock, stoken, [this] {
                return not customers_ready_to_be_served_.empty();
            });
            if (stoken.stop_requested()) {
                return size_t{};
            }

            lock.unlock();
            increment_service_number();

            auto ret{ customers_ready_to_be_served_.front() };
            customers_ready_to_be_served_.pop();
            return ret;
        }

        // Customers served
        void desk_notifies_a_customer_has_been_served(size_t customer_id) {
            std::unique_lock<std::mutex> lock{ m_customers_served_ };
            customers_served_.push_back(customer_id);
            cv_customers_served_.notify_all();  // notify all customers
        }
        void customer_waits_until_end_of_service(size_t customer_id) {
            std::unique_lock<std::mutex> lock{ m_customers_served_ };
            cv_customers_served_.wait(lock, [this, customer_id] {
                return std::ranges::binary_search(customers_served_, customer_id);
            });
            customers_served_.erase(std::ranges::find(customers_served_, customer_id));
        }

    private:
        size_t number_of_customers_{};
        size_t number_of_desks_{};
        ticketing_machine ticketing_machine_{};

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
        void increment_service_number() {
            std::unique_lock<std::mutex> lock{ m_service_number_ };
            service_number_++;
            cv_service_number_.notify_all();  // notify all customers
        }

        // Customers ready to be served
        void add_customer_ready_to_be_served(size_t customer_id) {
            std::unique_lock<std::mutex> lock{ m_customers_ready_to_be_served_ };
            customers_ready_to_be_served_.push(customer_id);
            cva_customers_ready_to_be_served_.notify_one();  // notify one desk
        }
    };


    // Sleep for random time
    //
    inline void random_sleep_for(int min, int max) {
        std::chrono::milliseconds t{ rtc::random::random_int{ min, max }() };
        std::this_thread::sleep_for(t);
    }


    // Customer
    //
    inline auto customer = [](size_t id, office& office, logger& logger, std::ostream& os) {
        using namespace tmcppc::logging::v2;

        logger.log(os, "\tCustomer ", id, ": started\n");

        random_sleep_for(100, 1200);  // time to get to the office
        logger.log(os, "\tCustomer ", id, ": got to the office\n");

        auto ticket_number{ office.customer_gets_ticket_number() };
        logger.log(os, "\tCustomer ", id, ": got ticket number ", ticket_number, "\n");

        logger.log(os, "\tCustomer ", id, ": waiting for service number\n");
        office.customer_waits_for_service_number(id, ticket_number);

        logger.log(os, "\tCustomer ", id, ": is being served\n");
        office.customer_waits_until_end_of_service(id);

        logger.log(os, "\tCustomer ", id, ": finished\n");
    };


    // Desk
    //
    inline auto desk = [](std::stop_token stoken, size_t id, office& office, logger& logger, std::ostream& os) {
        using namespace tmcppc::logging::v2;

        logger.log(os, "Desk ", id, ": started\n");

        for (;;) {
            auto customer_id{ office.desk_waits_until_customer_is_ready_to_be_served(stoken) };
            if (stoken.stop_requested()) {
                break;
            }
            logger.log(os, "Desk ", id, ": about to serve customer ", customer_id, "\n");
            random_sleep_for(50, 200);  // time to serve the customer
            logger.log(os, "Desk ", id, ": just served customer ", customer_id, "\n");
            office.desk_notifies_a_customer_has_been_served(customer_id);
        }

        logger.log(os, "Desk ", id, ": finished\n");
    };


    // Office simulator
    //
    class office_simulator {
    public:
        explicit office_simulator(size_t number_of_customers = 7, size_t number_of_desks = 3)
            : office_{ number_of_customers, number_of_desks }
            , logger_{ logger::get_instance() }
        {}
        office_simulator(const office_simulator& other) = delete;
        office_simulator& operator=(const office_simulator& other) = delete;

        void run(std::ostream& os) {
            std::vector<std::jthread> customers{};
            std::vector<std::jthread> desks{};
            for (size_t i{ 1 }; i <= office_.get_number_of_desks(); ++i) {
                desks.emplace_back(desk, i, std::ref(office_), std::ref(logger_), std::ref(os));
            }
            for (size_t i{ 1 }; i <= office_.get_number_of_customers(); ++i) {
                customers.emplace_back(customer, i, std::ref(office_), std::ref(logger_), std::ref(os));
            }
            std::for_each(std::begin(customers), std::end(customers), [](auto& t) { t.join(); });
            std::for_each(std::begin(desks), std::end(desks), [](auto& t) { t.request_stop(); });
            std::for_each(std::begin(desks), std::end(desks), [](auto& t) { t.join(); });
        }

    private:
        office office_;
        logger& logger_;
    };
}  // namespace tmcppc::office


void problem_66_main(std::istream& is, std::ostream& os);
void problem_66_main();
