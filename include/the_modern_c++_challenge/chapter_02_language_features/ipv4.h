#pragma once

#include <algorithm>
#include <array>
#include <cstdint>  // uint8_t, uint32_t
#include <ios>
#include <istream>
#include <numeric>
#include <ostream>
#include <regex>
#include <sstream>
#include <string>


// Notes
// 
// uint8_t is an alias for unsigned char and thus treated as char by streams
// We use a temporary string in the string constructor, and a std::to_string conversion in the octets constructor
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

    explicit IPv4(const std::string& address) {
        std::istringstream iss{ address };
        std::for_each(_octets.begin(), _octets.end(),
            [&iss, temp = std::string{}](std::uint8_t& n) mutable {
            std::getline(iss, temp, '.');
            n = std::stoi(temp);
        }
        );
    }

    explicit IPv4(const char* address)
        : IPv4{ std::string(address) }
    {}

    explicit constexpr IPv4(std::uint32_t address)
        : _octets{ (address >> 24) & 0xff, (address >> 16) & 0xff, (address >> 8) & 0xff, address & 0xff }
    {}

    constexpr IPv4(std::uint8_t o0, std::uint8_t o1, std::uint8_t o2, std::uint8_t o3)
        : _octets{ o0, o1, o2, o3 }
    {}

    [[nodiscard]] std::string to_string() const {
        std::ostringstream oss;
        oss << *this;
        return oss.str();
    }

    [[nodiscard]] constexpr unsigned long to_ulong() const noexcept {
        return static_cast<unsigned long>((_octets[0] << 24) | (_octets[1] << 16) | (_octets[2] << 8) | _octets[3]);
    }

    IPv4& operator++() {
        *this = IPv4{ this->to_ulong() + 1 };
        return *this;
    }

    IPv4 operator++(int) {
        IPv4 tmp{ *this }; ++(*this);
        return tmp;
    }

private:
    friend bool operator==(const IPv4& lhs, const IPv4& rhs) {
        return lhs._octets == rhs._octets;
    }

    friend bool operator<(const IPv4& lhs, const IPv4& rhs) {
        return lhs.to_ulong() < rhs.to_ulong();
    }

    friend std::ostream& operator<<(std::ostream& os, const IPv4& ipv4) {
        std::for_each(ipv4._octets.cbegin(), ipv4._octets.cend(),
            [&os, first = true](std::uint8_t n) mutable {
            os << (first ? "" : ".") << std::to_string(n);
            first = false;
        }
        );
        return os;
    }

    friend std::istream& operator>>(std::istream& is, IPv4& ipv4) {
        bool error{ false };

        // Read stream into a string
        std::string str{};
        is >> str;

        // Check string is a valid IPv4 address
        std::regex pattern{ R"(^([[:digit:]]{1,3})\.([[:digit:]]{1,3})\.([[:digit:]]{1,3})\.([[:digit:]]{1,3})$)" };
        std::smatch matches;
        if (std::regex_search(str, matches, pattern))
        {
            int i{ 0 };
            for (auto match = std::next(cbegin(matches)); match != cend(matches); ++match)
            {
                int octet = std::stoi(*match);
                if (octet > 255)
                {
                    error = true;  // an octet is bigger than 255
                    break;
                }
                ipv4._octets[i++] = octet;
            }
        }
        else
        {
            error = true;  // string format is not correct
        }

        if (error)
        {
            is.setstate(std::ios_base::failbit);
            ipv4._octets.fill(0);
        }

        return is;
    }

    std::array<std::uint8_t, 4> _octets{};
};
