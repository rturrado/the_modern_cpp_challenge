#pragma once

#include <condition_variable>  // condition_variable_any
#include <iosfwd>
#include <mutex>
#include <queue>
#include <thread>  // lock_guard, unique_lock
#include <vector>


class ticketing_machine {
public:
    ticketing_machine(const ticketing_machine& other) = delete;
    ticketing_machine& operator=(const ticketing_machine& other) = delete;

    static ticketing_machine& get_instance() {
        static ticketing_machine instance;
        return instance;
    }

    auto get_ticket_number() {
        std::lock_guard<std::mutex> lock{ m_ };
        return ticket_number_++;
    }

protected:
    ticketing_machine() {}

private:
    size_t ticket_number_{ 1 };
    std::mutex m_{};
};


class office {
public:
    office(const office& other) = delete;
    office& operator=(const office& other) = delete;

    static office& get_instance() {
        static office instance;
        return instance;
    }

    constexpr size_t get_number_of_customers() { return number_of_customers_; }
    constexpr size_t get_number_of_desks() { return number_of_desks_; }

    // Ticket number
    auto customer_gets_ticket_number() { return ticketing_machine_.get_ticket_number(); }

    // Service number
    void customer_waits_for_service_number(size_t customer_id, size_t ticket_number) {
        std::unique_lock<std::mutex> lock{ m_service_number_ };
        cv_service_number_.wait(lock, [this, ticket_number] { return service_number_ == ticket_number; });

        lock.unlock();
        add_customer_ready_to_be_served(customer_id);
    }

    // Customers ready to be served
    auto desk_waits_until_customer_is_ready_to_be_served(std::stop_token stoken) {
        std::unique_lock<std::mutex> lock{ m_customers_ready_to_be_served_ };
        cva_customers_ready_to_be_served_.wait(lock, stoken, [this] { return not customers_ready_to_be_served_.empty(); });
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
            return std::binary_search(std::begin(customers_served_), std::end(customers_served_), customer_id); });
        customers_served_.erase(std::find(std::begin(customers_served_), std::end(customers_served_), customer_id));
    }

protected:
    office() {}

private:
    const size_t number_of_customers_{ 7 };
    const size_t number_of_desks_{ 3 };

    ticketing_machine& ticketing_machine_{ ticketing_machine::get_instance() };

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


void problem_66_main(std::ostream& os);
void problem_66_main();
