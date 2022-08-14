#pragma once

#include <algorithm>  // all_of, transform
#include <array>
#include <bitset>
#include <cassert>  // assert
#include <cctype>  // isdigit
#include <cstdint>  // uint8_t
#include <map>
#include <stdexcept>  // runtime_error
#include <string>
#include <string_view>


namespace tmcppc::ean_13 {
    inline auto to_uint8_t(const unsigned char c) {
        return static_cast<uint8_t>(c - '0');
    };

    struct invalid_code_size_exception : public std::runtime_error {
        invalid_code_size_exception(std::string_view code_sv) : std::runtime_error{ "" } { message_ += code_sv; }
        virtual const char* what() const noexcept override { return message_.c_str(); }
    private:
        static inline std::string message_{ "invalid code size exception: " };
    };

    struct invalid_code_exception : public std::runtime_error {
        invalid_code_exception(std::string_view code_sv) : std::runtime_error{ "" } { message_ += code_sv; }
        virtual const char* what() const noexcept override { return message_.c_str(); }
    private:
        static inline std::string message_{ "invalid code exception: " };
    };

    constinit const size_t code_size{ 13 };
    constinit const size_t group_size{ 6 };
    constinit const size_t bits_per_digit{ 7 };

    using digit_bs = std::bitset<bits_per_digit>;
    using digit_group_bs = std::array<digit_bs, group_size>;

    enum class digit_type { l, g, r };

    class digit {
    private:
        static inline const auto l_encoding = std::map<std::uint8_t, digit_bs>{
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
        static inline const auto g_encoding = std::map<std::uint8_t, digit_bs>{
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
        static inline const auto r_encoding = std::map<std::uint8_t, digit_bs>{
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
        explicit digit(digit_type type)
            : type_{ type }
            , value_{ static_cast<std::uint8_t>(0) }
        {}

        [[nodiscard]] auto get_type() const { return type_; }
        [[nodiscard]] auto get_value() const { return value_; }

        [[nodiscard]] auto encode(uint8_t value) const -> digit_bs {
            switch (type_) {
                case digit_type::l: return l_encoding.at(value);
                case digit_type::g: return g_encoding.at(value);
                case digit_type::r: return r_encoding.at(value);
            }
            assert("Eror: trying to encode a digit of type other than l, g, or r, " and false);
            return {};
        }

    private:
        digit_type type_{};
        std::uint8_t value_{};
    };

    struct digit_group {
        [[nodiscard]] auto encode(std::string_view digits) const -> digit_group_bs {
            digit_group_bs ret{};

            std::ranges::transform(digits, data_, ret.begin(),
                [](const unsigned char c, const digit& d) { return d.encode(to_uint8_t(c));  });

            return ret;
        }

        std::array<digit, group_size> data_;
    };

    class barcode {
    private:
        static inline const auto l = digit{ digit_type::l };
        static inline const auto g = digit{ digit_type::g };
        static inline const auto r = digit{ digit_type::r };

        static inline const auto first_group_structure = std::map<std::uint8_t, digit_group>{
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
        static inline const auto second_group_structure = digit_group{ r, r, r, r, r, r };

    public:
        explicit barcode(std::string_view code) : code_{ code } { encode(); }

        [[nodiscard]] auto get_first_digit_group_bs() const { return first_digit_group_bs_; }
        [[nodiscard]] auto get_second_digit_group_bs() const { return second_digit_group_bs_; }

        [[nodiscard]] auto get_first_digit_char() const { return code_[0]; }
        [[nodiscard]] auto get_first_digit_string() const { return code_.substr(0, 1); }
        [[nodiscard]] auto get_first_digit_group_string() const { return code_.substr(1, group_size); }
        [[nodiscard]] auto get_second_digit_group_string() const { return code_.substr(1 + group_size); }

    public:
        static inline const auto start_marker{ std::bitset<3>{"101"} };
        static inline const auto center_marker{ std::bitset<5>{"01010"} };
        static inline const auto end_marker{ std::bitset<3>{"101"} };

    private:
        void encode() {
            if (code_.size() != code_size) {
                throw invalid_code_size_exception{ code_ };
            }
            if (not std::ranges::all_of(code_, [](unsigned char c) { return std::isdigit(c); })) {
                throw invalid_code_exception{ code_ };
            }

            auto& first_group_digits = first_group_structure.at(to_uint8_t(get_first_digit_char()));
            auto& second_group_digits = second_group_structure;

            first_digit_group_bs_ = first_group_digits.encode(get_first_digit_group_string());
            second_digit_group_bs_ = second_group_digits.encode(get_second_digit_group_string());
        }

    private:
        std::string_view code_{};

        digit_group_bs first_digit_group_bs_{};
        digit_group_bs second_digit_group_bs_{};
    };
}  // namespace tmcppc::ean_13
