#pragma once

#include <array>
#include <iostream>  // cout
#include <string>


// Notes
// 
// std::array is movable if its elements are movable
// That makes implementation of move constructor and move assignment operator unnecessary for the IPv4 class,
// since all the members are movable
// Copy construction, copy assignment operator and destructor are also unnecesary
// 
// operator<< and operator>> implemented as non-member functions and friends

class IPv4
{
public:
    IPv4() = default;
    explicit IPv4(const std::string& address);
    explicit IPv4(const char* address);
    explicit constexpr IPv4(unsigned long address);
    constexpr IPv4(unsigned char o0, unsigned char o1, unsigned char o2, unsigned char o3);

    [[nodiscard]] std::string to_string() const;
    [[nodiscard]] constexpr unsigned long to_ulong() const noexcept;

    IPv4& operator++();
    IPv4 operator++(int);
private:
    friend bool operator==(const IPv4& lhs, const IPv4& rhs);
    friend bool operator<(const IPv4& lhs, const IPv4& rhs);
    friend std::ostream& operator<<(std::ostream& os, const IPv4& ipv4);
    friend std::istream& operator>>(std::istream& is, IPv4& ipv4);

    std::array<unsigned char, 4> _octets{};
};
