#pragma once

#include <algorithm>  // for_each, remove_if
#include <fmt/format.h>
#include <fmt/ostream.h>
#include <fmt/ranges.h>
#include <list>
#include <map>
#include <memory>  // shared_ptr
#include <numeric>  // accumulate
#include <ostream>
#include <string>
#include <string_view>
#include <type_traits>  // is_convertible_v
#include <utility>  // forward, move
#include <vector>


template <typename T>
class observable_vector;


enum class notification_type { copy_assignment, move_assignment, push_back, pop_back, clear };

inline std::ostream& operator<<(std::ostream& os, const notification_type& nt) {
    fmt::print(os, "{}", nt);
    return os;
}

template <>
struct fmt::formatter<notification_type> {
    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const notification_type& nt, FormatContext& ctx) const -> decltype(ctx.out()) {
        switch (nt) {
            case notification_type::copy_assignment: return fmt::format_to(ctx.out(), "copy_assignment");
            case notification_type::move_assignment: return fmt::format_to(ctx.out(), "move_assignment");
            case notification_type::push_back: return fmt::format_to(ctx.out(), "push_back");
            case notification_type::pop_back: return fmt::format_to(ctx.out(), "pop_back");
            case notification_type::clear: return fmt::format_to(ctx.out(), "clear");
        }
        return fmt::format_to(ctx.out(), "unknown notification type");
    }
};


struct notification {
public:
    notification(notification_type t)
        : id_{ id++ }
        , type_{ t }
    {}
    notification(notification_type t, size_t i)
        : id_{ id++ }
        , type_{ t }
        , index_of_changed_element_{ i }
    {}

    [[nodiscard]] size_t get_id() const noexcept { return id_; }
    [[nodiscard]] notification_type get_type() const noexcept { return type_; }
    [[nodiscard]] size_t get_index_of_changed_element() const noexcept { return index_of_changed_element_; }
private:
    static inline size_t id{};

    size_t id_{};
    notification_type type_{};
    size_t index_of_changed_element_{};
};

inline std::ostream& operator<<(std::ostream& os, const notification& n) {
    fmt::print(os, "{}", n);
    return os;
}

template <>
struct fmt::formatter<notification> {
    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const notification& n, FormatContext& ctx) const -> decltype(ctx.out()) {
        notification_type n_type{ n.get_type() };
        return fmt::format_to(ctx.out(), "<id : {}, type : {}({})>",
            n.get_id(),
            n_type,
            (n_type == notification_type::push_back or n_type == notification_type::pop_back)
                ? std::to_string(n.get_index_of_changed_element())
                : ""
        );
    }
};


class group_id_generator {
public:
    static group_id_generator& get_instance() {
        static group_id_generator instance;
        return instance;
    }
    size_t operator()(const std::string& group) { return cache_[group]++; }
private:
    group_id_generator() = default;

    using group_t = std::string;
    using id_t = size_t;
    std::map<group_t, id_t> cache_{};
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
        : os_{ os }
        , sp_ov_ { sp_ov }
        , id_{ id_generator_("observer") }
    {}
private:
    static inline group_id_generator& id_generator_{ group_id_generator::get_instance() };

    size_t id_{};
    std::ostream& os_;
    std::shared_ptr<observable_vector<T>> sp_ov_{};
};


// Concrete observers 1 and 2 may do things completely different
// Like printing the vector contents to the console and printing the sum of all the vector elements
template <typename T>
class concrete_observer_1 : public observer<T> {
public:
    explicit concrete_observer_1(std::ostream& os, std::shared_ptr<observable_vector<T>> sp_ov) noexcept
        : observer<T>::observer{ os, sp_ov } {}
protected:
    virtual void update(const notification& n) noexcept override {
        auto id{ observer<T>::get_id() };
        auto& ov{ observer<T>::get_observable_vector() };
        fmt::print(observer<T>::get_os(), "\t[observer {}] received notification: {}\n", id, n);
        fmt::print(observer<T>::get_os(), "\t[observer {}] observable vector {}: {}\n", id, ov.get_id(), ov);
    }
};


template <typename T>
class concrete_observer_2 : public observer<T>
{
public:
    explicit concrete_observer_2(std::ostream& os, std::shared_ptr<observable_vector<T>> sp_ov) noexcept
        : observer<T>::observer{ os, sp_ov } {}
protected:
    virtual void update(const notification& n) noexcept override {
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

    void attach(const std::shared_ptr<observer<T>> observer) noexcept {
        observers_.insert(std::end(observers_), observer);
    }
    void detach(const std::shared_ptr<observer<T>> observer) noexcept {
        observers_.remove_if([&observer](auto sp) { return sp->get_id() == observer->get_id(); });
    }

protected:
    constexpr subject() : id_{ id_generator_("subject") } {}

    // Copy and move operations don't copy neither the id nor the list of observers
    constexpr subject(const subject& other) {}
    constexpr subject(subject&& other) noexcept { other.id_ = static_cast<size_t>(-1); other.observers_.clear(); }
    constexpr subject& operator=(const subject& other) { return *this; }
    constexpr subject& operator=(subject&& other) noexcept {
        other.id_ = static_cast<size_t>(-1); other.observers_.clear();
        return *this;
    }

    [[nodiscard]] bool is_observed() const noexcept { return not observers_.empty(); }

    void notify(const notification& n) const {
        std::for_each(std::begin(observers_), std::end(observers_), [&n](auto sp) { sp->update(n); });
    }

private:
    static inline group_id_generator& id_generator_{ group_id_generator::get_instance() };

    size_t id_{};
    std::list<std::shared_ptr<observer<T>>> observers_{};
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

    constexpr observable_vector() noexcept = default;
    constexpr explicit observable_vector(size_t s)
        : v_(s) {}
    constexpr observable_vector(size_t s, const T& t)
        : v_(s, t) {}
    template <typename InputIt>
    constexpr observable_vector(InputIt first, InputIt last)
        : v_(first, last) {}
    constexpr observable_vector(std::initializer_list<T> init)
        : v_(init) {}

    constexpr observable_vector(const observable_vector& other)
        : subject<T>{ other }
        , v_{ other.v_ }
    {}
    constexpr observable_vector(observable_vector&& other) noexcept
        : subject<T>{ std::move(other) }
        , v_{ std::move(other.v_) }
    {}
    constexpr observable_vector& operator=(const observable_vector& other)
    {
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
        fmt::print(os, v);
        return os;
    }

private:
    friend struct fmt::formatter<observable_vector>;

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


template <typename T>
struct fmt::is_range<observable_vector<T>, char> : std::false_type {};


template <typename T>
struct fmt::formatter<observable_vector<T>> {
    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const observable_vector<T>& v, FormatContext& ctx) const -> decltype(ctx.out()) {
        return fmt::format_to(ctx.out(), "{}", v.v_);
    }
};


template <typename T>
requires std::is_convertible_v<std::vector<T>, std::string_view>
struct fmt::formatter<observable_vector<T>> {
    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const observable_vector<T>& v, FormatContext& ctx) const -> decltype(ctx.out()) {
        fmt::format_to(ctx.out(), "[");
        bool first{ true };
        for (auto&& c : v.v_) {
            fmt::format_to(ctx.out(), "{}'{}'", first ? "" : ", ", c);
            first = false;
        }
        return fmt::format_to(ctx.out(), "]");
    }
};


void problem_71_main(std::ostream& os);
void problem_71_main();
