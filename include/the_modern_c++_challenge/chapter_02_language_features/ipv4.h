#pragma once

#include <algorithm>
#include <array>
#include <cstdint>  // uint8_t, uint32_t
#include <fmt/format.h>
#include <ios>
#include <istream>
#include <numeric>
#include <ostream>
#include <regex>
#include <sstream>
#include <stdexcept>  // runtime_error
#include <string>


struct invalid_ipv4_address_error : public std::runtime_error {
    invalid_ipv4_address_error(const std::string& address) : std::runtime_error{ "" } {
        message_ = fmt::format("{}: {}", message_, address);
    }
    const char* what() const noexcept { return message_.c_str(); }
private:
    std::string message_{ "invalid IPv4 address" };
};


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
class ipv4
{
public:
    ipv4() = default;

    explicit ipv4(const std::string& address) {
        if (not validate_ipv4_address(address, *this)) {
            throw invalid_ipv4_address_error{ address };
        }
    }

    explicit ipv4(const char* address)
        : ipv4{ std::string(address) }
    {}

    explicit constexpr ipv4(std::uint32_t address)
        : octets_{ (address >> 24) & 0xff, (address >> 16) & 0xff, (address >> 8) & 0xff, address & 0xff }
    {}

    constexpr ipv4(std::uint8_t o0, std::uint8_t o1, std::uint8_t o2, std::uint8_t o3)
        : octets_{ o0, o1, o2, o3 }
    {}

    [[nodiscard]] std::string to_string() const {
        std::ostringstream oss{};
        oss << *this;
        return oss.str();
    }

    [[nodiscard]] constexpr unsigned long to_ulong() const noexcept {
        return static_cast<unsigned long>((octets_[0] << 24) | (octets_[1] << 16) | (octets_[2] << 8) | octets_[3]);
    }

    ipv4& operator++() {
        *this = ipv4{ this->to_ulong() + 1 };
        return *this;
    }

    ipv4 operator++(int) {
        ipv4 tmp{ *this };
        ++(*this);
        return tmp;
    }

private:
    friend bool operator==(const ipv4& lhs, const ipv4& rhs) {
        return lhs.octets_ == rhs.octets_;
    }

    friend bool operator<(const ipv4& lhs, const ipv4& rhs) {
        return lhs.to_ulong() < rhs.to_ulong();
    }

    friend std::ostream& operator<<(std::ostream& os, const ipv4& address) {
        std::for_each(address.octets_.cbegin(), address.octets_.cend(),
            [&os, first = true](std::uint8_t n) mutable {
               os << (first ? "" : ".") << std::to_string(n);
                first = false;
        });
        return os;
    }

    friend std::istream& operator>>(std::istream& is, ipv4& address) {
        bool error{ false };

        std::string str{};
        is >> str;

        if (not validate_ipv4_address(str, address)) {
            is.setstate(std::ios_base::failbit);
            address.octets_.fill(0);
        }

        return is;
    }

    [[nodiscard]] friend bool validate_ipv4_address(const std::string& str, ipv4& address) {
        bool ret{ true };
        std::regex pattern{ R"(^([[:digit:]]{1,3})\.([[:digit:]]{1,3})\.([[:digit:]]{1,3})\.([[:digit:]]{1,3})$)" };
        std::smatch matches;
        if (std::regex_search(str, matches, pattern)) {
            int i{ 0 };
            for (auto match{ std::next(cbegin(matches)) }; match != cend(matches); ++match) {
                int octet{ std::stoi(*match) };
                if (octet > 255) {
                    ret = false;
                    break;
                }
                address.octets_[i++] = octet;
            }
        }
        else {
            ret = false;
        }
        if (not ret) {
            address.octets_.fill(0);
        }
        return ret;
    }

private:
    friend struct fmt::formatter<ipv4>;

    std::array<std::uint8_t, 4> octets_{};
};


template <>
struct fmt::formatter<ipv4>
{
    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const ipv4& address, FormatContext& ctx) {
        return fmt::format_to(ctx.out(), "{}.{}.{}.{}",
            address.octets_[0], address.octets_[1], address.octets_[2], address.octets_[3]);
    }
};
