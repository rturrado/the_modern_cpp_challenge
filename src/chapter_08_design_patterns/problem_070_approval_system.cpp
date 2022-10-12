#include "chapter_08_design_patterns/problem_070_approval_system.h"

#include <fmt/format.h>
#include <fmt/ostream.h>
#include <memory>  // make_shared, make_unique
#include <string>
#include <utility>  // pair
#include <vector>

using namespace tmcppc::company;


namespace tmcppc::company {
    void test_approve_expense(std::ostream& os, const employee& employee) {
        auto expenses{ std::vector<std::pair<double, std::string>>{
            {25, "Breakfast"},
            {250, "Glasses"},
            {2'500, "Laptop"},
            {25'000, "Car"},
            {250'000, "Boat"},
            {2'500'000, "House"}
        }};
        for (const auto& [expense_value, expense_description] : expenses) {
            auto expense{ employee.approve_expense(expense_value, expense_description) };
            fmt::print(os, "\tExpense \"{}\" of value {:.2f} {}.\n",
                expense_description,
                expense_value,
                expense.approved_by_
                    ? fmt::format("approved by {}", expense.approved_by_.value())
                    : "wasn't approved"
            );
        }
    }
}  // namespace tmcppc::company


// Approval system
//
// Write a program for a purchasing department of a company that allows employees to approve new purchases (or expenses).
// However, based on their position, each employee may only approve expenses up to a predefined limit.
// For instance:
//   - regular employees can approve expenses up to 1,000 currency units,
//   - team managers up to 10,000, and
//   - the department manager up to 100,000.
// Any expense greater than that must be explicitly approved by the company president.
void problem_70_main(std::ostream& os) {
    auto p{ std::make_shared<employee>("Joe Biden", std::make_unique<president>()) };
    auto dm{ std::make_shared<employee>("Kamala Harris", std::make_unique<department_manager>()) };
    auto tm{ std::make_shared<employee>("Deb Haaland", std::make_unique<team_manager>()) };
    auto r{ std::make_shared<employee>("Avril Haines", std::make_unique<regular_employee>()) };

    fmt::print(os, "Before calling set_direct_manager...\n");
    test_approve_expense(os, *r);
    fmt::print(os, "\n");

    r->set_direct_manager(tm);
    tm->set_direct_manager(dm);
    dm->set_direct_manager(p);

    fmt::print(os, "After calling set_direct_manager...\n");
    test_approve_expense(os, *p);
    fmt::print(os, "\n");
}
