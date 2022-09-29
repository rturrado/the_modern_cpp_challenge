#pragma once

#include <initializer_list>
#include <iosfwd>
#include <limits>  // numeric_limits
#include <memory>  // shared_ptr, unique_ptr
#include <optional>
#include <string>
#include <utility>  // move, pair


namespace tmcppc::company {
    struct expense {
        double value_{};
        std::string description_{};
        std::optional<std::string> approved_by_{};
    };


    class employee_role {
    public:
        virtual ~employee_role() = default;

        [[nodiscard]] virtual double get_approval_limit() const noexcept = 0;
    };


    class president : public employee_role {
    public:
        [[nodiscard]] virtual double get_approval_limit() const noexcept override {
            return expense_approval_limit_;
        };
    private:
        const double expense_approval_limit_{ std::numeric_limits<double>::max() };
    };


    class department_manager : public employee_role {
    public:
        [[nodiscard]] virtual double get_approval_limit() const noexcept override {
            return expense_approval_limit_;
        };
    private:
        const double expense_approval_limit_{ 100'000 };
    };


    class team_manager : public employee_role {
    public:
        [[nodiscard]] virtual double get_approval_limit() const noexcept override {
            return expense_approval_limit_;
        };
    private:
        const double expense_approval_limit_{ 10'000 };
    };


    class regular_employee : public employee_role {
    public:
        [[nodiscard]] virtual double get_approval_limit() const noexcept override {
            return expense_approval_limit_;
        };
    private:
        const double expense_approval_limit_{ 1'000 };
    };


    class employee {
    public:
        employee(const std::string& name, std::unique_ptr<employee_role> role)
            : name_{ name }
            , role_{ std::move(role) }
        {}

        void set_direct_manager(const std::shared_ptr<employee>& direct_manager) noexcept {
            direct_manager_ = direct_manager;
        }

        [[nodiscard]] expense approve_expense(double value, const std::string& description) const noexcept {
            if (value <= role_->get_approval_limit()) {
                return expense{ value, description, name_ };
            } else if (direct_manager_) {
                return direct_manager_->approve_expense(value, description);
            } else {
                return expense{ value, description, {} };
            }
        }

    private:
        std::string name_{};
        std::unique_ptr<employee_role> role_;
        std::shared_ptr<employee> direct_manager_{};
    };


    void test_approve_expense(std::ostream& os, const employee& employee);
}  // namespace tmcppc::company


void problem_70_main(std::ostream& os);
void problem_70_main();
