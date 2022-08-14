#pragma once

#include <algorithm>  // min
#include <fmt/format.h>
#include <fmt/ostream.h>
#include <fmt/ranges.h>
#include <stdexcept>  // out_of_range
#include <type_traits>  // false_type
#include <vector>


namespace tmcppc::data_structures {
    template <typename T>
    class circular_buffer {
    public:
        using container = std::vector<T>;
        using container_type = container;
        using const_reference = container::const_reference;
        using reference = container::reference;
        using size_type = container::size_type;
        using value_type = container::value_type;

    private:
        class const_iterator {
        public:
            using iterator_category = std::random_access_iterator_tag;
            using reference = container::const_reference;

            using TPtr_ = size_type;

            constexpr const_iterator() noexcept : ptr_{} {}
            constexpr const_iterator(const circular_buffer& cb, TPtr_ pos, bool last) noexcept
                : cb_{ cb }, ptr_{ pos }, last_{ last } {}
            constexpr reference operator*() const noexcept { return cb_.container_[ptr_]; }
            constexpr reference operator->() const noexcept { return cb_.container_[ptr_]; }
            constexpr const_iterator& operator++() noexcept {
                ptr_ = cb_.next_pos(ptr_);
                last_ = (ptr_ == cb_.next_pos(cb_.back_pos_));
                return *this;
            }
            constexpr const_iterator operator++(int) noexcept {
                const_iterator tmp{ *this };
                ++(*this);
                return tmp;
            }
            bool operator==(const const_iterator& other) const noexcept {
                return cb_ == other.cb_ and ptr_ == other.ptr_;
            }
            bool operator!=(const const_iterator& other) const noexcept {
                return not (*this == other);
            }
            auto operator<(const const_iterator& other) const noexcept {
                return cb_ < other.cb_ or (cb_ == other.cb_ and ptr_ < other.ptr_);
            }
            auto operator>(const const_iterator& other) const noexcept {
                return cb_ > other.cb_ or (cb_ == other.cb_ and ptr_ > other.ptr_);
            }
            auto operator<=(const const_iterator& other) const noexcept {
                return not (*this > other);
            }
            auto operator>=(const const_iterator& other) const noexcept {
                return not (*this < other);
            }

        protected:
            const circular_buffer<T>& cb_;
            TPtr_ ptr_{ front_pos_ };
            // begin and end will point to the same position in a full circular buffer
            // This flag will help us differentiate them at the beginning of a loop
            bool last_{};
        };

        class iterator : public const_iterator {
            using MyBase_ = const_iterator;

        public:
            using iterator_category = std::random_access_iterator_tag;
            using reference = container::reference;

            constexpr iterator() noexcept : const_iterator{} {}
            constexpr iterator(circular_buffer& cb, MyBase_::TPtr_ pos, bool last) noexcept
                : const_iterator{ cb, pos, last } {}
            constexpr reference operator*() const noexcept { return const_cast<reference>(MyBase_::operator*()); }
            constexpr reference operator->() const noexcept { return const_cast<reference>(MyBase_::operator->()); }
            constexpr iterator& operator++() noexcept {
                MyBase_::operator++();
                return *this;
            }
            constexpr iterator operator++(int) noexcept {
                iterator tmp{ *this };
                MyBase_::operator++();
                return tmp;
            }
        };

    public:
        circular_buffer(size_type capacity)
            : container_(capacity), capacity_{ capacity } {
            if (capacity_ == 0) {
                throw std::runtime_error{ "trying to create a circular_buffer with a fixed size of 0." };
            }
        }

        constexpr void push_back(const T& t) noexcept {
            back_pos_ = empty() ? front_pos_ : next_pos(back_pos_);
            if (full()) {
                front_pos_ = next_pos(front_pos_);
            }
            size_ = std::min(size_ + 1, capacity_);
            container_[back_pos_] = t;
        }
        constexpr void pop_front() {
            throw_if_empty();
            front_pos_ = next_pos(front_pos_);
            size_--;
        }
        constexpr void pop_back() {
            throw_if_empty();
            back_pos_ = prev_pos(back_pos_);
            size_--;
        }

        [[nodiscard]] constexpr T& front() {
            throw_if_empty();
            return container_[front_pos_];
        }
        [[nodiscard]] constexpr const T& front() const {
            throw_if_empty();
            return container_[front_pos_];
        }
        [[nodiscard]] constexpr T& back() {
            throw_if_empty();
            return container_[back_pos_];
        }
        [[nodiscard]] constexpr const T& back() const {
            throw_if_empty();
            return container_[back_pos_];
        }

        [[nodiscard]] constexpr size_type size() const noexcept { return size_; }
        [[nodiscard]] constexpr size_type capacity() const noexcept { return capacity_; }

        [[nodiscard]] constexpr bool empty() const noexcept { return size_ == 0; }
        [[nodiscard]] constexpr bool full() const noexcept { return size_ == capacity_; }

        constexpr void clear() noexcept { size_ = 0; }

        constexpr iterator begin() noexcept { return iterator{ *this, front_pos_, empty() }; }
        constexpr iterator end() noexcept { return iterator{ *this, empty() ? front_pos_ : next_pos(back_pos_), true }; }
        constexpr const_iterator begin() const noexcept { return cbegin(); }
        constexpr const_iterator end() const noexcept { return cend(); }
        constexpr const_iterator cbegin() const noexcept { return const_iterator{ *this, front_pos_, empty() }; }
        constexpr const_iterator cend() const noexcept { return const_iterator{ *this, empty() ? front_pos_ : next_pos(back_pos_), true }; }

        auto operator<=>(const circular_buffer& other) const noexcept = default;

    private:
        friend struct fmt::formatter<circular_buffer>;

        circular_buffer() = default;

        [[nodiscard]] constexpr size_type next_pos(size_type pos) const noexcept { return (++pos % capacity_); }
        [[nodiscard]] constexpr size_type prev_pos(size_type pos) const noexcept { return (pos == 0) ? (capacity_ - 1) : --pos; }

        constexpr void throw_if_empty() const {
            if (empty()) {
                throw std::runtime_error{ "trying to access an empty circular_buffer." };
            }
        }

        std::vector<T> container_{};
        size_type size_{};
        size_type capacity_{};
        size_type front_pos_{};
        size_type back_pos_{};
    };

    template <typename T>
    auto begin(circular_buffer<T>& cb) -> decltype(cb.begin()) { return cb.begin(); }
    template <typename T>
    auto end(circular_buffer<T>& cb) -> decltype(cb.end()) { return cb.end(); }
    template <typename T>
    auto begin(const circular_buffer<T>& cb) -> decltype(cb.cbegin()) { return cb.cbegin(); }
    template <typename T>
    auto end(const circular_buffer<T>& cb) -> decltype(cb.cend()) { return cb.cend(); }
    template <typename T>
    auto cbegin(const circular_buffer<T>& cb) -> decltype(cb.cbegin()) { return cb.cbegin(); }
    template <typename T>
    auto cend(const circular_buffer<T>& cb) -> decltype(cb.cend()) { return cb.cend(); }
}  // namespace tmcppc::data_structures


template <typename T>
struct fmt::is_range<tmcppc::data_structures::circular_buffer<T>, char> : std::false_type {};


template <typename T>
struct fmt::formatter<tmcppc::data_structures::circular_buffer<T>> {
    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const tmcppc::data_structures::circular_buffer<T>& cb, FormatContext& ctx) const -> decltype(ctx.out()) {
        return fmt::format_to(ctx.out(), "[{}]", fmt::join(cb.container_, ", "));
    }
};
