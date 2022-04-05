#ifndef IPV4_RANGE_H
#define IPV4_RANGE_H

#include "IPv4.h"

class IPv4Iterator
{
private:
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = IPv4;
    using pointer = IPv4*;
    using reference = const IPv4&;

public:
    explicit IPv4Iterator(const value_type& value) : _value{ value } {}

    auto operator*() const { return _value; }
    auto operator->() const { return &_value; }

    IPv4Iterator& operator++() { ++_value; return *this; }
    IPv4Iterator operator++(int) { IPv4Iterator tmp{ *this }; ++(*this); return tmp; }

    bool operator==(const IPv4Iterator& other) const { return _value == other._value; }
    bool operator!=(const IPv4Iterator& other) const { return _value != other._value; }

private:
    value_type _value;
};

class IPv4Range
{
public:
    IPv4Range(const IPv4& start, const IPv4& end) : _start{ start }, _end{ end } { ++_end; }
    auto begin() { return IPv4Iterator{ _start }; }
    auto end() { return IPv4Iterator{ _end }; }
    auto cbegin() const { return IPv4Iterator{ _start }; };
    auto cend() const { return IPv4Iterator{ _end }; }
    auto begin() const { return IPv4Iterator{ _start }; };
    auto end() const { return IPv4Iterator{ _end }; }
private:
    IPv4 _start;
    IPv4 _end;
};

#endif  // IPV4_RANGE_H
