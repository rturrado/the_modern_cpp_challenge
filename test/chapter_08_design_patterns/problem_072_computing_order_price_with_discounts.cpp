#include "chapter_08_design_patterns/problem_072_computing_order_price_with_discounts.h"

#include <cmath>  // fabs
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>  // make_shared, make_unique, unique_ptr
#include <sstream>  // ostringstream

using namespace tmcppc::store;


bool simple_compare_floats(float a, float b) {
    return std::fabs(a - b) < 0.001;
}


TEST(article_fixed_discount_percentage, discount_0) {
    std::unique_ptr<discount> d{ std::make_unique<article_fixed_discount>(0.0f) };
    EXPECT_TRUE(simple_compare_floats(d->percentage(1, 10.0f), 0.0f));
}
TEST(article_fixed_discount_percentage, discount_0_5) {
    std::unique_ptr<discount> d{ std::make_unique<article_fixed_discount>(0.5f) };
    EXPECT_TRUE(simple_compare_floats(d->percentage(1, 10.0f), 0.5f));
}


TEST(order_line_volume_discount_percentage, discount_0) {
    std::unique_ptr<discount> d{ std::make_unique<order_line_volume_discount>(0.0f, 0) };
    EXPECT_TRUE(simple_compare_floats(d->percentage(1, 10.0f), 0.0f));
}
TEST(order_line_volume_discount_percentage, discount_0_5_minimum_article_quantity_0) {
    std::unique_ptr<discount> d{ std::make_unique<order_line_volume_discount>(0.5f, 0) };
    EXPECT_TRUE(simple_compare_floats(d->percentage(1, 10.0f), 0.5f));
}
TEST(order_line_volume_discount_percentage, discount_0_5_minimum_article_quantity_5) {
    std::unique_ptr<discount> d{ std::make_unique<order_line_volume_discount>(0.5f, 5) };
    EXPECT_TRUE(simple_compare_floats(d->percentage(1, 10.0f), 0.0f));
}


TEST(order_line_price_discount_percentage, discount_0) {
    std::unique_ptr<discount> d{ std::make_unique<order_line_price_discount>(0.0f, 0.0f) };
    EXPECT_TRUE(simple_compare_floats(d->percentage(1, 10.0f), 0.0f));
}
TEST(order_line_price_discount_percentage, discount_0_5_minimum_total_article_price_0) {
    std::unique_ptr<discount> d{ std::make_unique<order_line_price_discount>(0.5f, 0.0f) };
    EXPECT_TRUE(simple_compare_floats(d->percentage(1, 10.0f), 0.5f));
}
TEST(order_line_price_discount_percentage, discount_0_5_minimum_total_article_price_100) {
    std::unique_ptr<discount> d{ std::make_unique<order_line_price_discount>(0.5f, 100.0f) };
    EXPECT_TRUE(simple_compare_floats(d->percentage(1, 10.0f), 0.0f));
}


TEST(order_price_discount_percentage, discount_0) {
    std::unique_ptr<discount> d{ std::make_unique<order_price_discount>(0.0f, 0.0f) };
    EXPECT_TRUE(simple_compare_floats(d->percentage(1, 10.0f), 0.0f));
}
TEST(order_price_discount_percentage, discount_0_5_minimum_total_order_price_0) {
    std::unique_ptr<discount> d{ std::make_unique<order_price_discount>(0.5f, 0.0f) };
    EXPECT_TRUE(simple_compare_floats(d->percentage(1, 10.0f), 0.5f));
}
TEST(order_price_discount_percentage, discount_0_5_minimum_total_order_price_100) {
    std::unique_ptr<discount> d{ std::make_unique<order_price_discount>(0.5f, 100.0f) };
    EXPECT_TRUE(simple_compare_floats(d->percentage(1, 10.0f), 0.0f));
}


TEST(price_calculator, calculate) {
    auto d1{ std::make_shared<article_fixed_discount>(0.05f) };
    auto d3{ std::make_shared<order_line_price_discount>(0.1f, 20.0f) };
    auto d4{ std::make_shared<order_price_discount>(0.03f, 100.0f) };
    auto a3{ std::make_shared<article_t>(2, 4.0f, std::vector<std::shared_ptr<discount>>{}) };
    auto a4{ std::make_shared<article_t>(3, 8.0f, std::vector<std::shared_ptr<discount>>{}) };
    auto c2{ std::make_shared<customer_t>(1, std::vector<std::shared_ptr<discount>>{ d1 }) };
    order_t o2{
        .id = 1,
        .order_lines = {
            { a3, 10, std::vector<std::shared_ptr<discount>>{ d3 } },
            { a4, 10, std::vector<std::shared_ptr<discount>>{ d3 } }
        },
        .customer = c2,
        .discounts = std::vector<std::shared_ptr<discount>>{ d4 }
    };
    EXPECT_TRUE(simple_compare_floats(cumulative_price_calculator{}.calculate(o2), 99.36f));
    EXPECT_TRUE(simple_compare_floats(non_cumulative_price_calculator{}.calculate(o2), 108.0f));
}


TEST(problem_72_main, output) {
    std::ostringstream oss{};
    problem_72_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "Store:\n"
        "    store[\n"
        "        article(\n"
        "            id : 0,\n"
        "            price : 1,\n"
        "            discounts : []\n"
        "        ),\n"
        "        article(\n"
        "            id : 1,\n"
        "            price : 2,\n"
        "            discounts : [\n"
        "                article_fixed_discount(percentage : 0.05)\n"
        "            ]\n"
        "        ),\n"
        "        article(\n"
        "            id : 2,\n"
        "            price : 4,\n"
        "            discounts : []\n"
        "        ),\n"
        "        article(\n"
        "            id : 3,\n"
        "            price : 8,\n"
        "            discounts : []\n"
        "        ),\n"
        "        article(\n"
        "            id : 5,\n"
        "            price : 16,\n"
        "            discounts : []\n"
        "        )\n"
        "    ]\n"
        "\n"
        "Order 1:\n"
        "    order(\n"
        "        id : 0,\n"
        "        order_lines : [\n"
        "            order_line(\n"
        "                article(\n"
        "                    id : 0,\n"
        "                    price : 1,\n"
        "                    discounts : []\n"
        "                ),\n"
        "                quantity : 6,\n"
        "                discounts : [\n"
        "                    order_line_volume_discount(percentage : 0.2, minimum_article_quantity : 3)\n"
        "                ]\n"
        "            ),\n"
        "            order_line(\n"
        "                article(\n"
        "                    id : 1,\n"
        "                    price : 2,\n"
        "                    discounts : [\n"
        "                        article_fixed_discount(percentage : 0.05)\n"
        "                    ]\n"
        "                ),\n"
        "                quantity : 2,\n"
        "                discounts : []\n"
        "            ),\n"
        "            order_line(\n"
        "                article(\n"
        "                    id : 5,\n"
        "                    price : 16,\n"
        "                    discounts : []\n"
        "                ),\n"
        "                quantity : 2,\n"
        "                discounts : [\n"
        "                    order_line_price_discount(percentage : 0.1, minimum_total_article_price : 20)\n"
        "                ]\n"
        "            )\n"
        "        ],\n"
        "        customer(\n"
        "            id : 0,\n"
        "            discounts : []\n"
        "        ),\n"
        "        discounts : []\n"
        "    )\n"
        "\n"
        "Order 2:\n"
        "    order(\n"
        "        id : 1,\n"
        "        order_lines : [\n"
        "            order_line(\n"
        "                article(\n"
        "                    id : 2,\n"
        "                    price : 4,\n"
        "                    discounts : []\n"
        "                ),\n"
        "                quantity : 10,\n"
        "                discounts : [\n"
        "                    order_line_price_discount(percentage : 0.1, minimum_total_article_price : 20)\n"
        "                ]\n"
        "            ),\n"
        "            order_line(\n"
        "                article(\n"
        "                    id : 3,\n"
        "                    price : 8,\n"
        "                    discounts : []\n"
        "                ),\n"
        "                quantity : 10,\n"
        "                discounts : [\n"
        "                    order_line_price_discount(percentage : 0.1, minimum_total_article_price : 20)\n"
        "                ]\n"
        "            )\n"
        "        ],\n"
        "        customer(\n"
        "            id : 1,\n"
        "            discounts : [\n"
        "                article_fixed_discount(percentage : 0.05)\n"
        "            ]\n"
        "        ),\n"
        "        discounts : [\n"
        "            order_price_discount(percentage : 0.03, minimum_total_order_price : 100)\n"
        "        ]\n"
        "    )\n"
        "\n"
        "Cumulative price for order 1: 37.4\n"
        "Cumulative price for order 2: 99.36\n"
        "Non cumulative price for order 1: 37.4\n"
        "Non cumulative price for order 2: 108\n\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::Not(::testing::EndsWith("\n\n\n")));
}
