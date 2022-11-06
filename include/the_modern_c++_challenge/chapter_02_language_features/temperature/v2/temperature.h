#pragma once

#include <fmt/ostream.h>
#include <iostream>  // ostream
#include <type_traits>  // common_type_t


// v2: based on the book's answer; also similar to Boost.Unit's implementation
//
// temperature class is templated on a Scale parameter as well
namespace tmcppc::temperature::v2 {
    enum class scale_t { celsius, fahrenheit, kelvin };

    template <typename Rep_ = float, scale_t scale_ = scale_t::celsius>
    class temperature {
    public:
        temperature() = delete;

        constexpr explicit temperature(const Rep_& value) noexcept
            : value_{ value }
        {}

        template <typename Rep2_>
        explicit temperature(const temperature<Rep2_>& other) noexcept
            : value_{ static_cast<Rep_>(other.value_) }
        {}

        template <typename Rep2_>
        temperature& operator=(const temperature<Rep2_>& other) noexcept {
            value_ = static_cast<Rep_>(other.value_);
            return *this;
        }

        template <typename Rep2_>
        explicit temperature(temperature<Rep2_>&& other) noexcept
            : value_{ static_cast<Rep_>(other.value_) } {
            other.value_ = 0.f;
        }

        template <typename Rep2_>
        temperature& operator=(temperature<Rep2_>&& other) noexcept {
            value_ = static_cast<Rep_>(other.value_);
            other.value_ = 0.f;
            return *this;
        }

        [[nodiscard]] Rep_ value() const noexcept { return value_; }
        [[nodiscard]] scale_t scale() const noexcept { return scale_; }

    private:
        Rep_ value_{ 0.f };
    };

    // Operator insertion
    //
    template <typename Rep_>
    std::ostream& operator<<(std::ostream& os, const temperature<Rep_, scale_t::celsius>& t) {
        return os << fmt::format("{:.2f} Celsius", t.value());
    }
    template <typename Rep_>
    std::ostream& operator<<(std::ostream& os, const temperature<Rep_, scale_t::fahrenheit>& t) {
        return os << fmt::format("{:.2f} Fahrenheit", t.value());
    }
    template <typename Rep_>
    std::ostream& operator<<(std::ostream& os, const temperature<Rep_, scale_t::kelvin>& t) {
        return os << fmt::format("{:.2f} Kelvin", t.value());
    }

    // Conversions
    //
    template <typename Rep_, scale_t S, typename Rep2_, scale_t S2>
    struct conversion_helper {
        static auto convert(const Rep_ v) = delete;
    };

    // C to F: (C * 9/5) + 32
    template <typename Rep_, typename Rep2_>
    struct conversion_helper<Rep_, scale_t::celsius, Rep2_, scale_t::fahrenheit> {
        using CT_ = std::common_type_t<Rep_, Rep2_>;
        static auto convert(const Rep_ c) noexcept { return static_cast<CT_>((c * 9.0 / 5.0) + 32.0); }
    };

    // F to C: (F - 32) * 5/9
    template <typename Rep_, typename Rep2_>
    struct conversion_helper<Rep_, scale_t::fahrenheit, Rep2_, scale_t::celsius> {
        using CT_ = std::common_type_t<Rep_, Rep2_>;
        static auto convert(const Rep_ f) noexcept { return static_cast<CT_>((f - 32.0) * 5.0 / 9.0); }
    };

    // C to K: C + 273.15
    template <typename Rep_, typename Rep2_>
    struct conversion_helper<Rep_, scale_t::celsius, Rep2_, scale_t::kelvin> {
        using CT_ = std::common_type_t<Rep_, Rep2_>;
        static auto convert(const Rep_ c) noexcept { return static_cast<CT_>(c + 273.15); }
    };

    // K to C: K - 273.15
    template <typename Rep_, typename Rep2_>
    struct conversion_helper<Rep_, scale_t::kelvin, Rep2_, scale_t::celsius> {
        using CT_ = std::common_type_t<Rep_, Rep2_>;
        static auto convert(const Rep_ k) noexcept { return static_cast<CT_>(k - 273.15); }
    };

    // F to K: (F - 32) * 5/9 + 273.15
    template <typename Rep_, typename Rep2_>
    struct conversion_helper<Rep_, scale_t::fahrenheit, Rep2_, scale_t::kelvin> {
        using CT_ = std::common_type_t<Rep_, Rep2_>;
        static auto convert(const Rep_ f) noexcept { return static_cast<CT_>((f - 32.0) * 5.0 / 9.0 + 273.15); }
    };

    // K to F: (K - 273.15) * 9/5 + 32
    template <typename Rep_, typename Rep2_>
    struct conversion_helper<Rep_, scale_t::kelvin, Rep2_, scale_t::fahrenheit> {
        using CT_ = std::common_type_t<Rep_, Rep2_>;
        static auto convert(const Rep_ k) noexcept { return static_cast<CT_>((k - 273.15) * 9.0 / 5.0 + 32.0); }
    };

    template <typename Rep2_, scale_t S2, typename Rep_, scale_t S>
    [[nodiscard]] constexpr auto temperature_cast(const temperature<Rep_, S>& t) noexcept {
        using CT_ = std::common_type_t<Rep_, Rep2_>;
        return temperature<CT_, S2>(conversion_helper<Rep_, S, Rep2_, S2>::convert(t.value()));
    }

    // Comparisons
    //
    inline bool simple_compare_long_doubles(long double a, long double b) {
        return std::fabs(a - b) < 0.001;
    }

    template <typename Rep_, scale_t S, typename Rep2_>
    bool operator==(const temperature<Rep_, S>& lhs, const temperature<Rep2_, S>& rhs) {
        auto a{ static_cast<long double>(lhs.value()) };
        auto b{ static_cast<long double>(rhs.value()) };
        return simple_compare_long_doubles(a, b);
    }

    template <typename Rep_, scale_t S, typename Rep2_>
    bool operator!=(const temperature<Rep_, S>& lhs, const temperature<Rep2_, S>& rhs) {
        return not (lhs == rhs);
    }

    template <typename Rep_, scale_t S, typename Rep2_>
    constexpr bool operator<(const temperature<Rep_, S>& lhs, const temperature<Rep2_, S>& rhs) {
        auto a{ static_cast<long double>(lhs.value()) };
        auto b{ static_cast<long double>(rhs.value()) };
        return (a < b) and not simple_compare_long_doubles(a, b);
    }

    template <typename Rep_, scale_t S, typename Rep2_>
    constexpr bool operator>(const temperature<Rep_, S>& lhs, const temperature<Rep2_, S>& rhs) {
        auto a{ static_cast<long double>(lhs.value()) };
        auto b{ static_cast<long double>(rhs.value()) };
        return (a > b) and not simple_compare_long_doubles(a, b);
    }

    template <typename Rep_, scale_t S, typename Rep2_>
    constexpr bool operator<=(const temperature<Rep_, S>& lhs, const temperature<Rep2_, S>& rhs) {
        return not (lhs > rhs);
    }

    template <typename Rep_, scale_t S, typename Rep2_>
    constexpr bool operator>=(const temperature<Rep_, S>& lhs, const temperature<Rep2_, S>& rhs) {
        return not (lhs < rhs);
    }

    // Arithmetic
    //
    template <typename Rep_, scale_t S, typename Rep2_>
    constexpr auto operator+(const temperature<Rep_, S>& lhs, const temperature<Rep2_, S>& rhs) {
        using CT_ = std::common_type_t<Rep_, Rep2_>;
        return temperature<CT_, S>(
            static_cast<CT_>(lhs.value()) + static_cast<CT_>(rhs.value()));
    }

    template <typename Rep_, scale_t S, typename Rep2_>
    constexpr auto operator-(const temperature<Rep_, S>& lhs, const temperature<Rep2_, S>& rhs) {
        using CT_ = std::common_type_t<Rep_, Rep2_>;
        return temperature<CT_, S>(
            static_cast<CT_>(lhs.value()) - static_cast<CT_>(rhs.value()));
    }

    // User defined literals
    //
    namespace literals {
        constexpr auto operator"" _deg(long double value) { return temperature<long double, scale_t::celsius>(value); }
        constexpr auto operator"" _f(long double value) { return temperature<long double, scale_t::fahrenheit>(value); }
        constexpr auto operator"" _K(long double value) { return temperature<long double, scale_t::kelvin>(value); }
    }  // namespace literals
}  // namespace tmcppc::temperature::v2


// fmt formatters
template <typename Rep_>
struct fmt::formatter<tmcppc::temperature::v2::temperature<Rep_, tmcppc::temperature::v2::scale_t::celsius>> : fmt::ostream_formatter {};
template <typename Rep_>
struct fmt::formatter<tmcppc::temperature::v2::temperature<Rep_, tmcppc::temperature::v2::scale_t::fahrenheit>> : fmt::ostream_formatter {};
template <typename Rep_>
struct fmt::formatter<tmcppc::temperature::v2::temperature<Rep_, tmcppc::temperature::v2::scale_t::kelvin>> : fmt::ostream_formatter {};
