#pragma once

#include <iomanip>  // setprecision
#include <ios>  // fixed
#include <iostream>  // ostream
#include <type_traits>  // common_type_t


// v2: based on the book's answer; also similar to Boost.Unit's implementation
// 
// temperature class is templated on a Scale parameter as well
namespace tmcppc::temperature::v2 {
    enum class scale { celsius, fahrenheit, kelvin };

    template <typename Rep_ = float, scale = scale::celsius>
    class temperature {
    public:
        using scale_ = scale;

        temperature() = delete;

        constexpr temperature(const Rep_& value) noexcept
            : value_{ value }
        {}

        template <typename Rep2_>
        temperature(const temperature<Rep2_>& other) noexcept
            : value_{ static_cast<Rep_>(other.value_) }
        {}

        template <typename Rep2_>
        temperature& operator=(const temperature<Rep2_>& other) noexcept {
            value_ = static_cast<Rep_>(other.value_);
            return *this;
        }

        template <typename Rep2_>
        temperature(temperature<Rep2_>&& other) noexcept
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
        [[nodiscard]] scale scale() const noexcept { return scale_; }

    private:
        Rep_ value_{ 0.f };
    };

    // Operator extraction
    //
    template <typename Rep_>
    std::ostream& operator<<(std::ostream& os, const temperature<Rep_, scale::celsius>& t) {
        return os << std::fixed << std::setprecision(2) << t.value() << " Celsius";
    }
    template <typename Rep_>
    std::ostream& operator<<(std::ostream& os, const temperature<Rep_, scale::fahrenheit>& t) {
        return os << std::fixed << std::setprecision(2) << t.value() << " Fahrenheit";
    }
    template <typename Rep_>
    std::ostream& operator<<(std::ostream& os, const temperature<Rep_, scale::kelvin>& t) {
        return os << std::fixed << std::setprecision(2) << t.value() << " Kelvin";
    }

    // Conversions
    //
    template <typename Rep_, scale S, typename Rep2_, scale S2>
    struct conversion_helper {
        static auto convert(const Rep_ v) = delete;
    };

    // C to F: (C * 9/5) + 32
    template <typename Rep_, typename Rep2_>
    struct conversion_helper<Rep_, scale::celsius, Rep2_, scale::fahrenheit> {
        using CT_ = std::common_type_t<Rep_, Rep2_>;
        static auto convert(const Rep_ c) noexcept { return static_cast<CT_>((c * 9.0 / 5.0) + 32.0); }
    };

    // F to C: (F - 32) * 5/9
    template <typename Rep_, typename Rep2_>
    struct conversion_helper<Rep_, scale::fahrenheit, Rep2_, scale::celsius> {
        using CT_ = std::common_type_t<Rep_, Rep2_>;
        static auto convert(const Rep_ f) noexcept { return static_cast<CT_>((f - 32.0) * 5.0 / 9.0); }
    };

    // C to K: C + 273.15
    template <typename Rep_, typename Rep2_>
    struct conversion_helper<Rep_, scale::celsius, Rep2_, scale::kelvin> {
        using CT_ = std::common_type_t<Rep_, Rep2_>;
        static auto convert(const Rep_ c) noexcept { return static_cast<CT_>(c + 273.15); }
    };

    // K to C: K - 273.15
    template <typename Rep_, typename Rep2_>
    struct conversion_helper<Rep_, scale::kelvin, Rep2_, scale::celsius> {
        using CT_ = std::common_type_t<Rep_, Rep2_>;
        static auto convert(const Rep_ k) noexcept { return static_cast<CT_>(k - 273.15); }
    };

    // F to K: (F - 32) * 5/9 + 273.15
    template <typename Rep_, typename Rep2_>
    struct conversion_helper<Rep_, scale::fahrenheit, Rep2_, scale::kelvin> {
        using CT_ = std::common_type_t<Rep_, Rep2_>;
        static auto convert(const Rep_ f) noexcept { return static_cast<CT_>((f - 32.0) * 5.0 / 9.0 + 273.15); }
    };

    // K to F: (K - 273.15) * 9/5 + 32
    template <typename Rep_, typename Rep2_>
    struct conversion_helper<Rep_, scale::kelvin, Rep2_, scale::fahrenheit> {
        using CT_ = std::common_type_t<Rep_, Rep2_>;
        static auto convert(const Rep_ k) noexcept { return static_cast<CT_>((k - 273.15) * 9.0 / 5.0 + 32.0); }
    };

    template <typename Rep2_, scale S2, typename Rep_, scale S>
    [[nodiscard]] constexpr auto temperature_cast(const temperature<Rep_, S>& t) noexcept {
        using CT_ = std::common_type_t<Rep_, Rep2_>;
        return temperature<CT_, S2>(conversion_helper<Rep_, S, Rep2_, S2>::convert(t.value()));
    }

    // Comparisons
    //
    bool simple_compare_long_doubles(long double lhs, long double rhs) {
        return std::fabs(lhs - rhs) <= std::numeric_limits<long double>::epsilon();
    }

    template <typename Rep_, scale S, typename Rep2_>
    bool operator==(const temperature<Rep_, S>& lhs, const temperature<Rep2_, S>& rhs) {
        return simple_compare_long_doubles(
            static_cast<long double>(lhs.value()),
            static_cast<long double>(rhs.value()));
    }

    template <typename Rep_, scale S, typename Rep2_>
    bool operator!=(const temperature<Rep_, S>& lhs, const temperature<Rep2_, S>& rhs) {
        return not (lhs == rhs);
    }

    template <typename Rep_, scale S, typename Rep2_>
    constexpr bool operator<(const temperature<Rep_, S>& lhs, const temperature<Rep2_, S>& rhs) {
        return static_cast<long double>(lhs.value()) < static_cast<long double>(rhs.value());
    }

    template <typename Rep_, scale S, typename Rep2_>
    constexpr bool operator>(const temperature<Rep_, S>& lhs, const temperature<Rep2_, S>& rhs) {
        return rhs < lhs;
    }

    template <typename Rep_, scale S, typename Rep2_>
    constexpr bool operator<=(const temperature<Rep_, S>& lhs, const temperature<Rep2_, S>& rhs) {
        return not (lhs > rhs);
    }

    template <typename Rep_, scale S, typename Rep2_>
    constexpr bool operator>=(const temperature<Rep_, S>& lhs, const temperature<Rep2_, S>& rhs) {
        return not (lhs < rhs);
    }

    // Arithmetic
    //
    template <typename Rep_, scale S, typename Rep2_>
    constexpr auto operator+(const temperature<Rep_, S>& lhs, const temperature<Rep2_, S>& rhs) {
        using CT_ = std::common_type_t<Rep_, Rep2_>;
        return temperature<CT_, S>(
            static_cast<CT_>(lhs.value()) + static_cast<CT_>(rhs.value()));
    }

    template <typename Rep_, scale S, typename Rep2_>
    constexpr auto operator-(const temperature<Rep_, S>& lhs, const temperature<Rep2_, S>& rhs) {
        using CT_ = std::common_type_t<Rep_, Rep2_>;
        return temperature<CT_, S>(
            static_cast<CT_>(lhs.value()) - static_cast<CT_>(rhs.value()));
    }

    // User defined literals
    //
    namespace literals {
        constexpr auto operator"" _deg(long double value) { return temperature<long double, scale::celsius>(value); }
        constexpr auto operator"" _f(long double value) { return temperature<long double, scale::fahrenheit>(value); }
        constexpr auto operator"" _K(long double value) { return temperature<long double, scale::kelvin>(value); }
    }  // namespace literals
}  // namespace tmcppc::temperature::v2
