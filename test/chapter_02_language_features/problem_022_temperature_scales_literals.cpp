#include "chapter_02_language_features/problem_022_temperature_scales_literals.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <sstream>  // ostringstream


TEST(problem_22_main, output) {
    std::ostringstream oss{};
    problem_22_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "Using temperature::v1:\n"
        "\t35.50 Celsius in Fahrenheit: 95.90 Fahrenheit\n"
        "\t35.50 Celsius in Kelvin: 308.65 Kelvin\n"
        "\n"
        "\t12.30 Celsius == 12.30 Fahrenheit? false. 12.30 Fahrenheit == -10.94 Celsius\n"
        "\t12.30 Celsius < 12.30 Fahrenheit? false. 12.30 Fahrenheit == -10.94 Celsius\n"
        "\t12.30 Celsius > 12.30 Kelvin? true. 12.30 Kelvin == -260.85 Celsius\n"
        "\n"
        "\t12.30 Celsius + 12.30 Fahrenheit = 1.36 Celsius. 12.30 Fahrenheit == -10.94 Celsius\n"
        "\t12.30 Celsius - 12.30 Kelvin = 273.15 Celsius. 12.30 Kelvin == -260.85 Celsius\n"
        "\n"
        "Using temperature::v2:\n"
        "\t35.50 Celsius in Fahrenheit: 95.90 Fahrenheit\n"
        "\t35.50 Celsius in Kelvin: 308.65 Kelvin\n"
        "\n"
        "\t12.30 Celsius == 12.30 Fahrenheit? false. 12.30 Fahrenheit == -10.94 Celsius\n"
        "\t12.30 Celsius < 12.30 Fahrenheit? false. 12.30 Fahrenheit == -10.94 Celsius\n"
        "\t12.30 Celsius > 12.30 Kelvin? true. 12.30 Kelvin == -260.85 Celsius\n"
        "\n"
        "\t12.30 Celsius + 12.30 Fahrenheit = 1.36 Celsius. 12.30 Fahrenheit == -10.94 Celsius\n"
        "\t12.30 Celsius - 12.30 Kelvin = 273.15 Celsius. 12.30 Kelvin == -260.85 Celsius\n\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::Not(::testing::EndsWith("\n\n\n")));
}
