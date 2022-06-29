#include "chapter_08_design_patterns/problem_072_computing_order_price_with_discounts.h"

#include <cassert>  // assert
#include <cmath>  // abs
#include <iostream>  // cout
#include <limits>  // epsilon, numeric_limits
#include <memory>  // make_shared
#include <ostream>


void problem_72_main(std::ostream& os) {
    using namespace tmcppc::store;

    const size_t store_articles_size{ 15 };

    // Discounts
    auto d1{ std::make_shared<article_fixed_discount>(0.05f) };
    auto d2{ std::make_shared<order_line_volume_discount>(0.2f, 3) };
    auto d3{ std::make_shared<order_line_price_discount>(0.1f, 20.0f) };
    auto d4{ std::make_shared<order_price_discount>(0.03f, 100.0f) };

    // Articles
    auto a1{ std::make_shared<article>(0, 1.0f, std::vector<std::shared_ptr<discount>>{}) };
    auto a2{ std::make_shared<article>(1, 2.0f, std::vector<std::shared_ptr<discount>>{ d1 }) };
    auto a3{ std::make_shared<article>(2, 4.0f, std::vector<std::shared_ptr<discount>>{}) };
    auto a4{ std::make_shared<article>(3, 8.0f, std::vector<std::shared_ptr<discount>>{}) };
    auto a5{ std::make_shared<article>(5, 16.0f, std::vector<std::shared_ptr<discount>>{}) };

    // Store
    store store{};
    store.articles.push_back(a1);
    store.articles.push_back(a2);
    store.articles.push_back(a3);
    store.articles.push_back(a4);
    store.articles.push_back(a5);

    fmt::print(os, "Store:\n");
    store.print(os, indentation{ 1 });
    fmt::print(os, "\n\n");

    // Customers
    auto c1{ std::make_shared<customer>(0, std::vector<std::shared_ptr<discount>>{}) };
    auto c2{ std::make_shared<customer>(1, std::vector<std::shared_ptr<discount>>{ d1 }) };

    // Orders
    order o1{
        .id = 0,
        .order_lines = {
            { a1, 6, std::vector<std::shared_ptr<discount>>{ d2 } },
            { a2, 2, std::vector<std::shared_ptr<discount>>{} },
            { a5, 2, std::vector<std::shared_ptr<discount>>{ d3 } }
        },
        .customer = c1,
        .discounts = std::vector<std::shared_ptr<discount>>{}
    };
    order o2{
        .id = 1,
        .order_lines = {
            { a3, 10, std::vector<std::shared_ptr<discount>>{ d3 } },
            { a4, 10, std::vector<std::shared_ptr<discount>>{ d3 } }
        },
        .customer = c2,
        .discounts = std::vector<std::shared_ptr<discount>>{ d4 }
    };

    fmt::print(os, "Order 1:\n");
    o1.print(os, indentation{ 1 });
    fmt::print(os, "\n\n");
    fmt::print(os, "Order 2:\n");
    o2.print(os, indentation{ 1 });
    fmt::print(os, "\n\n");

    auto equal = [](float a, float b) {
        return (std::abs(a - b) < std::numeric_limits<float>::epsilon());
    };

    // Price calculations
    cumulative_price_calculator cpc{};
    non_cumulative_price_calculator ncpc{};

    auto cp1{ cpc.calculate(o1) };
    auto cp2{ cpc.calculate(o2) };
    auto ncp1{ ncpc.calculate(o1) };
    auto ncp2{ ncpc.calculate(o2) };

    assert(equal(cp1, 37.4f) and "Error: calculating cumulative price for order 1");
    assert(equal(cp2, 99.36f) and "Error: calculating cumulative price for order 2");
    assert(equal(ncp1, 37.4f) and "Error: calculating non cumulative price for order 1");
    assert(equal(ncp2, 108.0f) and "Error: calculating non cumulative price for order 2");

    fmt::print(os, "Cumulative price for order 1: {}\n", cp1);
    fmt::print(os, "Cumulative price for order 2: {}\n", cp2);
    fmt::print(os, "Non cumulative price for order 1: {}\n", ncp1);
    fmt::print(os, "Non cumulative price for order 2: {}\n\n", ncp2);
}


// Computing order price with discounts
//
// A retail store sells a variety of goods and can offer various types of discount, for selected customers, articles, or per order.
// The following types of discount could be available:
//
//   - A fixed discount, such as 5%, regardless of the article or the quantity that is purchased.
//   - A volume discount, such as 10%, for each article when buying more than a particular quantity of that article.
//   - A price discount per total order of an article, that is, a discount for an article when a customer buys a quantity of that article
//     so that the total cost exceeds a particular amount.
//     For instance, a 15% discount for an article when the total cost of that article exceeds $100.
//     If the article costs $5, and the customer buys 30 units, the total cost is $150;
//     therefore, a 15% discount applies to the order of that article.
//   - A price discount per entire order (regardless what articles and in which quantity they were ordered).
//
// Write a program that can calculate the final price of a particular order.
// It is possible to compute the final price in different ways; for instance, all discounts could be cumulative,
// or on the other hand, if an article has a discount, a customer or total order discount might not be considered.
void problem_72_main() {
    problem_72_main(std::cout);
}
