#pragma once

#include <algorithm>  // for_each
#include <array>
#include <charconv>  // from_chars
#include <cstdint>  // uint8_t, uint32_t
#include <fmt/format.h>
#include <fmt/ostream.h>
#include <ios>  // ios_base
#include <istream>
#include <numeric>
#include <ostream>
#include <regex>
#include <sstream>  // ostringstream
#include <stdexcept>  // runtime_error
#include <string>


// fmt formatter
namespace tmcppc::network { class ipv4; }
template <>
struct fmt::formatter<tmcppc::network::ipv4> : fmt::ostream_formatter {};


namespace tmcppc::network {
    struct invalid_ipv4_address_error : public std::runtime_error {
        explicit invalid_ipv4_address_error(const std::string& address) : std::runtime_error{ "" } {
            message_ = fmt::format("{}: {}", message_, address);
        }
        [[nodiscard]] const char* what() const noexcept override { return message_.c_str(); }
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
    // Copy construction, copy assignment operator and destructor are also unnecessary
    //
    // operator<< and operator>> implemented as non-member functions and friends
    class ipv4 {
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
            : octets_{
                static_cast<uint8_t>((address >> 24) & 0xff),
                static_cast<uint8_t>((address >> 16) & 0xff),
                static_cast<uint8_t>((address >> 8) & 0xff),
                static_cast<uint8_t>(address & 0xff)
            }
        {}

        constexpr ipv4(std::uint8_t o0, std::uint8_t o1, std::uint8_t o2, std::uint8_t o3)
            : octets_{ o0, o1, o2, o3 }
        {}

        [[nodiscard]] std::string to_string() const {
            return fmt::format("{}", *this);
        }

        [[nodiscard]] constexpr unsigned long to_ulong() const noexcept {
            return static_cast<unsigned long>((octets_[0] << 24) | (octets_[1] << 16) | (octets_[2] << 8) | octets_[3]);
        }

        ipv4& operator++() {
            *this = ipv4{ static_cast<uint32_t>(this->to_ulong() + 1) };
            return *this;
        }

        ipv4 operator++(int) & {
            ipv4 tmp{ *this };
            ++(*this);
            return tmp;
        }

    public:
        friend bool operator==(const ipv4& lhs, const ipv4& rhs) {
            return lhs.octets_ == rhs.octets_;
        }

        friend bool operator<(const ipv4& lhs, const ipv4& rhs) {
            return lhs.to_ulong() < rhs.to_ulong();
        }

        friend std::ostream& operator<<(std::ostream& os, const ipv4& address) {
            std::ranges::for_each(address.octets_, [&os, first = true](std::uint8_t n) mutable {
                fmt::print(os, "{}{}", (first ? "" : "."), n);
                first = false;
            });
            return os;
        }

        friend std::istream& operator>>(std::istream& is, ipv4& address) {
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
                size_t i{ 0 };
                for (auto match{ std::next(cbegin(matches)) }; match != cend(matches); ++match) {
                    uint8_t octet{};
                    const auto& match_str{ match->str() };
                    const auto match_begin{ match_str.data() };
                    const auto match_end{ match_begin + match_str.size() };
                    auto [ptr, ec] = std::from_chars(match_begin, match_end, octet);
                    if (ec != std::errc{} or ptr != match_end) {
                        ret = false;
                        break;
                    }
                    address.octets_[i++] = octet;
                }
            } else {
                ret = false;
            }
            if (not ret) {
                address.octets_.fill(0);
            }
            return ret;
        }

    private:
        std::array<std::uint8_t, 4> octets_{};
    };
}  // namespace tmcppc::network
