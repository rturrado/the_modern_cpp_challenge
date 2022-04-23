#include "chapter_08_design_patterns/problem_071_observable_vector_container.h"
#include "rtc/print.h"

#include <algorithm>  // remove_if
#include <initializer_list>
#include <iostream>  // cout
#include <list>
#include <map>
#include <memory>  // make_shared, shared_ptr
#include <numeric>  // accumulate
#include <string>
#include <vector>


template <typename T>
class ObservableVector;


enum class NotificationType { COPY_ASSIGNMENT, MOVE_ASSIGNMENT, PUSH_BACK, POP_BACK, CLEAR };

std::ostream& operator<<(std::ostream& os, const NotificationType& nt)
{
    switch (nt)
    {
    case NotificationType::COPY_ASSIGNMENT: os << "copy_assignment"; break;
    case NotificationType::MOVE_ASSIGNMENT: os << "move_assignment"; break;
    case NotificationType::PUSH_BACK: os << "push_back"; break;
    case NotificationType::POP_BACK: os << "pop_back"; break;
    case NotificationType::CLEAR: os << "clear"; break;
    default: os << "unknown notification type"; break;
    }
    return os;
}

struct Notification
{
public:
    Notification(NotificationType t) : id_{ id++ }, type_{ t } {}
    Notification(NotificationType t, size_t i) : id_{ id++ }, type_{ t }, index_of_changed_element_{ i } {}

    [[nodiscard]] size_t get_id() const noexcept { return id_; }
    [[nodiscard]] NotificationType get_type() const noexcept { return type_; }
    [[nodiscard]] size_t get_index_of_changed_element() const noexcept { return index_of_changed_element_; }
private:
    static inline size_t id{};

    size_t id_{};
    NotificationType type_{};
    size_t index_of_changed_element_{};
};

std::ostream& operator<<(std::ostream& os, const Notification& n)
{
    NotificationType n_type{ n.get_type() };
    os << "{ " << "id : " << n.get_id() << ", type : " << n_type << "(";
    if (n_type == NotificationType::PUSH_BACK or n_type == NotificationType::POP_BACK) { os << n.get_index_of_changed_element(); }
    os << ") }";
    return os;
}


class GroupIdGenerator
{
public:
    static GroupIdGenerator& get_instance() { static GroupIdGenerator instance; return instance; }
    size_t operator()(const std::string& group) { return cache_[group]++; }
private:
    GroupIdGenerator() = default;

    using group_t = std::string;
    using id_t = size_t;
    std::map<group_t, id_t> cache_{};
};


template <typename T>
class Observer
{
public:
    virtual ~Observer() = default;

    [[nodiscard]] size_t get_id() const noexcept { return id_; }
    [[nodiscard]] ObservableVector<T>& get_observable_vector() const noexcept { return *sp_ov_; }

    virtual void update(const Notification& n) const noexcept = 0;
protected:
    std::shared_ptr<ObservableVector<T>> sp_ov_{};
    
    explicit Observer(std::shared_ptr<ObservableVector<T>> sp_ov) noexcept
        : sp_ov_{ sp_ov }, id_{ id_generator_("Observer") } {}
private:
    static inline GroupIdGenerator& id_generator_{ GroupIdGenerator::get_instance() };

    size_t id_{};
};

// Concrete observers 1 and 2 may do things completely different
// Like printing the vector contents to the console and printing the sum of all the vector elements
template <typename T>
class ConcreteObserver1 : public Observer<T>
{
public:
    explicit ConcreteObserver1(std::shared_ptr<ObservableVector<T>> sp_ov) noexcept : Observer<T>::Observer{ sp_ov } {}
protected:
    virtual void update(const Notification& n) const noexcept override
    {
        auto id{ Observer<T>::get_id() };
        auto& ov{ Observer<T>::get_observable_vector() };
        std::cout << "\t[Observer " << id << "] received notification: " << n << "\n";
        std::cout << "\t[Observer " << id << "] observable vector " << ov.get_id() << ": " << ov << "\n";
    }
};


template <typename T>
class ConcreteObserver2 : public Observer<T>
{
public:
    explicit ConcreteObserver2(std::shared_ptr<ObservableVector<T>> sp_ov) noexcept : Observer<T>::Observer{ sp_ov } {}
protected:
    virtual void update(const Notification& n) const noexcept override
    {
        auto id{ Observer<T>::get_id() };
        auto& ov{ Observer<T>::get_observable_vector() };
        std::cout << "\t[Observer " << id << "] received notification " << n << "\n";
        std::cout << "\t[Observer " << id << "] sum of elements of observable vector " << ov.get_id() << ": "
            << std::accumulate(std::begin(ov), std::end(ov), static_cast<T>(0)) << "\n";
    }
};


template <typename T>
class Subject
{
public:
    virtual ~Subject() = default;

    [[nodiscard]] size_t get_id() const noexcept { return id_; }

    void attach(const std::shared_ptr<Observer<T>> observer) noexcept
    {
        observers_.insert(std::end(observers_), observer);
    }
    void detach(const std::shared_ptr<Observer<T>> observer) noexcept
    {
        observers_.remove_if([&observer](auto sp) { return sp->get_id() == observer->get_id(); });
    }

protected:
    constexpr Subject() : id_{ id_generator_("Subject") } {}
    
    // Copy and move operations don't copy neither the id nor the list of observers
    constexpr Subject(const Subject& other) {}
    constexpr Subject(Subject&& other) noexcept { other.id_ = static_cast<size_t>(-1); other.observers_.clear(); }
    constexpr Subject& operator=(const Subject& other) { return *this; }
    constexpr Subject& operator=(Subject&& other) noexcept
    {
        other.id_ = static_cast<size_t>(-1); other.observers_.clear();
        return *this;
    }

    [[nodiscard]] bool is_observed() const noexcept { return not observers_.empty(); }
    
    void notify(const Notification& n) const
    {
        std::for_each(std::begin(observers_), std::end(observers_), [&n](auto sp) { sp->update(n); });
    }

private:
    static inline GroupIdGenerator& id_generator_{ GroupIdGenerator::get_instance() };

    size_t id_{};
    std::list<std::shared_ptr<Observer<T>>> observers_{};
};


template <typename T>
class ObservableVector : public Subject<T>
{
public:
    using size_type = std::vector<T>::size_type;
    using difference_type = std::vector<T>::difference_type;
    using reference = std::vector<T>::reference;
    using const_reference = std::vector<T>::const_reference;
    using iterator = std::vector<T>::iterator;
    using const_iterator = std::vector<T>::const_iterator;

    constexpr ObservableVector() noexcept = default;
    constexpr explicit ObservableVector(size_t s) : v_(s) {}
    constexpr ObservableVector(size_t s, const T& t) : v_(s, t) {}
    template <typename InputIt>
    constexpr ObservableVector(InputIt first, InputIt last) : v_(first, last) {}
    constexpr ObservableVector(std::initializer_list<T> init) : v_(init) {}
    
    constexpr ObservableVector(const ObservableVector& other) : Subject<T>{ other }, v_{ other.v_ } {}
    constexpr ObservableVector(ObservableVector&& other) noexcept : Subject<T>{ std::move(other) }, v_{ std::move(other.v_) } {}
    constexpr ObservableVector& operator=(const ObservableVector& other)
    {
        Subject<T>::operator=(other);
        v_.clear();
        v_ = other.v_;

        if (Subject<T>::is_observed()) { Subject<T>::notify(Notification{ NotificationType::COPY_ASSIGNMENT }); }
        return *this;
    }
    constexpr ObservableVector& operator=(ObservableVector&& other) noexcept
    {
        Subject<T>::operator=(std::move(other));
        v_.clear();
        v_ = std::move(other.v_);

        if (Subject<T>::is_observed()) { Subject<T>::notify(Notification{ NotificationType::MOVE_ASSIGNMENT }); }
        return *this;
    }
    constexpr reference operator[](size_type pos) { return v_[pos]; }
    constexpr const_reference operator[](size_type pos) const { return v_[pos]; }
    constexpr void push_back(T&& t)
    {
        v_.push_back(std::forward<T>(t));

        if (Subject<T>::is_observed()) { Subject<T>::notify(Notification{ NotificationType::PUSH_BACK, v_.size() - 1 }); }
    }
    constexpr void pop_back()
    {
        v_.pop_back();

        if (Subject<T>::is_observed()) { Subject<T>::notify(Notification{ NotificationType::POP_BACK, v_.size() }); }
    }
    constexpr void clear() noexcept
    {
        v_.clear();

        if (Subject<T>::is_observed()) { Subject<T>::notify(Notification{ NotificationType::CLEAR }); }
    }
    [[nodiscard]] auto size () const noexcept { return v_.size(); }
    [[nodiscard]] auto empty() const noexcept { return v_.empty(); }
    
    constexpr iterator begin() noexcept { return v_.begin(); }
    constexpr const_iterator begin() const noexcept { return v_.begin(); }
    constexpr const_iterator cbegin() const noexcept { return v_.cbegin(); }
    constexpr iterator end() noexcept { return v_.end(); }
    constexpr const_iterator end() const noexcept { return v_.end(); }
    constexpr const_iterator cend() const noexcept { return v_.cend(); }

    friend std::ostream& operator<<(std::ostream& os, const ObservableVector<T>& v) { return os << v.v_; }

private:
    std::vector<T> v_{};
};

template <typename T>
constexpr auto begin(ObservableVector<T>& v) -> decltype(v.begin()) { return v.begin(); }
template <typename T>
constexpr auto begin(const ObservableVector<T>& v) -> decltype(v.begin()) { return v.begin(); }
template <typename T>
constexpr auto cbegin(const ObservableVector<T>& v) -> decltype(begin(v)) { return begin(v); }
template <typename T>
constexpr auto end(ObservableVector<T>& v) -> decltype(v.end()) { return v.end(); }
template <typename T>
constexpr auto end(const ObservableVector<T>& v) -> decltype(v.end()) { return v.end(); }
template <typename T>
constexpr auto cend(const ObservableVector<T>& v) -> decltype(end(v)) { return end(v); }


// Observable vector container
//
// Write a class template that behaves like a vector but can notify registered parties of internal state changes.
// The class must provide at least the following operations:
//
//   - Various constructors for creating new instances of the class.
//   - operator= to assign values to the container.
//   - push_back() to add a new element at the end of the container.
//   - pop_back() to remove the last element from the container.
//   - clear() to remove all the elements from the container.
//   - size() to return the number of elements from the container.
//   - empty() to indicate whether the container is empty or has elements.
//
// operator=, push_back(), pop_back(), and clear() must notify others of the state changes.
// The notification should include the type of the change, and, when the case,
// the index of the element that was changed (such as added or removed).
void problem_71_main()
{
    // Test observable vector constructors
    std::cout << "Creating the observable vectors:\n";
    auto sp_ov_0{ std::make_shared<ObservableVector<std::string>>() };
    auto sp_ov_1{ std::make_shared<ObservableVector<float>>(5) }; for (auto i = 0; i < sp_ov_1->size(); ++i) { (*sp_ov_1)[i] = 3.14f * i; }
    auto sp_ov_2{ std::make_shared<ObservableVector<double>>(3, 1.5) };
    const char* cstr{ "Hello, universe!" }; auto sp_ov_3{ std::make_shared<ObservableVector<char>>(cstr + 4, cstr + 8) };
    auto sp_ov_4{ std::make_shared<ObservableVector<int>>()};
    std::cout << "\tov_0: " << *sp_ov_0 << "\n";
    std::cout << "\tov_1: " << *sp_ov_1 << "\n";
    std::cout << "\tov_2: " << *sp_ov_2 << "\n";
    std::cout << "\tov_3: " << *sp_ov_3 << "\n";
    std::cout << "\tov_4: " << *sp_ov_4 << "\n";
    std::cout << "\n";

    // Concrete observers
    auto sp_co_0{ std::make_shared<ConcreteObserver1<std::string>>(sp_ov_0) };
    auto sp_co_1{ std::make_shared<ConcreteObserver2<float>>(sp_ov_1) };
    auto sp_co_2{ std::make_shared<ConcreteObserver2<double>>(sp_ov_2) };
    auto sp_co_3{ std::make_shared<ConcreteObserver1<char>>(sp_ov_3) };
    auto sp_co_4{ std::make_shared<ConcreteObserver2<int>>(sp_ov_4) };

    // Attach concrete observers to observable vectors
    sp_ov_0->attach(sp_co_0);
    sp_ov_1->attach(sp_co_1);
    sp_ov_2->attach(sp_co_2);
    sp_ov_3->attach(sp_co_3);
    sp_ov_4->attach(sp_co_4);

    // Test operations and notifications
    std::cout << "Pushing back on ov_0:\n";
    sp_ov_0->push_back("Tush! Never tell me;"); sp_ov_0->push_back("I take it much unkindly."); std::cout << "\n";

    std::cout << "Copy assigning from ov_3:\n";
    ObservableVector<char> ov_char{};  // copy operations don't copy the list of observers
    ov_char = *sp_ov_3;
    ov_char.pop_back();
    std::cout << "\n";

    std::cout << "Move assigning from ov_1:\n";
    ObservableVector<float> ov_float{};  // move operations don't copy the list of observers
    ov_float = std::move(*sp_ov_1);
    ov_float.push_back(3.14f);
    std::cout << "\n";

    std::cout << "Copy assigning to ov_3:\n";
    *sp_ov_3 = ov_char;
    std::cout << "\n";

    std::cout << "Move assigning to ov_4:\n";
    *sp_ov_4 = ObservableVector<int>(std::initializer_list<int>{ 1, 1, 2, 3, 5 });
    std::cout << "\n";

    std::cout << "Detaching from ov_1:\n";
    sp_ov_0->detach(sp_co_0);
    sp_ov_0->push_back("That thou, Iago, who hast had my purse.");
    std::cout << "\n";
}
