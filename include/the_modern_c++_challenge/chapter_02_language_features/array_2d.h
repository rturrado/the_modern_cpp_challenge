#pragma once

#include <algorithm>
#include <format>
#include <iostream>  // cout
#include <iterator>
#include <ranges>
#include <sstream>
#include <stdexcept>
#include <vector>


template <typename T>
concept printable = requires(std::ostream& os, T t) { os << t; };

template <printable T>
class Array2D
{
    class ConstIterator
    {
    public:
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::random_access_iterator_tag;
        using pointer = const T*;
        using reference = const T&;
        using value_type = T;

        using _TPtr = T*;

        constexpr ConstIterator() noexcept : _ptr{} {}
        constexpr ConstIterator(_TPtr ptr) noexcept : _ptr{ ptr } {}
        constexpr reference operator*() const noexcept { return *_ptr; }
        constexpr pointer operator->() const noexcept { return _ptr; }
        constexpr ConstIterator& operator++() noexcept { ++_ptr; return *this; }
        constexpr ConstIterator operator++(int) noexcept { ConstIterator tmp{ *this }; ++(*this); return tmp; }
        constexpr ConstIterator& operator--() noexcept { --_ptr; return *this; }
        constexpr ConstIterator operator--(int) noexcept { ConstIterator tmp{ *this }; --(*this); return tmp; }
        constexpr ConstIterator& operator+=(const difference_type offset) noexcept { _ptr += offset; return *this; }
        constexpr ConstIterator operator+(const difference_type offset) const noexcept { ConstIterator tmp{ *this }; tmp += offset; return tmp; }
        constexpr ConstIterator& operator-=(const difference_type offset) noexcept { *this += -offset; return *this; }
        constexpr ConstIterator operator-(const difference_type offset) const noexcept { ConstIterator tmp{ *this }; tmp -= offset; return tmp; }
        constexpr difference_type operator-(const ConstIterator& other) const noexcept { return _ptr - other._ptr; }
        constexpr bool operator==(const ConstIterator& other) const noexcept { return _ptr == other._ptr; }
        constexpr bool operator<=>(const ConstIterator& other) const noexcept { return _ptr <=> other._ptr; }

    protected:
        _TPtr _ptr{ nullptr };
    };

    class Iterator : public ConstIterator
    {
        using _MyBase = ConstIterator;

    public:
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::random_access_iterator_tag;
        using pointer = T*;
        using reference = T&;
        using value_type = T;
    
        constexpr reference operator*() const noexcept { return const_cast<reference>(_MyBase::operator*()); }
        constexpr pointer operator->() const noexcept { return this->_ptr; }
        constexpr Iterator& operator++() noexcept { _MyBase::operator++(); return *this; }
        constexpr Iterator operator++(int) noexcept { Iterator tmp{ *this }; _MyBase::operator++(); return tmp; }
        constexpr Iterator& operator--() noexcept { _MyBase::operator--(); return *this; }
        constexpr Iterator operator--(int) noexcept { Iterator tmp{ *this }; _MyBase::operator--(); return tmp; }
        constexpr Iterator& operator+=(const difference_type offset) noexcept { _MyBase::operator+=(offset); return *this; }
        constexpr Iterator operator+(const difference_type offset) const noexcept { Iterator tmp{ *this }; tmp += offset; return tmp; }
        constexpr Iterator& operator-=(const difference_type offset) noexcept { _MyBase::operator-=(offset); return *this; }
        constexpr Iterator operator-(const difference_type offset) const noexcept { Iterator tmp{ *this }; tmp -= offset; return tmp; }
        constexpr difference_type operator-(const Iterator& other) const noexcept { return this->_ptr - other._ptr; }
    };

    template <typename Iter>
    class ReverseIterator
    {
    public:
        using difference_type = Iter::difference_type;
        using iterator_category = Iter::iterator_category;
        using pointer = Iter::pointer;
        using reference = Iter::reference;
        using value_type = Iter::value_type;

        template <typename>
        friend class ReverseIterator;

        constexpr ReverseIterator(Iter it) noexcept : _current{ std::move(it) } {}
        template <typename OtherIter>
        constexpr ReverseIterator(const ReverseIterator<OtherIter>& other) noexcept : _current{ other._current } {}
        constexpr reference operator*() const noexcept { Iter tmp{ _current }; return *(--tmp); }
        constexpr pointer operator->() const noexcept { Iter tmp{ _current }; --tmp; return tmp->operator->(); }
        constexpr ReverseIterator& operator++() noexcept { --_current; return *this; }
        constexpr ReverseIterator operator++(int) noexcept { ReverseIterator tmp{ *this }; --_current; return tmp; }
        constexpr ReverseIterator& operator--() noexcept { ++_current; return *this; }
        constexpr ReverseIterator operator--(int) noexcept { ReverseIterator tmp{ *this }; ++_current; return tmp; }
        constexpr ReverseIterator& operator+=(const difference_type offset) noexcept { _current -= offset; return *this; }
        constexpr ReverseIterator operator+(const difference_type offset) const noexcept { return ReverseIterator{ _current - offset }; }
        constexpr ReverseIterator& operator-=(const difference_type offset) noexcept { _current += offset; return *this; }
        constexpr ReverseIterator operator-(const difference_type offset) const noexcept { return ReverseIterator{ _current + offset }; }
        template <typename OtherIter>
        constexpr difference_type operator-(const ReverseIterator<OtherIter>& other) const noexcept { return _current - other._current; }
        template <typename OtherIter>
        constexpr bool operator==(const ReverseIterator<OtherIter>& other) const noexcept { return _current == other._current; }
        template <typename OtherIter>
        constexpr bool operator<=>(const ReverseIterator<OtherIter>& other) const noexcept { return _current <=> other._current; }

    protected:
        Iter _current{};
    };

public:
    using const_iterator = ConstIterator;
    using const_reference = const T&;
    using const_reverse_iterator = ReverseIterator<ConstIterator>;
    using iterator = Iterator;
    using reference = T&;
    using reverse_iterator = ReverseIterator<iterator>;
    using size_type = std::vector<T>::size_type;
    using value_type = T;

private:
    void verify_indexed_access(
        size_type index,
        size_type num_elems,
        const std::string& index_text,
        const std::string& num_elems_text) const
    {

        if (index >= num_elems)
        {
            std::ostringstream oss{};
            oss << index_text << " (zero based index) = " << index << " and " << num_elems_text << " = " << num_elems << ".";
            throw std::out_of_range{ oss.str() };
        }
    };

public:
    Array2D() : _width{ 0 }, _height{ 0 } {}
    Array2D(size_type width, size_type height) : _width{ width }, _height{ height } { _data.resize(width * height); }
    Array2D(std::initializer_list<std::initializer_list<T>>&& data)
    {
        _height = data.size();
        _width = (_height ? (*data.begin()).size() : 0);

        for (auto&& v : data)
        {
            for (auto&& t : v)
            {
                _data.emplace_back(t);
            }
        }
    }

    [[nodiscard]] constexpr reference at(size_type row, size_type col)
    {
        verify_indexed_access(row, _height, "row", "height");
        verify_indexed_access(col, _width, "left_col", "width");

        return _data.at(row * _width + col);
    }

    [[nodiscard]] constexpr const_reference at(size_type row, size_type col) const
    {
        verify_indexed_access(row, _height, "row", "height");
        verify_indexed_access(col, _width, "left_col", "width");

        return _data.at(row * _width + col);
    }

    [[nodiscard]] constexpr T* data() noexcept { return const_cast<T*>(_data.data()); }
    [[nodiscard]] constexpr const T* data() const noexcept { return _data.data(); }
    
    [[nodiscard]] constexpr size_type height() const noexcept { return _height; }
    [[nodiscard]] constexpr size_type width() const noexcept { return _width; }

    [[nodiscard]] constexpr iterator begin() const noexcept { return iterator(const_cast<T*>(_data.data())); }
    [[nodiscard]] constexpr iterator end() const noexcept { return iterator(const_cast<T*>(_data.data()) + _data.size()); }
    [[nodiscard]] constexpr const_iterator cbegin() const noexcept { return begin(); }
    [[nodiscard]] constexpr const_iterator cend() const noexcept { return end(); }
    [[nodiscard]] constexpr reverse_iterator rbegin() const noexcept { return reverse_iterator(end()); }
    [[nodiscard]] constexpr reverse_iterator rend() const noexcept { return reverse_iterator(begin()); }
    [[nodiscard]] constexpr const_reverse_iterator crbegin() const noexcept { return rbegin(); }
    [[nodiscard]] constexpr const_reverse_iterator crend() const noexcept { return rend(); }

    constexpr void swap(size_type left_row, size_type left_col, size_type right_row, size_type right_col)
    {
        verify_indexed_access(left_row, _height, "left_row", "height");
        verify_indexed_access(right_row, _height, "right_row", "height");
        verify_indexed_access(left_col, _width, "left_col", "width");
        verify_indexed_access(right_col, _width, "right_col", "width");

        auto left_it{ begin() + left_row * _width + left_col };
        auto right_it{ begin() + right_row * _width + right_col };
        T tmp{ *left_it }; *left_it = *right_it; *right_it = tmp;
    }

    [[nodiscard]] constexpr auto sub_array(
        size_type begin_row,
        size_type begin_col,
        size_type sub_array_width,
        size_type sub_array_height) const
    {
        verify_indexed_access(begin_row, _height, "begin_row", "height");
        verify_indexed_access(begin_row + sub_array_height, _height, "begin_row + sub_array_height", "height");
        verify_indexed_access(begin_col, _width, "begin_col", "width");
        verify_indexed_access(begin_col + sub_array_width, _width, "begin_col + sub_array_width", "width");

        Array2D sub_array(sub_array_width, sub_array_height);
        for (auto row = begin_row; row < begin_row + sub_array_height; ++row)
        {
            for (auto col = begin_col; col < begin_col + sub_array_width; ++col)
            {
                sub_array.at(row - begin_row, col - begin_col) = _data[row * _width + col];
            }
        }

        return sub_array;
    }

    [[nodiscard]] constexpr auto row_as_vector(size_type row) const
    {
        verify_indexed_access(row, _height, "row", "height");

        return std::vector<T>(begin() + row * _width, begin() + (row + 1) * _width);
    }

    [[nodiscard]] constexpr auto column_as_vector(size_type column) const
    {
        verify_indexed_access(column, _width, "column", "width");

        std::vector<T> column_vector{};
        for (auto row = 0; row < _height; ++row)
        {
            column_vector.emplace_back(_data[row * _width + column]);
        }
        return column_vector;
    }

    friend auto get_column_width(const Array2D& arr, size_type column)
    {
        auto column_vector = arr.column_as_vector(column);
        std::ostringstream oss{};
        std::for_each(column_vector.cbegin(), column_vector.cend(),
            [&oss](const auto& val) { oss << val; oss.seekp(0); });
        return oss.str().size();
    }

    friend auto get_column_widths(const Array2D& arr)
    {
        std::vector<size_t> column_widths{};

        for (auto col{0}; col < arr._height; ++col)
        {
            column_widths.push_back(get_column_width(arr, col));
        }

        return column_widths;
    }

    friend std::ostream& operator<<(std::ostream& os, const Array2D& arr)
    {
        auto print_left_border = [&os](auto row, auto num_rows) {
            char c{ static_cast<char>(179) };
            if (row == 0) { c = static_cast<char>(218); }
            else if (row == num_rows - 1) { c = static_cast<char>(192); }
            os << c;
        };

        auto print_right_border = [&os](auto row, auto num_rows) {
            char c{ static_cast<char>(179) };
            if (row == 0) { c = static_cast<char>(191); }
            else if (row == num_rows - 1) { c = static_cast<char>(217); }
            os << " " << c;
        };

        auto column_widths = get_column_widths(arr);

        for (auto row = 0; row < arr._height; ++row)
        {
            print_left_border(row, arr._height);
            for (auto col = 0; col < arr._width; ++col)
            {
                os << (col == 0 ? " " : ", ") << std::format("{1:>{0}}", column_widths[col], arr.at(row, col));
            }
            print_right_border(row, arr._height);
            os << "\n";
        }
        return os << "\n";
    }

private:
    std::vector<T> _data;
    size_type _width{ 0 };
    size_type _height{ 0 };
};

template <printable T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
{
    os << "[";
    std::for_each(v.cbegin(), v.cend(), [ &os, first = true ](const auto& e) mutable {
        os << (first ? " " : ", ") << e;
        first = false;
    });
    return os << " ]\n\n";
}
