#pragma once

#include <algorithm>  // all_of, transform
#include <array>
#include <bitset>
#include <cctype>  // isdigit
#include <cstdint>  // uint8_t
#include <map>
#include <stdexcept>  // runtime_error
#include <string>


namespace tmcppc::ean_13 {
    auto to_uint8_t(const unsigned char c) {
        return static_cast<uint8_t>(c - '0');
    };

    constinit const size_t code_size{ 13 };
    constinit const size_t group_size{ 6 };
    constinit const size_t bits_per_digit{ 7 };

    using digit_bs = std::bitset<bits_per_digit>;
    using digit_group_bs = std::array<digit_bs, group_size>;

    enum class digit_type { none, l, g, r };

    class digit {
    private:
        static inline auto l_encoding = std::map<std::uint8_t, digit_bs>{
            { 0, digit_bs{"0001101"} },
            { 1, digit_bs{"0011001"} },
            { 2, digit_bs{"0010011"} },
            { 3, digit_bs{"0111101"} },
            { 4, digit_bs{"0100011"} },
            { 5, digit_bs{"0110001"} },
            { 6, digit_bs{"0101111"} },
            { 7, digit_bs{"0111011"} },
            { 8, digit_bs{"0110111"} },
            { 9, digit_bs{"0001011"} }
        };
        static inline auto g_encoding = std::map<std::uint8_t, digit_bs>{
            { 0, digit_bs{"0100111"} },
            { 1, digit_bs{"0110011"} },
            { 2, digit_bs{"0011011"} },
            { 3, digit_bs{"0100001"} },
            { 4, digit_bs{"0011101"} },
            { 5, digit_bs{"0111001"} },
            { 6, digit_bs{"0000101"} },
            { 7, digit_bs{"0010001"} },
            { 8, digit_bs{"0001001"} },
            { 9, digit_bs{"0010111"} }
        };
        static inline auto r_encoding = std::map<std::uint8_t, digit_bs>{
            { 0, digit_bs{"1110010"} },
            { 1, digit_bs{"1100110"} },
            { 2, digit_bs{"1101100"} },
            { 3, digit_bs{"1000010"} },
            { 4, digit_bs{"1011100"} },
            { 5, digit_bs{"1001110"} },
            { 6, digit_bs{"1010000"} },
            { 7, digit_bs{"1000100"} },
            { 8, digit_bs{"1001000"} },
            { 9, digit_bs{"1110100"} }
        };

    public:
        digit() : type_{ digit_type::none } {}
        explicit digit(std::uint8_t value) : value_{ value } {}
        explicit digit(digit_type type) : type_{ type } {}

        [[nodiscard]] inline auto get_type() const { return type_; }
        [[nodiscard]] inline auto get_value() const { return value_; }

        [[nodiscard]] inline auto encode(uint8_t value) const -> digit_bs {
            switch (type_) {
                case digit_type::l: return l_encoding[value];
                case digit_type::g: return g_encoding[value];
                case digit_type::r: return r_encoding[value];
                default: return {};
            }
        }

    private:
        digit_type type_{};
        std::uint8_t value_{};
    };

    struct digit_group {
        [[nodiscard]] inline auto encode(const std::string& digits_str) const {
            digit_group_bs ret{};

            std::transform(digits_str.cbegin(), digits_str.cend(), data_.cbegin(), ret.begin(),
                [](const unsigned char c, const digit& d) { return d.encode(to_uint8_t(c));  });

            return ret;
        }

        std::array<digit, group_size> data_{};
    };

    struct invalid_code_size_exception : public std::runtime_error {
        invalid_code_size_exception(const std::string& code_str)
            : std::runtime_error{ message_ + code_str }
        {}
    private:
        static inline std::string message_{ "invalid code size exception: " };
    };

    struct invalid_code_exception : public std::runtime_error {
        invalid_code_exception(const std::string& code_str)
            : std::runtime_error{ message_ + code_str }
        {}
    private:
        static inline std::string message_{ "invalid code exception: " };
    };

    class barcode {
    private:
        static inline auto l = digit{ digit_type::l };
        static inline auto g = digit{ digit_type::g };
        static inline auto r = digit{ digit_type::r };

        static inline auto first_group_structure_map = std::map<std::uint8_t, digit_group>{
            { 0, { l, l, l, l, l, l } },
            { 1, { l, l, g, l, l, g } },
            { 2, { l, l, g, g, l, g } },
            { 3, { l, l, g, g, g, l } },
            { 4, { l, g, l, l, g, g } },
            { 5, { l, g, g, l, l, g } },
            { 6, { l, g, g, g, l, l } },
            { 7, { l, g, l, g, l, g } },
            { 8, { l, g, l, g, g, l } },
            { 9, { l, g, g, l, g, l } }
        };

    public:
        explicit barcode(const std::string& code_str) : code_str_{ code_str } { encode(); }

        [[nodiscard]] auto get_first_digit_group_bs() const { return first_digit_group_bs_; }
        [[nodiscard]] auto get_second_digit_group_bs() const { return second_digit_group_bs_; }

        [[nodiscard]] auto get_first_digit_char() const { return code_str_[0]; }
        [[nodiscard]] auto get_first_digit_str() const { return std::string{ code_str_[0] }; }
        [[nodiscard]] auto get_first_digit_group_str() const { return code_str_.substr(1, group_size); }
        [[nodiscard]] auto get_second_digit_group_str() const { return code_str_.substr(1 + group_size); }

    public:
        static inline const auto start_marker{ std::bitset<3>{"101"} };
        static inline const auto center_marker{ std::bitset<5>{"01010"} };
        static inline const auto end_marker{ std::bitset<3>{"101"} };

    private:
        void encode() {
            if (code_str_.size() != code_size) {
                throw invalid_code_size_exception{ code_str_ };
            }
            if (not std::ranges::all_of(code_str_, [](unsigned char c) { return std::isdigit(c); })) {
                throw invalid_code_exception{ code_str_ };
            }

            auto first_digit = digit{ to_uint8_t(get_first_digit_char()) };
            auto& first_group_digits = first_group_structure_map[first_digit.get_value()];
            auto second_group_digits = digit_group{ r, r, r, r, r, r };

            first_digit_group_bs_ = first_group_digits.encode(get_first_digit_group_str());
            second_digit_group_bs_ = second_group_digits.encode(get_second_digit_group_str());
        }

    private:
        std::string code_str_{};

        digit_group_bs first_digit_group_bs_{};
        digit_group_bs second_digit_group_bs_{};
    };
}  // namespace tmcppc::ean_13
