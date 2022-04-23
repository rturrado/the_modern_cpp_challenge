#pragma once

#include "ipv4.h"


namespace tmcppc {
    class ipv4_iterator
    {
    private:
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = ipv4;
        using pointer = ipv4*;
        using reference = const ipv4&;

    public:
        explicit ipv4_iterator(const value_type& value) : value_{ value } {}

        auto operator*() const { return value_; }
        auto operator->() const { return &value_; }

        ipv4_iterator& operator++() { ++value_; return *this; }
        ipv4_iterator operator++(int) { ipv4_iterator tmp{ *this }; ++(*this); return tmp; }

        bool operator==(const ipv4_iterator& other) const { return value_ == other.value_; }
        bool operator!=(const ipv4_iterator& other) const { return value_ != other.value_; }

    private:
        value_type value_;
    };

    class ipv4_range
    {
    public:
        ipv4_range(const ipv4& start, const ipv4& end) : start_{ start }, end_{ end } { ++end_; }
        auto begin() { return ipv4_iterator{ start_ }; }
        auto end() { return ipv4_iterator{ end_ }; }
        auto begin() const { return ipv4_iterator{ start_ }; };
        auto end() const { return ipv4_iterator{ end_ }; }
        auto cbegin() const { return ipv4_iterator{ start_ }; };
        auto cend() const { return ipv4_iterator{ end_ }; }
    private:
        ipv4 start_;
        ipv4 end_;
    };
}  // namespace tmcppc
