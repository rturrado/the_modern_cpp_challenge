#include "chapter_02_language_features/temperature/v2/temperature.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <fmt/format.h>
#include <sstream>  // ostringstream

using namespace tmcppc::temperature::v2;


TEST(temperature_v2, DISABLED_operator_insertion_celsius) {
    std::ostringstream oss{};
    temperature<float, scale::celsius> t{ 25.0f };
    oss << t;
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("25.00 Celsius"));
}
TEST(temperature_v2, DISABLED_operator_insertion_fahrenheit) {
    std::ostringstream oss{};
    temperature<float, scale::fahrenheit> t{ 25.0f };
    oss << t;
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("25.00 Fahrenheit"));
}
TEST(temperature_v2, DISABLED_operator_insertion_kelvin) {
    std::ostringstream oss{};
    temperature<float, scale::kelvin> t{ 25.0f };
    oss << t;
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("25.00 Kelvin"));
}

TEST(temperature_v2, DISABLED_fmt_format_celsius) {
    temperature<float, scale::celsius> t{ 25.0f };
    EXPECT_THAT(fmt::format("{}", t), "25.00 Celsius");
}
TEST(temperature_v2, DISABLED_fmt_format_fahrenheit) {
    temperature<float, scale::fahrenheit> t{ 25.0f };
    EXPECT_EQ(fmt::format("{}", t), "25.00 Fahrenheit");
}
TEST(temperature_v2, DISABLED_fmt_format_kelvin) {
    temperature<float, scale::kelvin> t{ 25.0f };
    EXPECT_EQ(fmt::format("{}", t), "25.00 Kelvin");
}

TEST(temperature_v2, DISABLED_conversion_helper) {
    double fahrenheit_d{ 77.0 };
    double kelvin_d{ 298.15 };
    float fahrenheit_f{ 77.0f };
    temperature<double, scale::celsius> t1d{ 25.0 };
    temperature<float, scale::celsius> t1f{ 25.0f };
    EXPECT_TRUE(simple_compare_long_doubles(
        fahrenheit_d,
        conversion_helper<double, scale::celsius, double, scale::fahrenheit>::convert(t1d.value())
    ));
    EXPECT_TRUE(simple_compare_long_doubles(
        fahrenheit_d,
        conversion_helper<double, scale::celsius, float, scale::fahrenheit>::convert(t1d.value())
    ));
    EXPECT_TRUE(simple_compare_long_doubles(
        kelvin_d,
        conversion_helper<double, scale::celsius, float, scale::kelvin>::convert(t1d.value())
    ));
    EXPECT_TRUE(simple_compare_long_doubles(
        fahrenheit_f,
        conversion_helper<float, scale::celsius, float, scale::fahrenheit>::convert(t1f.value())
    ));
    EXPECT_TRUE(simple_compare_long_doubles(
        fahrenheit_d,
        conversion_helper<float, scale::celsius, double, scale::fahrenheit>::convert(t1f.value())
    ));
    EXPECT_TRUE(simple_compare_long_doubles(
        kelvin_d,
        conversion_helper<float, scale::celsius, double, scale::kelvin>::convert(t1f.value())
    ));
}
TEST(temperature_v2, DISABLED_temperature_cast) {
    temperature<double, scale::celsius> t1d{ 25.0 };
    temperature<double, scale::fahrenheit> t2d{ 77.0 };
    temperature<double, scale::kelvin> t3d{ 298.15 };
    temperature<float, scale::celsius> t1f{ 25.0f };
    temperature<float, scale::fahrenheit> t2f{ 77.0f };
    temperature<float, scale::kelvin> t3f{ 298.15f };
    EXPECT_TRUE(t2d == (temperature_cast<double, scale::fahrenheit>(t1d)));
    EXPECT_TRUE(t2d == (temperature_cast<float, scale::fahrenheit>(t1d)));
    EXPECT_TRUE(t3d == (temperature_cast<float, scale::kelvin>(t1d)));
    EXPECT_TRUE(t2f == (temperature_cast<float, scale::fahrenheit>(t1f)));
    EXPECT_TRUE(t2d == (temperature_cast<double, scale::fahrenheit>(t1f)));
    EXPECT_TRUE(t3d == (temperature_cast<double, scale::kelvin>(t1f)));
}

TEST(temperature_v2, DISABLED_comparisons) {
    temperature<float, scale::celsius> t1{ 20.0f };
    temperature<float, scale::celsius> t2{ 25.0f };
    temperature<float, scale::fahrenheit> t3{ 77.0f };
    temperature<float, scale::kelvin> t4{ 298.15f };
    EXPECT_TRUE(t1 == t1);
    EXPECT_TRUE(t2 == (temperature_cast<float, scale::celsius>(t3)));
    EXPECT_TRUE(t2 == (temperature_cast<float, scale::celsius>(t4)));
    EXPECT_TRUE(t1 < t2);
    EXPECT_TRUE(t2 > t1);
    EXPECT_TRUE(t1 <= t2);
    EXPECT_TRUE(t2 >= t1);
    EXPECT_TRUE(t2 <= (temperature_cast<float, scale::celsius>(t3)));
    EXPECT_TRUE(t3 >= (temperature_cast<float, scale::fahrenheit>(t2)));
    EXPECT_TRUE(t2 <= (temperature_cast<float, scale::celsius>(t4)));
    EXPECT_TRUE(t4 >= (temperature_cast<float, scale::kelvin>(t2)));
}
TEST(temperature_v2, DISABLED_equality_precision) {
    temperature<float, scale::celsius> t1{ 25.0f };
    temperature<float, scale::celsius> slightly_above_t1{ 25.01f };
    temperature<float, scale::fahrenheit> t2{ 77.0f };
    temperature<float, scale::fahrenheit> slightly_above_t2{ 77.018f };
    temperature<float, scale::kelvin> t3{ 298.15f };
    temperature<float, scale::kelvin> slightly_above_t3{ 298.16f };
    EXPECT_FALSE(t1 == slightly_above_t1);
    EXPECT_FALSE(t2 == slightly_above_t2);
    EXPECT_FALSE(t3 == slightly_above_t3);
    EXPECT_FALSE(t1 == (temperature_cast<float, scale::celsius>(slightly_above_t2)));
    EXPECT_FALSE(t1 == (temperature_cast<float, scale::celsius>(slightly_above_t3)));
    EXPECT_FALSE(t2 == (temperature_cast<double, scale::fahrenheit>(slightly_above_t1)));
    EXPECT_FALSE(t2 == (temperature_cast<double, scale::fahrenheit>(slightly_above_t3)));
    EXPECT_FALSE(t3 == (temperature_cast<double, scale::kelvin>(slightly_above_t1)));
    EXPECT_FALSE(t3 == (temperature_cast<double, scale::kelvin>(slightly_above_t2)));
}

TEST(temperature_v2, DISABLED_arithmetic) {
    temperature<double, scale::celsius> t1d{ 25.0 };
    temperature<double, scale::fahrenheit> t2d{ 77.0 };
    temperature<double, scale::kelvin> t3d{ 298.15 };
    temperature<float, scale::celsius> t1f{ 25.0f };
    temperature<float, scale::fahrenheit> t2f{ 77.0f };
    temperature<float, scale::kelvin> t3f{ 298.15f };
    temperature<double, scale::celsius> sum_c{ 50.0 };
    temperature<double, scale::fahrenheit> sum_f{ 154.0 };
    temperature<double, scale::kelvin> sum_k{ 596.30 };
    temperature<double, scale::celsius> difference_c{ 0.0 };
    temperature<double, scale::fahrenheit> difference_f{ 0.0 };
    temperature<double, scale::kelvin> difference_k{ 0.0 };
    EXPECT_TRUE(t1d + t1d == sum_c);
    EXPECT_TRUE(t1f + t1f == sum_c);
    EXPECT_TRUE(t2d + t2d == sum_f);
    EXPECT_TRUE(t2f + t2f == sum_f);
    EXPECT_TRUE(t3d + t3d == sum_k);
    EXPECT_TRUE(t3f + t3f == sum_k);
    EXPECT_TRUE(t1d - t1d == difference_c);
    EXPECT_TRUE(t1f - t1f == difference_c);
    EXPECT_TRUE(t2d - t2d == difference_f);
    EXPECT_TRUE(t2f - t2f == difference_f);
    EXPECT_TRUE(t3d - t3d == difference_k);
    EXPECT_TRUE(t3f - t3f == difference_k);
}

TEST(temperature_v2, DISABLED_user_defined_literals) {
    using namespace literals;
    temperature<double, scale::celsius> t1{ 25.0 };
    temperature<double, scale::fahrenheit> t2{ 77.0 };
    temperature<double, scale::kelvin> t3{ 298.15 };
    EXPECT_TRUE(25.0_deg == t1);
    EXPECT_TRUE(77.0_f == t2);
    EXPECT_TRUE(298.15_K == t3);
}
