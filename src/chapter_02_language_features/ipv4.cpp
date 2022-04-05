#include "chapter_02_language_features/ipv4.h"

#include <algorithm>
#include <cstdint>  // uint8_t, uint32_t
#include <ios>
#include <numeric>
#include <regex>
#include <sstream>
#include <string>


// Notes
// 
// uint8_t is an alias for unsigned char and thus treated as char by streams
// We use a temporary string in the string constructor, and a std::to_string conversion in the octets constructor
IPv4::IPv4(const std::string& address)
{
    std::istringstream iss{ address };
    std::for_each(_octets.begin(), _octets.end(),
        [&iss, temp = std::string{}](uint8_t& n) mutable {
            std::getline(iss, temp, '.');
            n = std::stoi(temp);
        }
    );
}

IPv4::IPv4(const char* address)
    : IPv4{ std::string(address) }
{
}

constexpr IPv4::IPv4(uint32_t address)
    : _octets{ (address >> 24) & 0xff, (address >> 16) & 0xff, (address >> 8) & 0xff, address & 0xff }
{
}

constexpr IPv4::IPv4(uint8_t o0, uint8_t o1, uint8_t o2, uint8_t o3)
    : _octets{ o0, o1, o2, o3 }
{
}

[[nodiscard]] std::string IPv4::to_string() const
{
    std::ostringstream oss;
    oss << *this;
    return oss.str();
}

[[nodiscard]] constexpr uint32_t IPv4::to_ulong() const noexcept
{
    return (_octets[0] << 24) | (_octets[1] << 16) | (_octets[2] << 8) | _octets[3];
}

IPv4& IPv4::operator++()
{
    *this = IPv4{ this->to_ulong() + 1 };
    return *this;
}

IPv4 IPv4::operator++(int)
{
    IPv4 tmp{ *this }; ++(*this);
    return tmp;
}

/* friend */
bool operator==(const IPv4& lhs, const IPv4& rhs)
{
    return lhs._octets == rhs._octets;
}

/* friend */
bool operator<(const IPv4& lhs, const IPv4& rhs)
{
    return lhs.to_ulong() < rhs.to_ulong();
}

/* friend */
std::ostream& operator<<(std::ostream& os, const IPv4& ipv4)
{
    std::for_each(ipv4._octets.cbegin(), ipv4._octets.cend(),
        [&os, first = true](uint8_t n) mutable {
            os << (first ? "" : ".") << std::to_string(n);
            first = false;
        }
    );
    return os;
}

/* friend */
std::istream& operator>>(std::istream& is, IPv4& ipv4)
{
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
