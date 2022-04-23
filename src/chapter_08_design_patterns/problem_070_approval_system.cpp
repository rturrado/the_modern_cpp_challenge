#include "chapter_08_design_patterns/problem_070_approval_system.h"

#include <format>
#include <initializer_list>
#include <iomanip>  // fixed, setprecision
#include <iostream>  // cout
#include <limits>  // numeric_limits
#include <memory>  // make_shared, make_unique, shared_ptr, unique_ptr
#include <optional>
#include <utility>  // pair

struct Expense
{
    double value_{};
    std::string description_{};
    std::optional<std::string> approved_by_{};
};

class EmployeeRole
{
public:
    virtual ~EmployeeRole() = default;

    [[nodiscard]] virtual double get_approval_limit() const noexcept = 0;
};

class President : public EmployeeRole
{
public:
    [[nodiscard]] virtual double get_approval_limit() const noexcept override { return expense_approval_limit_; };
private:
    const double expense_approval_limit_{ std::numeric_limits<double>::max() };
};

class DepartmentManager : public EmployeeRole
{
public:
    [[nodiscard]] virtual double get_approval_limit() const noexcept override { return expense_approval_limit_; };
private:
    const double expense_approval_limit_{ 100'000 };
};

class TeamManager : public EmployeeRole
{
public:
    [[nodiscard]] virtual double get_approval_limit() const noexcept override { return expense_approval_limit_; };
private:
    const double expense_approval_limit_{ 10'000 };
};

class Regular : public EmployeeRole
{
public:
    [[nodiscard]] virtual double get_approval_limit() const noexcept override { return expense_approval_limit_; };
private:
    const double expense_approval_limit_{ 1'000 };
};

class Employee
{
public:
    Employee(const std::string& name, std::unique_ptr<EmployeeRole> role) : name_{ name }, role_{ std::move(role) } {}

    void set_direct_manager(std::shared_ptr<Employee> direct_manager) noexcept { direct_manager_ = direct_manager; }

    [[nodiscard]] Expense approve_expense(double value, const std::string& description) const noexcept
    {
        if (value <= role_->get_approval_limit()) { return Expense{ value, description, name_ }; }
        else if (direct_manager_) { return direct_manager_->approve_expense(value, description); }
        else { return Expense{ value, description, {} }; }
    }

private:
    std::string name_{};
    std::unique_ptr<EmployeeRole> role_;
    std::shared_ptr<Employee> direct_manager_{};
};

void test_approve_expense(std::shared_ptr<Employee> employee)
{
    for (auto [expense_value, expense_description]
        : std::initializer_list<std::pair<double, std::string>>{
            {25, "Breakfast"},
            {250, "Glasses"},
            {2'500, "Laptop"},
            {25'000, "Car"},
            {250'000, "Boat"},
            {2'500'000, "House"}
        })
    {
        auto expense{ employee->approve_expense(expense_value, expense_description) };
        std::cout << "\tExpense \"" << expense_description
            << "\" of value " << std::fixed << std::setprecision(2) << expense_value
            << (expense.approved_by_ ? std::format(" approved by {}", expense.approved_by_.value()) : " wasn't approved") << ".\n";
    }
}

// Approval system
//
// Write a program for a purchasing department of a company that allows employees to approve new purchases (or expenses).
// However, based on their position, each employee may only approve expenses up to a predefined limit.
// For instance:
//   - regular employees can approve expenses up to 1,000 currency units,
//   - team managers up to 10,000, and
//   - the department manager up to 100,000.
// Any expense greater than that must be explicitly approved by the company president.
void problem_70_main()
{
    auto president{ std::make_shared<Employee>("Joe Biden", std::make_unique<President>()) };
    auto department_manager{ std::make_shared<Employee>("Kamala Harris", std::make_unique<DepartmentManager>()) };
    auto team_manager{ std::make_shared<Employee>("Deb Haaland", std::make_unique<TeamManager>()) };
    auto regular{ std::make_shared<Employee>("Avril Haines", std::make_unique<Regular>()) };

    std::cout << "Before calling set_direct_manager...\n";
    test_approve_expense(regular);
    std::cout << "\n";

    regular->set_direct_manager(team_manager);
    team_manager->set_direct_manager(department_manager);
    department_manager->set_direct_manager(president);

    std::cout << "After calling set_direct_manager...\n";
    test_approve_expense(regular);
    std::cout << "\n";
}
