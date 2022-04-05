#pragma once

#include <iomanip>  // setprecision
#include <ios>  // fixed
#include <iostream>  // ostream
#include <stdexcept>  // runtime_error
#include <type_traits>  // common_type_t


// V1: my initial solution.
//     temperature class is only templated on the representation type
namespace my_temperature_v1
{
    enum class Scale { Invalid = -1, Celsius, Fahrenheit, Kelvin };


    struct InvalidTemperature : public std::runtime_error
    {
        explicit InvalidTemperature()
            : std::runtime_error("invalid temperature")
        {
            // Do nothing
        }
    };


    template <typename Rep_ = float>
    class temperature
    {
    public:
        temperature() = delete;

        constexpr temperature(const Rep_& value, const Scale& scale) noexcept
            : value_{ value }
            , scale_{ scale }
        {
            // Do nothing
        }

        template <typename Rep2_>
        temperature(const temperature<Rep2_>& other) noexcept
            : value_{ static_cast<Rep_>(other.value_) }
            , scale_{ other.scale_ }
        {
            // Do nothing
        }

        template <typename Rep2_>
        temperature& operator=(const temperature<Rep2_>& other) noexcept
            : value_{ static_cast<Rep_>(other.value_) }
            , scale_{ other.scale_ }
        {
            return *this;
        }

        template <typename Rep2_>
        temperature(temperature<Rep2_>&& other) noexcept
            : value_{ static_cast<Rep_>(other.value_) }
            , scale_{ other.scale_ }
        {
            other.value_ = 0.f;
            other.scale_ = Scale::Invalid;
        }

        template <typename Rep2_>
        temperature& operator=(temperature<Rep2_>&& other) noexcept
            : value_{ static_cast<Rep_>(other.value_) }
            , scale_{ other.scale_ }
        {
            other.value_ = 0.f;
            other.scale_ = Scale::Invalid;
            return *this;
        }

        [[nodiscard]] Rep_ value() const noexcept { return value_; }
        [[nodiscard]] Scale scale() const noexcept { return scale_; }

    private:
        Rep_ value_{ 0.f };
        Scale scale_{ Scale::Invalid };
    };


    // Operator extraction
    //
    template <typename Rep_>
    std::ostream& operator<<(std::ostream& os, const temperature<Rep_>& t)
    {
        if (t.scale() == Scale::Invalid)
        {
            os << "<invalid temperature>";
        }
        else
        {
            os << std::fixed << std::setprecision(2) << t.value() << " ";

            switch (t.scale())
            {
            case Scale::Celsius: os << "Celsius"; break;
            case Scale::Fahrenheit: os << "Fahrenheit"; break;
            case Scale::Kelvin: os << "Kelvin"; break;
            default: break;
            }
        }

        return os;
    }


    // Conversions
    //
    // C to F: (C * 9/5) + 32
    template <typename Rep_>
    Rep_ celsius_to_fahrenheit(Rep_ c) { return (c * 9.0 / 5.0) + 32.0; }

    // F to C: (F - 32) * 5/9
    template <typename Rep_>
    Rep_ fahrenheit_to_celsius(Rep_ f) { return (f - 32.0) * 9.0 / 5.0; }

    // C to K: C - 273.15
    template <typename Rep_>
    Rep_ celsius_to_kelvin(Rep_ c) { return c + 273.15; }

    // K to C: K + 273.15
    template <typename Rep_>
    Rep_ kelvin_to_celsius(Rep_ k) { return k - 273.15; }

    // F to K: (F - 32) * 5/9 + 273.15
    template <typename Rep_>
    Rep_ fahrenheit_to_kelvin(Rep_ f) { return (f - 32.0) * 5.0 / 9.0 + 273.15; }

    // K to F: (K - 273.15) * 9/5 + 32
    template <typename Rep_>
    Rep_ kelvin_to_fahrenheit(Rep_ k) { return (k - 273.15) * 9.0 / 5.0 + 32.0; }

    template <typename Rep_>
    [[nodiscard]] constexpr Rep_ to_celsius(const temperature<Rep_>& t)
    {
        Rep_ ret{};

        switch (t.scale())
        {
        case Scale::Invalid: throw InvalidTemperature{};
        case Scale::Celsius: ret = ret = t.value(); break;
        case Scale::Fahrenheit: ret = fahrenheit_to_celsius<Rep_>(t.value()); break;
        case Scale::Kelvin: ret = kelvin_to_celsius<Rep_>(t.value()); break;
        default: break;
        }

        return ret;
    }

    template <typename Rep_>
    [[nodiscard]] constexpr Rep_ to_fahrenheit(const temperature<Rep_>& t)
    {
        Rep_ ret{};

        switch (t.scale())
        {
        case Scale::Invalid: throw InvalidTemperature{};
        case Scale::Celsius: ret = celsius_to_fahrenheit<Rep_>(t.value()); break;
        case Scale::Fahrenheit: ret = t.value(); break;
        case Scale::Kelvin: ret = kelvin_to_fahrenheit<Rep_>(t.value()); break;
        default: break;
        }

        return ret;
    }

    template <typename Rep_>
    [[nodiscard]] constexpr Rep_ to_kelvin(const temperature<Rep_>& t)
    {
        Rep_ ret{};

        switch (t.scale())
        {
        case Scale::Invalid: throw InvalidTemperature{};
        case Scale::Celsius: ret = celsius_to_kelvin<Rep_>(t.value()); break;
        case Scale::Fahrenheit: ret = fahrenheit_to_kelvin<Rep_>(t.value()); break;
        case Scale::Kelvin: ret = t.value(); break;
        default: break;
        }

        return ret;
    }


    // Comparisons
    //
    bool simple_compare_long_doubles(long double lhs, long double rhs)
    {
        return std::fabs(lhs - rhs) <= std::numeric_limits<long double>::epsilon();
    }

    template <typename Rep_, typename Rep2_>
    bool operator==(const temperature<Rep_>& lhs, const temperature<Rep2_>& rhs)
    {
        return simple_compare_long_doubles(
            static_cast<long double>(to_celsius(lhs)),
            static_cast<long double>(to_celsius(rhs)));
    }

    template <typename Rep_, typename Rep2_>
    bool operator!=(const temperature<Rep_>& lhs, const temperature<Rep2_>& rhs)
    {
        return not (lhs == rhs);
    }

    template <typename Rep_, typename Rep2_>
    constexpr bool operator<(const temperature<Rep_>& lhs, const temperature<Rep2_>& rhs)
    {
        return static_cast<long double>(to_celsius(lhs)) < static_cast<long double>(to_celsius(rhs));
    }

    template <typename Rep_, typename Rep2_>
    constexpr bool operator>(const temperature<Rep_>& lhs, const temperature<Rep2_>& rhs)
    {
        return rhs < lhs;
    }

    template <typename Rep_, typename Rep2_>
    constexpr bool operator<=(const temperature<Rep_>& lhs, const temperature<Rep2_>& rhs)
    {
        return not (lhs > rhs);
    }

    template <typename Rep_, typename Rep2_>
    constexpr bool operator>=(const temperature<Rep_>& lhs, const temperature<Rep2_>& rhs)
    {
        return not (lhs < rhs);
    }


    // Arithmetic
    //
    template <typename Rep_, typename Rep2_>
    constexpr auto operator+(const temperature<Rep_>& lhs, const temperature<Rep2_>& rhs)
    {
        using CT_ = std::common_type_t<Rep_, Rep2_>;
        return temperature<CT_>(
            static_cast<long double>(to_celsius(lhs)) + static_cast<long double>(to_celsius(rhs)), Scale::Celsius);
    }

    template <typename Rep_, typename Rep2_>
    constexpr auto operator-(const temperature<Rep_>& lhs, const temperature<Rep2_>& rhs)
    {
        using CT_ = std::common_type_t<Rep_, Rep2_>;
        return temperature<CT_>(
            static_cast<long double>(to_celsius(lhs)) - static_cast<long double>(to_celsius(rhs)), Scale::Celsius);
    }


    // User defined literals
    //
    namespace literals
    {
        constexpr auto operator"" _deg(long double value) { return temperature<long double>(value, Scale::Celsius); }
        constexpr auto operator"" _f(long double value) { return temperature<long double>(value, Scale::Fahrenheit); }
        constexpr auto operator"" _K(long double value) { return temperature<long double>(value, Scale::Kelvin); }
    }
    // namespace my_temperature_literals
}
// namespace my_temperature_v1
