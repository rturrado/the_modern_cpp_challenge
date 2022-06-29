#include "chapter_08_design_patterns/problem_070_approval_system.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>  // make_shared, make_unique
#include <sstream>  // ostringstream

using namespace tmcppc::company;


TEST(regular_employee_with_no_direct_manager, DISABLED_approve_expense_0) {
    employee re{ "RE", std::make_unique<regular_employee>() };
    auto ex{ re.approve_expense(0, "ex_1") };
    EXPECT_EQ(ex.approved_by_, "RE");
}
TEST(regular_employee_with_no_direct_manager, DISABLED_approve_expense_1_000) {
    employee re{ "RE", std::make_unique<regular_employee>() };
    auto ex{ re.approve_expense(1'000, "ex_2") };
    EXPECT_EQ(ex.approved_by_, "RE");
}
TEST(regular_employee_with_team_manager_as_direct_manager, DISABLED_approve_expense_2_000) {
    employee re{ "RE", std::make_unique<regular_employee>() };
    re.set_direct_manager(std::make_shared<employee>("TM", std::make_unique<team_manager>()));
    auto ex{ re.approve_expense(2'000, "ex_3") };
    EXPECT_EQ(ex.approved_by_, "TM");
}


TEST(team_manager_with_no_direct_manager, DISABLED_approve_expense_10_000) {
    employee tm{ "TM", std::make_unique<team_manager>() };
    auto ex{ tm.approve_expense(10'000, "ex_4") };
    EXPECT_EQ(ex.approved_by_, "TM");
}
TEST(team_manager_with_no_direct_manager, DISABLED_approve_expense_20_000) {
    employee tm{ "TM", std::make_unique<team_manager>() };
    auto ex{ tm.approve_expense(20'000, "ex_5") };
    EXPECT_FALSE(ex.approved_by_);
}
TEST(team_manager_with_department_manager_as_direct_manager, DISABLED_approve_expense_20_000) {
    employee tm{ "TM", std::make_unique<team_manager>() };
    tm.set_direct_manager(std::make_shared<employee>("DM", std::make_unique<department_manager>()));
    auto ex{ tm.approve_expense(20'000, "ex_6") };
    EXPECT_EQ(ex.approved_by_, "DM");
}


TEST(department_manager_with_no_direct_manager, DISABLED_approve_expense_100_000) {
    employee dm{ "DM", std::make_unique<department_manager>() };
    auto ex{ dm.approve_expense(100'000, "ex_7") };
    EXPECT_EQ(ex.approved_by_, "DM");
}
TEST(department_manager_with_no_direct_manager, DISABLED_approve_expense_200_000) {
    employee dm{ "DM", std::make_unique<department_manager>() };
    auto ex{ dm.approve_expense(200'000, "ex_8") };
    EXPECT_FALSE(ex.approved_by_);
}
TEST(department_manager_with_president_as_direct_manager, DISABLED_approve_expense_200_000) {
    employee dm{ "DM", std::make_unique<department_manager>() };
    dm.set_direct_manager(std::make_shared<employee>("P", std::make_unique<president>()));
    auto ex{ dm.approve_expense(200'000, "ex_9") };
    EXPECT_EQ(ex.approved_by_, "P");
}

TEST(president_with_no_direct_manager, DISABLED_approve_expense_200_000) {
    employee p{ "P", std::make_unique<president>() };
    auto ex{ p.approve_expense(200'000, "ex_10") };
    EXPECT_EQ(ex.approved_by_, "P");
}


TEST(problem_70_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_70_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "Before calling set_direct_manager...\n"
        "\tExpense \"Breakfast\" of value 25.00 approved by Avril Haines.\n"
        "\tExpense \"Glasses\" of value 250.00 approved by Avril Haines.\n"
        "\tExpense \"Laptop\" of value 2500.00 wasn't approved.\n"
        "\tExpense \"Car\" of value 25000.00 wasn't approved.\n"
        "\tExpense \"Boat\" of value 250000.00 wasn't approved.\n"
        "\tExpense \"House\" of value 2500000.00 wasn't approved.\n"
        "\n"
        "After calling set_direct_manager...\n"
        "\tExpense \"Breakfast\" of value 25.00 approved by Joe Biden.\n"
        "\tExpense \"Glasses\" of value 250.00 approved by Joe Biden.\n"
        "\tExpense \"Laptop\" of value 2500.00 approved by Joe Biden.\n"
        "\tExpense \"Car\" of value 25000.00 approved by Joe Biden.\n"
        "\tExpense \"Boat\" of value 250000.00 approved by Joe Biden.\n"
        "\tExpense \"House\" of value 2500000.00 approved by Joe Biden.\n"
    ));
}
