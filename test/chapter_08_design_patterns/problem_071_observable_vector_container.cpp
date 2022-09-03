#include "chapter_08_design_patterns/problem_071_observable_vector_container.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <fmt/format.h>
#include <memory>  // make_shared
#include <sstream>  // ostringstream

using namespace tmcppc::data_structures;


TEST(observable_vector, copy_assignment) {
    std::ostringstream oss{};
    auto sp_ov_1{ std::make_shared<observable_vector<char>>(std::initializer_list<char>{ 'a', 'b', 'c' }) };
    auto sp_co_1{ std::make_shared<concrete_observer_1<char>>(oss, sp_ov_1) };
    sp_ov_1->attach(sp_co_1);
    auto ov_2{ observable_vector<char>{ 'z', 'x', 'c', 'v', 'b' } };
    *sp_ov_1 = ov_2;
    EXPECT_EQ(sp_ov_1->size(), 5);
    EXPECT_EQ(fmt::format("{}", *sp_ov_1), "['z', 'x', 'c', 'v', 'b']");
    EXPECT_THAT(oss.str(), ::testing::ContainsRegex(
        "\t\\[observer \\d+\\] received notification: <id : \\d+, type : copy_assignment\\(\\)>\n"
        "\t\\[observer \\d+\\] observable vector \\d+: \\['z', 'x', 'c', 'v', 'b'\\]\n"
    ));
}

TEST(observable_vector, move_assignment) {
    std::ostringstream oss{};
    auto sp_ov{ std::make_shared<observable_vector<char>>(std::initializer_list<char>{ 'a', 'b', 'c' }) };
    auto sp_co_1{ std::make_shared<concrete_observer_1<char>>(oss, sp_ov) };
    sp_ov->attach(sp_co_1);
    *sp_ov = observable_vector<char>{ 'z', 'x', 'c', 'v', 'b' };
    EXPECT_EQ(sp_ov->size(), 5);
    EXPECT_EQ(fmt::format("{}", *sp_ov), "['z', 'x', 'c', 'v', 'b']");
    EXPECT_THAT(oss.str(), ::testing::ContainsRegex(
        "\t\\[observer \\d+\\] received notification: <id : \\d+, type : move_assignment\\(\\)>\n"
        "\t\\[observer \\d+\\] observable vector \\d+: \\['z', 'x', 'c', 'v', 'b'\\]\n"
    ));
}

TEST(observable_vector, push_back) {
    std::ostringstream oss{};
    auto sp_ov{ std::make_shared<observable_vector<char>>(std::initializer_list<char>{ 'a', 'b', 'c' }) };
    auto sp_co_1{ std::make_shared<concrete_observer_1<char>>(oss, sp_ov) };
    sp_ov->attach(sp_co_1);
    sp_ov->push_back('d');
    EXPECT_EQ(sp_ov->size(), 4);
    EXPECT_EQ(fmt::format("{}", *sp_ov), "['a', 'b', 'c', 'd']");
    EXPECT_THAT(oss.str(), ::testing::ContainsRegex(
        "\t\\[observer \\d+\\] received notification: <id : \\d+, type : push_back\\(3\\)>\n"
        "\t\\[observer \\d+\\] observable vector \\d+: \\['a', 'b', 'c', 'd'\\]\n"
    ));
}

TEST(observable_vector, pop_back) {
    std::ostringstream oss{};
    auto sp_ov{ std::make_shared<observable_vector<char>>(std::initializer_list<char>{ 'a', 'b', 'c' }) };
    auto sp_co_1{ std::make_shared<concrete_observer_1<char>>(oss, sp_ov) };
    sp_ov->attach(sp_co_1);
    sp_ov->pop_back();
    EXPECT_EQ(sp_ov->size(), 2);
    EXPECT_THAT(oss.str(), ::testing::ContainsRegex(
        "\t\\[observer \\d+\\] received notification: <id : \\d+, type : pop_back\\(2\\)>\n"
        "\t\\[observer \\d+\\] observable vector \\d+: \\['a', 'b'\\]\n"
    ));
}

TEST(observable_vector, clear) {
    std::ostringstream oss{};
    auto sp_ov{ std::make_shared<observable_vector<char>>(std::initializer_list<char>{ 'a', 'b', 'c' }) };
    auto sp_co_1{ std::make_shared<concrete_observer_1<char>>(oss, sp_ov) };
    sp_ov->attach(sp_co_1);
    sp_ov->clear();
    EXPECT_TRUE(sp_ov->empty());
    EXPECT_THAT(oss.str(), ::testing::ContainsRegex(
        "\t\\[observer \\d+\\] received notification: <id : \\d+, type : clear\\(\\)>\n"
        "\t\\[observer \\d+\\] observable vector \\d+: \\[\\]\n"
    ));
}

TEST(observable_vector, detach) {
    std::ostringstream oss{};
    auto sp_ov{ std::make_shared<observable_vector<char>>(std::initializer_list<char>{ 'a', 'b', 'c' }) };
    auto sp_co_1{ std::make_shared<concrete_observer_1<char>>(oss, sp_ov) };
    sp_ov->attach(sp_co_1);
    sp_ov->detach(sp_co_1);
    sp_ov->clear();
    EXPECT_TRUE(sp_ov->empty());
    EXPECT_TRUE(oss.str().empty());
}

TEST(observable_vector, no_observers) {
    observable_vector<char> ov{ 'a', 'b', 'c' };
    ov.push_back('d');
    EXPECT_EQ(ov.size(), 4);
    EXPECT_EQ(fmt::format("{}", ov), "['a', 'b', 'c', 'd']");
}

TEST(observable_vector, two_observers) {
    std::ostringstream oss{};
    auto sp_ov{ std::make_shared<observable_vector<int>>(std::initializer_list<int>{ -1000, 0, 500 }) };
    auto sp_co_1{ std::make_shared<concrete_observer_1<int>>(oss, sp_ov) };
    auto sp_co_2{ std::make_shared<concrete_observer_2<int>>(oss, sp_ov) };
    sp_ov->attach(sp_co_1);
    sp_ov->attach(sp_co_2);
    sp_ov->pop_back();
    EXPECT_EQ(sp_ov->size(), 2);
    EXPECT_EQ(fmt::format("{}", *sp_ov), "[-1000, 0]");
    EXPECT_THAT(oss.str(), ::testing::ContainsRegex(
        "\t\\[observer \\d+\\] received notification: <id : \\d+, type : pop_back\\(2\\)>\n"
        "\t\\[observer \\d+\\] observable vector \\d+: \\[-1000, 0\\]\n"
        "\t\\[observer \\d+\\] received notification: <id : \\d+, type : pop_back\\(2\\)>\n"
        "\t\\[observer \\d+\\] sum of elements of observable vector \\d+: -1000\n"
    ));
}


TEST(problem_71_main, output) {
    std::ostringstream oss{};
    problem_71_main(oss);
    EXPECT_THAT(oss.str(), ::testing::ContainsRegex(
        "Creating the observable vectors:\n"
        "\tov_0: \\[\\]\n"
        "\tov_1: \\[0, 3.14, 6.28, 9.42, 12.56\\]\n"
        "\tov_2: \\[1.5, 1.5, 1.5\\]\n"
        "\tov_3: \\['o', ',', ' ', 'u'\\]\n"
        "\tov_4: \\[\\]\n"
        "\n"
        "Pushing back to ov_0:\n"
        "\t\\[observer \\d+\\] received notification: <id : \\d+, type : push_back\\(0\\)>\n"
        "\t\\[observer \\d+\\] observable vector \\d+: \\[\"Tush! Never tell me;\"\\]\n"
        "\t\\[observer \\d+\\] received notification: <id : \\d+, type : push_back\\(1\\)>\n"
        "\t\\[observer \\d+\\] observable vector \\d+: \\[\"Tush! Never tell me;\", \"I take it much unkindly.\"\\]\n"
        "\n"
        "Copy assigning from ov_3:\n"
        "Popping back from the copied-to vector:\n"
        "\n"
        "Move assigning from ov_1:\n"
        "Pushing back to the moved-to vector:\n"
        "\n"
        "Copy assigning to ov_3:\n"
        "\t\\[observer \\d+\\] received notification: <id : \\d+, type : copy_assignment\\(\\)>\n"
        "\t\\[observer \\d+\\] observable vector \\d+: \\['o', ',', ' '\\]\n"
        "\n"
        "Move assigning to ov_4:\n"
        "\t\\[observer \\d+\\] received notification: <id : \\d+, type : move_assignment\\(\\)>\n"
        "\t\\[observer \\d+\\] sum of elements of observable vector \\d+: 12\n"
        "\n"
        "Detaching from ov_0:\n"
        "Pushing back to ov_0:\n\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::Not(::testing::EndsWith("\n\n\n")));
}
