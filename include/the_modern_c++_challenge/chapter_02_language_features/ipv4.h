#pragma once

#include <array>
#include <cstdint>  // uint32_t
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
    explicit constexpr IPv4(uint32_t address);
    constexpr IPv4(uint8_t o0, uint8_t o1, uint8_t o2, uint8_t o3);

    std::string to_string() const;
    constexpr uint32_t to_ulong() const noexcept;

    IPv4& operator++();
    IPv4 operator++(int);
private:
    friend bool operator==(const IPv4& lhs, const IPv4& rhs);
    friend bool operator<(const IPv4& lhs, const IPv4& rhs);
    friend std::ostream& operator<<(std::ostream& os, const IPv4& ipv4);
    friend std::istream& operator>>(std::istream& is, IPv4& ipv4);

    std::array<uint8_t, 4> _octets{};
};
