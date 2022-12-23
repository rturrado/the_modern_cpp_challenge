#pragma once

#include <algorithm>  // for_each, remove_if
#include <fmt/format.h>
#include <fmt/ostream.h>
#include <fmt/ranges.h>
#include <list>
#include <map>
#include <memory>  // shared_ptr, weak_ptr
#include <numeric>  // accumulate
#include <ostream>
#include <string>
#include <string_view>
#include <type_traits>  // is_arithmetic_v, is_convertible_v
#include <utility>  // forward, move
#include <vector>


namespace tmcppc::data_structures {
    enum class notification_type;
    struct notification;
    template <typename T> class observable_vector;
}

// fmt formatters
template <>
struct fmt::formatter<tmcppc::data_structures::notification_type> : fmt::ostream_formatter {};
template <>
struct fmt::formatter<tmcppc::data_structures::notification> : fmt::ostream_formatter {};
template <typename T>
struct fmt::is_range<tmcppc::data_structures::observable_vector<T>, char> : std::false_type {};
template <typename T>
struct fmt::formatter<tmcppc::data_structures::observable_vector<T>> : fmt::ostream_formatter {};


namespace tmcppc::data_structures {
    enum class notification_type { copy_assignment, move_assignment, push_back, pop_back, clear };

    inline std::ostream& operator<<(std::ostream& os, const notification_type& nt) {
        switch (nt) {
            case notification_type::copy_assignment: return os << fmt::format("copy_assignment");
            case notification_type::move_assignment: return os << fmt::format("move_assignment");
            case notification_type::push_back: return os << fmt::format("push_back");
            case notification_type::pop_back: return os << fmt::format("pop_back");
            case notification_type::clear: return os << fmt::format("clear");
        }
        return os << fmt::format("unknown notification type");
    }


    struct notification {
    public:
        explicit notification(notification_type t)
            : id_{ id++ }
            , type_{ t }
            , index_of_changed_element_{ 0 }
        {}
        notification(notification_type t, size_t i)
            : id_{ id++ }
            , type_{ t }
            , index_of_changed_element_{ i }
        {}

        [[nodiscard]] size_t get_id() const noexcept { return id_; }
        [[nodiscard]] notification_type get_type() const noexcept { return type_; }
        [[nodiscard]] size_t get_index_of_changed_element() const noexcept { return index_of_changed_element_; }

        friend std::ostream& operator<<(std::ostream& os, const notification& n) {
            tmcppc::data_structures::notification_type n_type{ n.get_type() };
            return os << fmt::format("<id : {}, type : {}({})>",
                n.get_id(),
                n_type,
                (n_type == notification_type::push_back or
                 n_type == notification_type::pop_back)
                    ? std::to_string(n.get_index_of_changed_element())
                    : ""
            );
        }
    private:
        static inline size_t id{};

        size_t id_;
        notification_type type_;
        size_t index_of_changed_element_;
    };


    class group_id_generator {
    public:
        [[nodiscard]] static group_id_generator& get_instance() {
            static group_id_generator instance;
            return instance;
        }
        [[nodiscard]] size_t operator()(const std::string& group) { return cache_[group]++; }
    private:
        group_id_generator() = default;

        using group_t = std::string;
        using id_t = size_t;
        std::map<group_t, id_t> cache_;
    };


    template <typename T>
    class observer {
    public:
        virtual ~observer() = default;

        [[nodiscard]] size_t get_id() const noexcept { return id_; }
        [[nodiscard]] std::ostream& get_os() noexcept { return os_; }
        [[nodiscard]] observable_vector<T>& get_observable_vector() const noexcept { return *sp_ov_; }

        virtual void update(const notification& n) noexcept = 0;
    protected:
        explicit observer(std::ostream& os, std::shared_ptr<observable_vector<T>> sp_ov) noexcept
            : id_{ id_generator_("observer") }
            , os_{ os }
            , sp_ov_{ std::move(sp_ov) }
        {}
        constexpr observer(const observer& other) = default;
        constexpr observer(observer&& other) = default;
        constexpr observer& operator=(const observer& other) = default;
        constexpr observer& operator=(observer&& other) = default;
    private:
        static inline group_id_generator& id_generator_{ group_id_generator::get_instance() };

        size_t id_;
        std::ostream& os_;
        std::shared_ptr<observable_vector<T>> sp_ov_;
    };


    // Concrete observers 1 and 2 may do things completely different
    // Like printing the vector contents to the console and printing the sum of all the vector elements
    template <typename T>
        requires requires (T t) { fmt::print("{}", t); }
    class concrete_observer_1 : public observer<T> {
    public:
        explicit concrete_observer_1(std::ostream& os, std::shared_ptr<observable_vector<T>> sp_ov) noexcept
            : observer<T>::observer{ os, std::move(sp_ov) } {}
        constexpr concrete_observer_1(const concrete_observer_1& other) = default;
        constexpr concrete_observer_1(concrete_observer_1&& other) = default;
        constexpr concrete_observer_1& operator=(const concrete_observer_1& other) = default;
        constexpr concrete_observer_1& operator=(concrete_observer_1&& other) = default;
        ~concrete_observer_1() = default;
    protected:
        void update(const notification& n) noexcept override {
            auto id{ observer<T>::get_id() };
            auto& ov{ observer<T>::get_observable_vector() };
            fmt::print(observer<T>::get_os(), "\t[observer {}] received notification: {}\n", id, n);
            fmt::print(observer<T>::get_os(), "\t[observer {}] observable vector {}: {}\n", id, ov.get_id(), ov);
        }
    };


    template <typename T>
        requires std::is_arithmetic_v<T>
    class concrete_observer_2 : public observer<T> {
    public:
        explicit concrete_observer_2(std::ostream& os, std::shared_ptr<observable_vector<T>> sp_ov) noexcept
            : observer<T>::observer{ os, std::move(sp_ov) } {}
        constexpr concrete_observer_2(const concrete_observer_2& other) = default;
        constexpr concrete_observer_2(concrete_observer_2&& other) = default;
        constexpr concrete_observer_2& operator=(const concrete_observer_2& other) = default;
        constexpr concrete_observer_2& operator=(concrete_observer_2&& other) = default;
        ~concrete_observer_2() = default;
    protected:
        void update(const notification& n) noexcept override {
            auto id{ observer<T>::get_id() };
            auto& ov{ observer<T>::get_observable_vector() };
            fmt::print(observer<T>::get_os(), "\t[observer {}] received notification: {}\n", id, n);
            fmt::print(observer<T>::get_os(), "\t[observer {}] sum of elements of observable vector {}: {}\n",
                id, ov.get_id(), std::accumulate(std::begin(ov), std::end(ov), static_cast<T>(0)));
        }
    };


    template <typename T>
    class subject {
    public:
        virtual ~subject() = default;

        [[nodiscard]] size_t get_id() const noexcept { return id_; }

        void attach(const std::shared_ptr<observer<T>>& observer_sp) noexcept {
            observers_.insert(std::end(observers_), observer_sp);
        }
        void detach(const std::shared_ptr<observer<T>>& observer_sp) noexcept {
            observers_.remove_if([&observer_sp](const auto& wp) {
                auto sp{ wp.lock() };
                return sp and sp->get_id() == observer_sp->get_id();
            });
        }

    protected:
        constexpr subject() : id_{ id_generator_("subject") } {}

        // Copy and move operations don't copy neither the id nor the list of observers
        constexpr subject(const subject& other) {}
        constexpr subject(subject&& other) noexcept {
            other.id_ = static_cast<size_t>(-1);
            other.observers_.clear();
        }
        constexpr subject& operator=([[maybe_unused]] const subject& other) { return *this; }
        constexpr subject& operator=(subject&& other) noexcept {
            other.id_ = static_cast<size_t>(-1);
            other.observers_.clear();
            return *this;
        }

        [[nodiscard]] bool is_observed() const noexcept { return not observers_.empty(); }

        void notify(const notification& n) const {
            std::ranges::for_each(observers_, [&n](const auto& wp) {
                if (auto sp{ wp.lock() }; sp != nullptr) {
                    sp->update(n);
                }
            });
        }

    private:
        static inline group_id_generator& id_generator_{ group_id_generator::get_instance() };

        size_t id_;
        std::list<std::weak_ptr<observer<T>>> observers_;
    };


    template <typename T>
    class observable_vector : public subject<T> {
    public:
        using size_type = std::vector<T>::size_type;
        using difference_type = std::vector<T>::difference_type;
        using reference = std::vector<T>::reference;
        using const_reference = std::vector<T>::const_reference;
        using iterator = std::vector<T>::iterator;
        using const_iterator = std::vector<T>::const_iterator;

        constexpr observable_vector() = default;
        constexpr explicit observable_vector(size_t s)
            : v_(s) {}
        constexpr observable_vector(size_t s, const T& t)
            : v_(s, t) {}
        template <typename InputIt>
        constexpr observable_vector(InputIt first, InputIt last)
            : v_(first, last) {}
        constexpr observable_vector(std::initializer_list<T> init)
            : v_{ init } {}

        constexpr observable_vector(const observable_vector& other)
            : subject<T>{ other }
            , v_{ other.v_ }
        {}
        constexpr observable_vector(observable_vector&& other) noexcept
            : subject<T>{ std::move(other) }
            , v_{ std::move(other.v_) }
        {}
        constexpr observable_vector& operator=(const observable_vector& other) {
            subject<T>::operator=(other);
            v_.clear();
            v_ = other.v_;

            if (subject<T>::is_observed()) {
                subject<T>::notify(notification{ notification_type::copy_assignment });
            }
            return *this;
        }
        constexpr observable_vector& operator=(observable_vector&& other) noexcept {
            subject<T>::operator=(std::move(other));
            v_.clear();
            v_ = std::move(other.v_);

            if (subject<T>::is_observed()) {
                subject<T>::notify(notification{ notification_type::move_assignment });
            }
            return *this;
        }
        constexpr reference operator[](size_type pos) { return v_[pos]; }
        constexpr const_reference operator[](size_type pos) const { return v_[pos]; }
        constexpr void push_back(T&& t) {
            v_.push_back(std::forward<T>(t));

            if (subject<T>::is_observed()) {
                subject<T>::notify(notification{ notification_type::push_back, v_.size() - 1 });
            }
        }
        constexpr void pop_back() {
            v_.pop_back();

            if (subject<T>::is_observed()) {
                subject<T>::notify(notification{ notification_type::pop_back, v_.size() });
            }
        }
        constexpr void clear() noexcept {
            v_.clear();

            if (subject<T>::is_observed()) {
                subject<T>::notify(notification{ notification_type::clear });
            }
        }
        [[nodiscard]] auto size() const noexcept { return v_.size(); }
        [[nodiscard]] auto empty() const noexcept { return v_.empty(); }

        constexpr iterator begin() noexcept { return v_.begin(); }
        constexpr const_iterator begin() const noexcept { return v_.begin(); }
        constexpr const_iterator cbegin() const noexcept { return v_.cbegin(); }
        constexpr iterator end() noexcept { return v_.end(); }
        constexpr const_iterator end() const noexcept { return v_.end(); }
        constexpr const_iterator cend() const noexcept { return v_.cend(); }

        friend std::ostream& operator<<(std::ostream& os, const observable_vector<T>& v) {
            return os << fmt::format("{}", v.v_);
        }

        friend std::ostream& operator<<(std::ostream& os, const observable_vector<T>& v)
            requires std::is_convertible_v<std::vector<T>, std::string_view> {

            os << fmt::format("[");
            bool first{ true };
            for (auto&& c : v.v_) {
                os << fmt::format("{}'{}'", first ? "" : ", ", c);
                first = false;
            }
            return os << fmt::format("]");
        }

    private:
        std::vector<T> v_{};
    };

    template <typename T>
    constexpr auto begin(observable_vector<T>& v) -> decltype(v.begin()) { return v.begin(); }
    template <typename T>
    constexpr auto begin(const observable_vector<T>& v) -> decltype(v.begin()) { return v.begin(); }
    template <typename T>
    constexpr auto cbegin(const observable_vector<T>& v) -> decltype(begin(v)) { return begin(v); }
    template <typename T>
    constexpr auto end(observable_vector<T>& v) -> decltype(v.end()) { return v.end(); }
    template <typename T>
    constexpr auto end(const observable_vector<T>& v) -> decltype(v.end()) { return v.end(); }
    template <typename T>
    constexpr auto cend(const observable_vector<T>& v) -> decltype(end(v)) { return end(v); }
}  // namespace tmcppc::data_structures


void problem_71_main(std::ostream& os);
