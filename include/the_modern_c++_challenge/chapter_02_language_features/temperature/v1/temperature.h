#pragma once

#include <fmt/ostream.h>
#include <iostream>  // ostream
#include <stdexcept>  // runtime_error
#include <type_traits>  // common_type_t


// v1: my initial solution
//
// temperature class is only templated on the representation type
namespace tmcppc::temperature::v1 {
    enum class scale_t { invalid = -1, celsius, fahrenheit, kelvin };

    [[nodiscard]] inline std::string to_string(const scale_t& s) {
        switch (s) {
            case scale_t::celsius: return "Celsius";
            case scale_t::fahrenheit: return "Fahrenheit";
            case scale_t::kelvin: return "Kelvin";
        }
        return "<invalid temperature>";
    }

    struct invalid_temperature_error : public std::runtime_error {
        explicit invalid_temperature_error() : std::runtime_error{ "invalid temperature" } {}
    };

    template <typename Rep_ = float>
    class temperature {
    public:
        temperature() = delete;

        constexpr temperature(const Rep_& v, const scale_t& s) noexcept
            : value_{ v }
            , scale_{ s }
        {}

        template <typename Rep2_>
        explicit temperature(const temperature<Rep2_>& other) noexcept
            : value_{ static_cast<Rep_>(other.value_) }
            , scale_{ other.scale_ }
        {}

        template <typename Rep2_>
        temperature& operator=(const temperature<Rep2_>& other) noexcept {
            value_ = static_cast<Rep_>(other.value_);
            scale_ = other.scale_;
            return *this;
        }

        template <typename Rep2_>
        explicit temperature(temperature<Rep2_>&& other) noexcept
            : value_{ static_cast<Rep_>(other.value_) }
            , scale_{ other.scale_ } {
            other.value_ = 0;
            other.scale_ = scale_t::invalid;
        }

        template <typename Rep2_>
        temperature& operator=(temperature<Rep2_>&& other) noexcept {
            value_ = static_cast<Rep_>(other.value_);
            scale_ = other.scale_;
            other.value_ = 0;
            other.scale_ = scale_t::invalid;
            return *this;
        }

        [[nodiscard]] Rep_ value() const noexcept { return value_; }
        [[nodiscard]] scale_t scale() const noexcept { return scale_; }

    private:
        friend struct fmt::formatter<temperature>;

        Rep_ value_{ 0 };
        enum scale_t scale_{ scale_t::invalid };
    };

    // Operator insertion
    //
    template <typename Rep_>
    std::ostream& operator<<(std::ostream& os, const temperature<Rep_>& t) {
        fmt::print(os, "{}", t);
        return os;
    }

    // Conversions
    //
    // C to F: (C * 9/5) + 32
    template <typename Rep_>
    constexpr Rep_ celsius_to_fahrenheit(Rep_ c) { return static_cast<Rep_>((c * 9.0 / 5.0) + 32.0); }

    // F to C: (F - 32) * 5/9
    template <typename Rep_>
    constexpr Rep_ fahrenheit_to_celsius(Rep_ f) { return static_cast<Rep_>((f - 32.0) * 5.0 / 9.0); }

    // C to K: C + 273.15
    template <typename Rep_>
    constexpr Rep_ celsius_to_kelvin(Rep_ c) { return static_cast<Rep_>(c + 273.15); }

    // K to C: K - 273.15
    template <typename Rep_>
    constexpr Rep_ kelvin_to_celsius(Rep_ k) { return static_cast<Rep_>(k - 273.15); }

    // F to K: (F - 32) * 5/9 + 273.15
    template <typename Rep_>
    constexpr Rep_ fahrenheit_to_kelvin(Rep_ f) { return static_cast<Rep_>((f - 32.0) * 5.0 / 9.0 + 273.15); }

    // K to F: (K - 273.15) * 9/5 + 32
    template <typename Rep_>
    constexpr Rep_ kelvin_to_fahrenheit(Rep_ k) { return static_cast<Rep_>((k - 273.15) * 9.0 / 5.0 + 32.0); }

    template <typename Rep_>
    [[nodiscard]] constexpr Rep_ to_celsius(const temperature<Rep_>& t) {
        Rep_ ret{};
        switch (t.scale()) {
            case scale_t::invalid: throw invalid_temperature_error{};
            case scale_t::celsius: ret = t.value(); break;
            case scale_t::fahrenheit: ret = fahrenheit_to_celsius<Rep_>(t.value()); break;
            case scale_t::kelvin: ret = kelvin_to_celsius<Rep_>(t.value()); break;
            default: break;
        }
        return ret;
    }

    template <typename Rep_>
    [[nodiscard]] constexpr Rep_ to_fahrenheit(const temperature<Rep_>& t) {
        Rep_ ret{};
        switch (t.scale()) {
            case scale_t::invalid: throw invalid_temperature_error{};
            case scale_t::celsius: ret = celsius_to_fahrenheit<Rep_>(t.value()); break;
            case scale_t::fahrenheit: ret = t.value(); break;
            case scale_t::kelvin: ret = kelvin_to_fahrenheit<Rep_>(t.value()); break;
            default: break;
        }
        return ret;
    }

    template <typename Rep_>
    [[nodiscard]] constexpr Rep_ to_kelvin(const temperature<Rep_>& t) {
        Rep_ ret{};
        switch (t.scale()) {
            case scale_t::invalid: throw invalid_temperature_error{};
            case scale_t::celsius: ret = celsius_to_kelvin<Rep_>(t.value()); break;
            case scale_t::fahrenheit: ret = fahrenheit_to_kelvin<Rep_>(t.value()); break;
            case scale_t::kelvin: ret = t.value(); break;
            default: break;
        }
        return ret;
    }

    // Comparisons
    //
    inline bool simple_compare_long_doubles(long double a, long double b) {
        return std::fabs(a - b) < 0.001;
    }

    template <typename Rep_, typename Rep2_>
    bool operator==(const temperature<Rep_>& lhs, const temperature<Rep2_>& rhs) {
        auto a{ static_cast<long double>(to_celsius(lhs)) };
        auto b{ static_cast<long double>(to_celsius(rhs)) };
        return simple_compare_long_doubles(a, b);
    }

    template <typename Rep_, typename Rep2_>
    bool operator!=(const temperature<Rep_>& lhs, const temperature<Rep2_>& rhs) {
        return not (lhs == rhs);
    }

    template <typename Rep_, typename Rep2_>
    constexpr bool operator<(const temperature<Rep_>& lhs, const temperature<Rep2_>& rhs) {
        auto a{ static_cast<long double>(to_celsius(lhs)) };
        auto b{ static_cast<long double>(to_celsius(rhs)) };
        return (a < b) and not simple_compare_long_doubles(a, b);
    }

    template <typename Rep_, typename Rep2_>
    constexpr bool operator>(const temperature<Rep_>& lhs, const temperature<Rep2_>& rhs) {
        auto a{ static_cast<long double>(to_celsius(lhs)) };
        auto b{ static_cast<long double>(to_celsius(rhs)) };
        return (a > b) and not simple_compare_long_doubles(a, b);
    }

    template <typename Rep_, typename Rep2_>
    constexpr bool operator<=(const temperature<Rep_>& lhs, const temperature<Rep2_>& rhs) {
        return not (lhs > rhs);
    }

    template <typename Rep_, typename Rep2_>
    constexpr bool operator>=(const temperature<Rep_>& lhs, const temperature<Rep2_>& rhs) {
        return not (lhs < rhs);
    }

    // Arithmetic
    //
    template <typename Rep_, typename Rep2_>
    constexpr auto operator+(const temperature<Rep_>& lhs, const temperature<Rep2_>& rhs) {
        using CT_ = std::common_type_t<Rep_, Rep2_>;
        return temperature<CT_>(static_cast<CT_>(
            static_cast<long double>(to_celsius(lhs)) + static_cast<long double>(to_celsius(rhs))), scale_t::celsius);
    }

    template <typename Rep_, typename Rep2_>
    constexpr auto operator-(const temperature<Rep_>& lhs, const temperature<Rep2_>& rhs) {
        using CT_ = std::common_type_t<Rep_, Rep2_>;
        return temperature<CT_>(static_cast<CT_>(
            static_cast<long double>(to_celsius(lhs)) - static_cast<long double>(to_celsius(rhs))), scale_t::celsius);
    }

    // User defined literals
    //
    namespace literals {
        constexpr auto operator"" _deg(long double value) { return temperature<long double>(value, scale_t::celsius); }
        constexpr auto operator"" _f(long double value) { return temperature<long double>(value, scale_t::fahrenheit); }
        constexpr auto operator"" _K(long double value) { return temperature<long double>(value, scale_t::kelvin); }
    }  // namespace my_temperature_literals
}  // namespace tmcppc::temperature::v1


template <typename Rep_>
struct fmt::formatter<tmcppc::temperature::v1::temperature<Rep_>> {
    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const tmcppc::temperature::v1::temperature<Rep_>& t, FormatContext& ctx) const -> decltype(ctx.out()) {
        const auto& s{ t.scale() };
        if (s == tmcppc::temperature::v1::scale_t::invalid) {
            return fmt::format_to(ctx.out(), "{}", to_string(s));
        }
        return fmt::format_to(ctx.out(), "{:.2f} {}", t.value(), to_string(s));
    }
};
