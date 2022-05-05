#pragma once

#include <algorithm>
#include <fmt/format.h>
#include <fmt/ostream.h>
#include <fmt/ranges.h>
#include <format>
#include <iostream>  // cout
#include <iterator>
#include <ranges>
#include <sstream>
#include <stdexcept>
#include <utility>  // exchange
#include <vector>


namespace tmcppc {
    template <typename T>
    concept printable = requires(std::ostream& os, T t) { os << t; };

    template <printable T>
    class array_2d {
        class const_iterator {
        public:
            using difference_type = std::ptrdiff_t;
            using iterator_category = std::random_access_iterator_tag;
            using pointer = const T*;
            using reference = const T&;
            using value_type = T;

            using TPtr_ = T*;

            constexpr const_iterator() noexcept : ptr_{} {}
            constexpr const_iterator(TPtr_ ptr) noexcept : ptr_{ ptr } {}
            constexpr reference operator*() const noexcept { return *ptr_; }
            constexpr pointer operator->() const noexcept { return ptr_; }
            constexpr const_iterator& operator++() noexcept { ++ptr_; return *this; }
            constexpr const_iterator operator++(int) noexcept { const_iterator tmp{ *this }; ++(*this); return tmp; }
            constexpr const_iterator& operator--() noexcept { --ptr_; return *this; }
            constexpr const_iterator operator--(int) noexcept { const_iterator tmp{ *this }; --(*this); return tmp; }
            constexpr const_iterator& operator+=(const difference_type offset) noexcept { ptr_ += offset; return *this; }
            constexpr const_iterator operator+(const difference_type offset) const noexcept { const_iterator tmp{ *this }; tmp += offset; return tmp; }
            constexpr const_iterator& operator-=(const difference_type offset) noexcept { *this += -offset; return *this; }
            constexpr const_iterator operator-(const difference_type offset) const noexcept { const_iterator tmp{ *this }; tmp -= offset; return tmp; }
            constexpr difference_type operator-(const const_iterator& other) const noexcept { return ptr_ - other.ptr_; }
            constexpr bool operator==(const const_iterator& other) const noexcept { return ptr_ == other.ptr_; }
            constexpr bool operator<=>(const const_iterator& other) const noexcept { return ptr_ <=> other.ptr_; }

        protected:
            TPtr_ ptr_{ nullptr };
        };

        class iterator : public const_iterator {
            using MyBase_ = const_iterator;

        public:
            using difference_type = std::ptrdiff_t;
            using iterator_category = std::random_access_iterator_tag;
            using pointer = T*;
            using reference = T&;
            using value_type = T;

            constexpr reference operator*() const noexcept { return const_cast<reference>(MyBase_::operator*()); }
            constexpr pointer operator->() const noexcept { return this->ptr_; }
            constexpr iterator& operator++() noexcept { MyBase_::operator++(); return *this; }
            constexpr iterator operator++(int) noexcept { iterator tmp{ *this }; MyBase_::operator++(); return tmp; }
            constexpr iterator& operator--() noexcept { MyBase_::operator--(); return *this; }
            constexpr iterator operator--(int) noexcept { iterator tmp{ *this }; MyBase_::operator--(); return tmp; }
            constexpr iterator& operator+=(const difference_type offset) noexcept { MyBase_::operator+=(offset); return *this; }
            constexpr iterator operator+(const difference_type offset) const noexcept { iterator tmp{ *this }; tmp += offset; return tmp; }
            constexpr iterator& operator-=(const difference_type offset) noexcept { MyBase_::operator-=(offset); return *this; }
            constexpr iterator operator-(const difference_type offset) const noexcept { iterator tmp{ *this }; tmp -= offset; return tmp; }
            constexpr difference_type operator-(const iterator& other) const noexcept { return this->ptr_ - other.ptr_; }
        };

        template <typename Iter>
        class reverse_iterator {
        public:
            using difference_type = Iter::difference_type;
            using iterator_category = Iter::iterator_category;
            using pointer = Iter::pointer;
            using reference = Iter::reference;
            using value_type = Iter::value_type;

            template <typename>
            friend class reverse_iterator;

            constexpr reverse_iterator(Iter it) noexcept : current_{ std::move(it) } {}
            template <typename OtherIter>
            constexpr reverse_iterator(const reverse_iterator<OtherIter>& other) noexcept : current_{ other.current_ } {}
            constexpr reference operator*() const noexcept { Iter tmp{ current_ }; return *(--tmp); }
            constexpr pointer operator->() const noexcept { Iter tmp{ current_ }; --tmp; return tmp->operator->(); }
            constexpr reverse_iterator& operator++() noexcept { --current_; return *this; }
            constexpr reverse_iterator operator++(int) noexcept { reverse_iterator tmp{ *this }; --current_; return tmp; }
            constexpr reverse_iterator& operator--() noexcept { ++current_; return *this; }
            constexpr reverse_iterator operator--(int) noexcept { reverse_iterator tmp{ *this }; ++current_; return tmp; }
            constexpr reverse_iterator& operator+=(const difference_type offset) noexcept { current_ -= offset; return *this; }
            constexpr reverse_iterator operator+(const difference_type offset) const noexcept { return reverse_iterator{ current_ - offset }; }
            constexpr reverse_iterator& operator-=(const difference_type offset) noexcept { current_ += offset; return *this; }
            constexpr reverse_iterator operator-(const difference_type offset) const noexcept { return reverse_iterator{ current_ + offset }; }
            template <typename OtherIter>
            constexpr difference_type operator-(const reverse_iterator<OtherIter>& other) const noexcept { return current_ - other.current_; }
            template <typename OtherIter>
            constexpr bool operator==(const reverse_iterator<OtherIter>& other) const noexcept { return current_ == other.current_; }
            template <typename OtherIter>
            constexpr bool operator<=>(const reverse_iterator<OtherIter>& other) const noexcept { return current_ <=> other.current_; }

        protected:
            Iter current_{};
        };

    public:
        using const_reference = const T&;
        using const_reverse_iterator = reverse_iterator<const_iterator>;
        using reference = T&;
        using reverse_iterator_t = reverse_iterator<iterator>;
        using size_type = std::vector<T>::size_type;
        using value_type = T;

    private:
        void verify_indexed_access(
            size_type index,
            size_type num_elems,
            const std::string& index_text,
            const std::string& num_elems_text) const {

            if (index >= num_elems) {
                std::ostringstream oss{};
                oss << index_text << " (zero based index) = " << index << " and " << num_elems_text << " = " << num_elems << ".";
                throw std::out_of_range{ oss.str() };
            }
        };

    public:
        array_2d() : width_{ 0 }, height_{ 0 } {}
        array_2d(size_type width, size_type height) : width_{ width }, height_{ height } { data_.resize(width * height); }
        array_2d(std::initializer_list<std::initializer_list<T>>&& data) {
            height_ = data.size();
            width_ = (height_ ? data.begin()->size() : 0);

            for (auto&& v : data) {
                for (auto&& t : v) {
                    data_.emplace_back(t);
                }
            }
        }
        array_2d(const array_2d& other) = default;
        array_2d& operator=(const array_2d& other) = default;
        array_2d(array_2d&& other) noexcept {
            data_ = std::move(other.data_);
            width_ = other.width_;
            height_ = other.height_;
            other.width_ = 0;
            other.height_ = 0;
        }
        array_2d& operator=(array_2d&& other) noexcept {
            data_ = std::move(other.data_);
            width_ = other.width_;
            height_ = other.height_;
            other.width_ = 0;
            other.height_ = 0;
            return *this;
        }
        ~array_2d() = default;

        [[nodiscard]] constexpr reference at(size_type row, size_type col) {
            verify_indexed_access(row, height_, "row", "height");
            verify_indexed_access(col, width_, "left_col", "width");

            return data_.at(row * width_ + col);
        }

        [[nodiscard]] constexpr const_reference at(size_type row, size_type col) const {
            verify_indexed_access(row, height_, "row", "height");
            verify_indexed_access(col, width_, "left_col", "width");

            return data_.at(row * width_ + col);
        }

        [[nodiscard]] constexpr T* data() noexcept { return data_.data(); }
        [[nodiscard]] constexpr const T* data() const noexcept { return data_.data(); }

        [[nodiscard]] constexpr bool empty() const noexcept { return data_.empty(); }
        [[nodiscard]] constexpr size_type height() const noexcept { return height_; }
        [[nodiscard]] constexpr size_type width() const noexcept { return width_; }

        [[nodiscard]] constexpr iterator begin() noexcept { return iterator(data_.data()); }
        [[nodiscard]] constexpr iterator end() noexcept { return iterator(data_.data() + data_.size()); }
        [[nodiscard]] constexpr const_iterator begin() const noexcept { return const_iterator(const_cast<T*>(data_.data())); }
        [[nodiscard]] constexpr const_iterator end() const noexcept { return const_iterator(const_cast<T*>(data_.data()) + data_.size()); }
        [[nodiscard]] constexpr reverse_iterator_t rbegin() noexcept { return reverse_iterator_t(end()); }
        [[nodiscard]] constexpr reverse_iterator_t rend() noexcept { return reverse_iterator_t(begin()); }
        [[nodiscard]] constexpr const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); }
        [[nodiscard]] constexpr const_reverse_iterator rend() const noexcept { return const_reverse_iterator(begin()); }
        [[nodiscard]] constexpr const_iterator cbegin() const noexcept { return begin(); }
        [[nodiscard]] constexpr const_iterator cend() const noexcept { return end(); }
        [[nodiscard]] constexpr const_reverse_iterator crbegin() const noexcept { return rbegin(); }
        [[nodiscard]] constexpr const_reverse_iterator crend() const noexcept { return rend(); }

        [[nodiscard]] constexpr auto operator<=>(const array_2d& other) const = default;

        constexpr void swap(size_type left_row, size_type left_col, size_type right_row, size_type right_col) {
            verify_indexed_access(left_row, height_, "left_row", "height");
            verify_indexed_access(right_row, height_, "right_row", "height");
            verify_indexed_access(left_col, width_, "left_col", "width");
            verify_indexed_access(right_col, width_, "right_col", "width");

            auto left_it{ begin() + left_row * width_ + left_col };
            auto right_it{ begin() + right_row * width_ + right_col };
            *right_it = std::exchange(*left_it, *right_it);
        }

        [[nodiscard]] constexpr auto sub_array(
            size_type begin_row,
            size_type begin_col,
            size_type sub_array_width,
            size_type sub_array_height) const {

            auto end_row{ begin_row + sub_array_height - 1 };
            auto end_col{ begin_col + sub_array_width - 1 };

            verify_indexed_access(begin_row, height_, "begin_row", "height");
            verify_indexed_access(end_row, height_, "end_row", "height");
            verify_indexed_access(begin_col, width_, "begin_col", "width");
            verify_indexed_access(end_col, width_, "end_col", "width");

            array_2d sub_array(sub_array_width, sub_array_height);
            for (auto row{ begin_row }; row <= end_row; ++row) {
                for (auto col{ begin_col }; col <= end_col; ++col) {
                    sub_array.at(row - begin_row, col - begin_col) = data_[row * width_ + col];
                }
            }

            return sub_array;
        }

        [[nodiscard]] constexpr auto row_as_vector(size_type row) const {
            verify_indexed_access(row, height_, "row", "height");

            return std::vector<T>(begin() + row * width_, begin() + (row + 1) * width_);
        }

        [[nodiscard]] constexpr auto column_as_vector(size_type column) const {
            verify_indexed_access(column, width_, "column", "width");

            std::vector<T> column_vector{};
            for (auto row{ 0 }; row < height_; ++row) {
                column_vector.emplace_back(data_[row * width_ + column]);
            }
            return column_vector;
        }

        friend auto get_column_width(const array_2d& arr, size_type column) {
            auto column_vector{ arr.column_as_vector(column) };
            std::ostringstream oss{};
            std::for_each(column_vector.cbegin(), column_vector.cend(),
                [&oss](const auto& val) { oss << val; oss.seekp(0); });
            return oss.str().size();
        }

        friend auto get_column_widths(const array_2d& arr) {
            if (arr.empty()) {
                return std::vector<size_t>{};
            }
            std::vector<size_t> column_widths(arr.width_);
            for (auto col{ 0 }; col < arr.width_; ++col) {
                column_widths[col] = get_column_width(arr, col);
            }
            return column_widths;
        }

        friend std::ostream& operator<<(std::ostream& os, const array_2d& arr) {
            fmt::print(os, "{}", arr);
            return os;
        }

    private:
        friend struct fmt::formatter<array_2d>;

        std::vector<T> data_;
        size_type width_;
        size_type height_;
    };
}  // namespace tmcppc


template <tmcppc::printable T>
struct fmt::is_range<tmcppc::array_2d<T>, char> : std::false_type {};


template <tmcppc::printable T>
struct fmt::formatter<tmcppc::array_2d<T>> {
    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const tmcppc::array_2d<T>& arr, FormatContext& ctx) const -> decltype(ctx.out()) {
        if (arr.empty()) {
            fmt::format_to(ctx.out(), "{}", "[]");
        }
        else {
            auto column_widths{ get_column_widths(arr) };

            for (auto row{ 0 }; row < arr.height_; ++row) {
                fmt::format_to(ctx.out(), "{}{}", (row == 0 ? "" : "\n"), "[ ");
                for (auto col{ 0 }; col < arr.width_; ++col) {
                    fmt::format_to(ctx.out(), "{0}{2:>{1}}", (col == 0 ? "" : ", "), column_widths[col], arr.at(row, col));
                }
                fmt::format_to(ctx.out(), "{}", " ]");
            }
        }
        return ctx.out();
    }
};
