#pragma once

#include <algorithm>  // make_heap, push_heap, pop_heap, swap
#include <functional>  // less
#include <stdexcept>  // runtime_error
#include <vector>


namespace tmcppc::data_structures {
    template <typename T, typename Compare = std::less<T>>
    class priority_queue {
    public:
        using container = std::vector<T>;
        using container_type = container;
        using const_reference = container::const_reference;
        using reference = container::reference;
        using size_type = container::size_type;
        using value_compare = Compare;
        using value_type = container::value_type;

    public:
        using const_iterator = container::const_iterator;
        using iterator = container::iterator;

        priority_queue() = default;

        template <typename InputIt>
        priority_queue(InputIt first, InputIt last, const Compare& comp = Compare{})
            : container_{ first, last }, compare_{ comp } {
            std::ranges::make_heap(container_, compare_);
        }

        constexpr void push(const T& t) noexcept {
            container_.push_back(t);
            std::ranges::push_heap(container_, compare_);
        }
        constexpr void pop() {
            throw_if_empty();
            std::ranges::pop_heap(container_, compare_);
            container_.pop_back();
        }
        [[nodiscard]] constexpr T& top() {
            throw_if_empty();
            return container_.front();
        }
        [[nodiscard]] constexpr const T& top() const {
            throw_if_empty();
            return container_.front();
        }
        [[nodiscard]] constexpr size_type size() const noexcept { return container_.size(); }
        [[nodiscard]] constexpr bool empty() const noexcept { return container_.empty(); }

        void swap(priority_queue& other) noexcept {
            std::swap(container_, other.container_);
            std::swap(compare_, other.compare_);
        }

        constexpr iterator begin() noexcept { return container_.begin(); }
        constexpr iterator end() noexcept { return container_.end(); }
        constexpr const_iterator begin() const noexcept { return container_.cbegin(); }
        constexpr const_iterator end() const noexcept { return container_.cend(); }
        constexpr const_iterator cbegin() const noexcept { return container_.cbegin(); }
        constexpr const_iterator cend() const noexcept { return container_.cend(); }

    private:
        constexpr void throw_if_empty() const {
            if (empty()) {
                throw std::runtime_error{ "trying to access an empty priority queue." };
            }
        }

        std::vector<T> container_{};
        Compare compare_{};
    };

    template <typename T, typename Compare>
    void swap(priority_queue<T, Compare>& lhs, priority_queue<T, Compare>& rhs) noexcept(noexcept(lhs.swap(rhs))) { lhs.swap(rhs); }

    template <typename T, typename Compare>
    auto begin(priority_queue<T, Compare>& pq) -> decltype(pq.begin()) { return pq.begin(); }
    template <typename T, typename Compare>
    auto end(priority_queue<T, Compare>& pq) -> decltype(pq.end()) { return pq.end(); }
    template <typename T, typename Compare>
    auto begin(const priority_queue<T, Compare>& pq) -> decltype(pq.cbegin()) { return pq.cbegin(); }
    template <typename T, typename Compare>
    auto end(const priority_queue<T, Compare>& pq) -> decltype(pq.cend()) { return pq.cend(); }
    template <typename T, typename Compare>
    auto cbegin(const priority_queue<T, Compare>& pq) -> decltype(pq.cbegin()) { return pq.cbegin(); }
    template <typename T, typename Compare>
    auto cend(const priority_queue<T, Compare>& pq) -> decltype(pq.cend()) { return pq.cend(); }
}  // namespace tmcppc::data_structures
