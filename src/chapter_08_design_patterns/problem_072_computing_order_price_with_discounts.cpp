#include "chapter_08_design_patterns/problem_072_computing_order_price_with_discounts.h"
#include "rtc/pretty_print.h"
#include "rtc/print.h"

#include <cassert>  // assert
#include <cmath>  // fabs
#include <iostream>  // cout
#include <limits>  // epsilon, numeric_limits
#include <memory>  // make_shared, shared_ptr
#include <ostream>
#include <vector>


struct Discount
{
    virtual ~Discount() = default;

    [[nodiscard]] virtual float percentage(size_t, float) const noexcept = 0;

    [[nodiscard]] virtual void print(std::ostream& os, const FillLineStart& fill_line_start = {}) const noexcept = 0;
};

std::ostream& operator<<(std::ostream& os, const Discount& d) { d.print(os); return os; }


struct ArticleFixedDiscount : public Discount
{
    explicit ArticleFixedDiscount(float p) : percentage_{ p } {}

    [[nodiscard]] virtual void print(std::ostream& os, const FillLineStart& fill_line_start = {}) const noexcept override
    {
        os << fill_line_start << "ArticleFixedDiscount(percentage : " << percentage_ << ")";
    }

protected:
    [[nodiscard]] virtual float percentage(size_t, float) const noexcept override
    {
        return percentage_;
    }

private:
    ArticleFixedDiscount() = default;

    float percentage_{};
};


class OrderLineVolumeDiscount : public Discount
{
public:
    OrderLineVolumeDiscount(float p, size_t q) : percentage_{ p }, minimum_article_quantity_{ q } {}

    [[nodiscard]] virtual void print(std::ostream& os, const FillLineStart& fill_line_start = {}) const noexcept override
    {
        os << fill_line_start << "ArticleVolumeDiscount(percentage : " << percentage_ << ", minimum_article_quantity : " << minimum_article_quantity_ << ")";
    }

protected:
    [[nodiscard]] virtual float percentage(size_t article_quantity, float) const noexcept override
    {
        return (article_quantity >= minimum_article_quantity_) ? percentage_ : 0;
    }

private:
    OrderLineVolumeDiscount() = default;

    float percentage_{};
    size_t minimum_article_quantity_{};
};


struct OrderLinePriceDiscount : public Discount
{
public:
    OrderLinePriceDiscount(float p, float mtap) : percentage_{ p }, minimum_total_article_price_{ mtap } {}

    [[nodiscard]] virtual void print(std::ostream& os, const FillLineStart& fill_line_start = {}) const noexcept override
    {
        os << fill_line_start << "OrderLinePriceDiscount(percentage : " << percentage_ << ", minimum_total_article_price : " << minimum_total_article_price_ << ")";
    }

protected:
    [[nodiscard]] virtual float percentage(size_t article_quantity, float article_price) const noexcept override
    {
        return (article_quantity * article_price > minimum_total_article_price_) ? percentage_ : 0;
    }

private:
    OrderLinePriceDiscount() = default;

    float percentage_{};
    float minimum_total_article_price_{};
};


struct OrderPriceDiscount : public Discount
{
public:
    OrderPriceDiscount(float p, float mtop) : percentage_{ p }, minimum_total_order_price_{ mtop } {}

    [[nodiscard]] virtual void print(std::ostream& os, const FillLineStart& fill_line_start = {}) const noexcept override
    {
        os << fill_line_start << "OrderPriceDiscount(percentage : " << percentage_ << ", minimum_total_order_price : " << minimum_total_order_price_ << ")";
    }

protected:
    [[nodiscard]] virtual float percentage(size_t, float order_price) const noexcept override
    {
        return (order_price > minimum_total_order_price_) ? percentage_ : 0;
    }

private:
    OrderPriceDiscount() = default;

    float percentage_{};
    float minimum_total_order_price_{};
};


struct Article
{
    size_t id{};
    float price{};
    std::vector<std::shared_ptr<Discount>> discounts{};

    void print(std::ostream& os, const FillLineStart& fill_line_start = {}) const noexcept
    {
        os << fill_line_start << "Article(\n";
        os << (fill_line_start + 1) << "id : " << id << ",\n";
        os << (fill_line_start + 1) << "price : " << price << ",\n";
        os << (fill_line_start + 1) << "discounts : [\n";
        for (auto&& discount : discounts) { discount->print(os, fill_line_start + 2); os << "\n"; }
        os << (fill_line_start + 1) << "]\n";
        os << fill_line_start << ")";
    }
};

std::ostream& operator<<(std::ostream& os, const Article& a) { a.print(os); return os; }


struct Store
{
    std::vector<std::shared_ptr<Article>> articles{};

    void print(std::ostream& os, const FillLineStart& fill_line_start = {}) const noexcept
    {
        os << fill_line_start << "Store[\n";
        for (auto&& article : articles) { article->print(os, fill_line_start + 1); os << "\n"; }
        os << fill_line_start << "]";
    }
};

std::ostream& operator<<(std::ostream& os, const Store& s) { s.print(os); return os; }


struct Customer
{
    size_t id{};
    std::vector<std::shared_ptr<Discount>> discounts{};

    void print(std::ostream& os, const FillLineStart& fill_line_start = {}) const noexcept
    {
        os << fill_line_start << "Customer(\n";
        os << (fill_line_start + 1) << "id : " << id << ",\n";
        os << (fill_line_start + 1) << "discounts : [\n";
        for (auto&& discount : discounts) { discount->print(os, fill_line_start + 2); os << "\n"; }
        os << (fill_line_start + 1) << "],\n";
        os << fill_line_start << ")";
    }
};

std::ostream& operator<<(std::ostream& os, const Customer& c) { c.print(os); return os; }


struct OrderLine
{
    std::shared_ptr<Article> article{};
    size_t quantity{};
    std::vector<std::shared_ptr<Discount>> discounts{};

    void print(std::ostream& os, const FillLineStart& fill_line_start = {}) const noexcept
    {
        os << fill_line_start << "OrderLine(\n";
        os << (fill_line_start + 1) << "article :\n"; article->print(os, fill_line_start + 2); os << ",\n";
        os << (fill_line_start + 1) << "quantity : " << quantity << ",\n";
        os << (fill_line_start + 1) << "discounts : [\n";
        for (auto&& discount : discounts) { discount->print(os, fill_line_start + 2); os << "\n"; }
        os << (fill_line_start + 1) << "]\n";
        os << fill_line_start << ")";
    }
};

std::ostream& operator<<(std::ostream& os, const OrderLine& ol) { ol.print(os); return os; }


struct Order
{
    size_t id{};
    std::vector<OrderLine> order_lines{};
    std::shared_ptr<Customer> customer{};
    std::vector<std::shared_ptr<Discount>> discounts{};

    void print(std::ostream& os, const FillLineStart& fill_line_start = {}) const noexcept
    {
        os << fill_line_start << "Order(\n";
        os << (fill_line_start + 1) << "id : " << id << ",\n";
        os << (fill_line_start + 1) << "order_lines : [\n";
        for (auto&& order_line : order_lines) { order_line.print(os, fill_line_start + 2); os << "\n"; }
        os << (fill_line_start + 1) << "],\n";
        os << (fill_line_start + 1) << "customer :\n"; customer->print(os, fill_line_start + 2); os << ",\n";
        os << (fill_line_start + 1) << "discounts : [\n";
        for (auto&& discount : discounts) { discount->print(os, fill_line_start + 2); os << "\n"; }
        os << (fill_line_start + 1) << "]\n";
        os << fill_line_start << ")";
    }
};

std::ostream& operator<<(std::ostream& os, const Order& o) { o.print(os); return os; }


struct PriceCalculator
{
    virtual ~PriceCalculator() = default;

    [[nodiscard]] virtual float calculate(const Order& order) const noexcept = 0;
};


struct CumulativePriceCalculator : public PriceCalculator
{
    [[nodiscard]] virtual float calculate(const Order& order) const noexcept override
    {
        float ret{};

        for (auto&& order_line : order.order_lines)
        {
            auto article{ order_line.article };
            auto price{ article->price };
            auto quantity{ order_line.quantity };
            auto order_line_price{ price * quantity };

            float discount_percentages{};
            for (auto&& article_discount : article->discounts) { discount_percentages += article_discount->percentage(quantity, price); }
            for (auto&& order_line_discount : order_line.discounts) { discount_percentages += order_line_discount->percentage(quantity, price); }
            order_line_price *= (1.0f - discount_percentages);

            ret += order_line_price;
        }

        float discount_percentages{};
        for (auto&& customer_discount : order.customer->discounts) { discount_percentages += customer_discount->percentage(0, ret); }
        for (auto&& order_discount : order.discounts) { discount_percentages += order_discount->percentage(0, ret); }
        ret *= (1.0f - discount_percentages);

        return ret;
    }
};


struct NonCumulativePriceCalculator : public PriceCalculator
{
    [[nodiscard]] virtual float calculate(const Order& order) const noexcept override
    {
        float ret{};
        float discountable_order_price{};

        for (auto&& order_line : order.order_lines)
        {
            auto article{ order_line.article };
            auto price{ article->price };
            auto quantity{ order_line.quantity };
            auto order_line_price{ price * quantity };

            float discount_percentages{};
            for (auto&& article_discount : article->discounts) { discount_percentages += article_discount->percentage(quantity, price); }
            for (auto&& order_line_discount : order_line.discounts) { discount_percentages += order_line_discount->percentage(quantity, price); }
            order_line_price *= (1.0f - discount_percentages);

            ret += order_line_price;
            
            if (article->discounts.empty() and order_line.discounts.empty()) { discountable_order_price += order_line_price; }
        }

        if (discountable_order_price != 0)
        {
            float discount_percentages{};
            for (auto&& customer_discount : order.customer->discounts) { discount_percentages += customer_discount->percentage(0, discountable_order_price); }
            for (auto&& order_discount : order.discounts) { discount_percentages += order_discount->percentage(0, discountable_order_price); }
            ret *= (1.0f - discount_percentages);
        }

        return ret;
    }
};


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
void problem_72_main()
{
    const size_t store_articles_size{ 15 };

    // Discounts
    auto d1{ std::make_shared<ArticleFixedDiscount>(0.05f) };
    auto d2{ std::make_shared<OrderLineVolumeDiscount>(0.2f, 3) };
    auto d3{ std::make_shared<OrderLinePriceDiscount>(0.1f, 20.0f) };
    auto d4{ std::make_shared<OrderPriceDiscount>(0.03f, 100.0f) };

    // Articles
    auto a1{ std::make_shared<Article>(0, 1.0f, std::vector<std::shared_ptr<Discount>>{}) };
    auto a2{ std::make_shared<Article>(1, 2.0f, std::vector<std::shared_ptr<Discount>>{ d1 }) };
    auto a3{ std::make_shared<Article>(2, 4.0f, std::vector<std::shared_ptr<Discount>>{}) };
    auto a4{ std::make_shared<Article>(3, 8.0f, std::vector<std::shared_ptr<Discount>>{}) };
    auto a5{ std::make_shared<Article>(5, 16.0f, std::vector<std::shared_ptr<Discount>>{}) };

    // Store
    Store store{};
    store.articles.push_back(a1);
    store.articles.push_back(a2);
    store.articles.push_back(a3);
    store.articles.push_back(a4);
    store.articles.push_back(a5);

    std::cout << store << "\n\n";

    // Customers
    auto c1{ std::make_shared<Customer>(0, std::vector<std::shared_ptr<Discount>>{}) };
    auto c2{ std::make_shared<Customer>(1, std::vector<std::shared_ptr<Discount>>{ d1 }) };

    // Orders
    Order o1{
        0,
        {
            { a1, 6, std::vector<std::shared_ptr<Discount>>{ d2 } },
            { a2, 2, std::vector<std::shared_ptr<Discount>>{} },
            { a5, 2, std::vector<std::shared_ptr<Discount>>{ d3 } }
        },
        c1,
        std::vector<std::shared_ptr<Discount>>{}
    };
    Order o2{
        1,
        {
            { a3, 10, std::vector<std::shared_ptr<Discount>>{ d3 } },
            { a4, 10, std::vector<std::shared_ptr<Discount>>{ d3 } }
        },
        c2,
        std::vector<std::shared_ptr<Discount>>{ d4 }
    };

    std::cout << o1 << "\n\n";
    std::cout << o2 << "\n\n";

    auto equal = [](float a, float b) {
        return (std::abs(a - b) < std::numeric_limits<float>::epsilon());
    };

    // Price calculations
    CumulativePriceCalculator cpc{};
    NonCumulativePriceCalculator ncpc{};

    auto cp1{ cpc.calculate(o1) }; std::cout << "Cumulative price for order 1: " << cp1 << "\n";
    auto cp2{ cpc.calculate(o2) }; std::cout << "Cumulative price for order 2: " << cp2 << "\n";
    auto ncp1{ ncpc.calculate(o1) }; std::cout << "Non cumulative price for order 1: " << ncp1 << "\n";
    auto ncp2{ ncpc.calculate(o2) }; std::cout << "Non cumulative price for order 2: " << ncp2 << "\n";

    assert(equal(cp1, 37.4f) and "Error: calculating cumulative price for order 1");
    assert(equal(cp2, 99.36f) and "Error: calculating cumulative price for order 2");
    assert(equal(ncp1, 37.4f) and "Error: calculating non cumulative price for order 1");
    assert(equal(ncp2, 108.0f) and "Error: calculating non cumulative price for order 2");

    std::cout << "\n";
}
