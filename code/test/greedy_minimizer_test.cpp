//
// Created by paul on 05/01/18.
//

#include <optimize/constraint.h>
#include <optimize/vacuous_constraint.h>
#include <function/set_function.h>
#include <function/cost_wrapper.h>
#include <cost/team_inclusion_cost_adder.h>
#include <optimize/greedy_minimizer.h>
#include <optimize/hiring_budget_constraint.h>
#include "greedy_minimizer_test.h"

using namespace hh;

TEST_F(greedy_minimizer_test, hire_all)
{
    constraint_t vc = std::make_shared<vacuous_constraint>();

    // need a function to minimize
    cost_calculator_t team_inclusion = std::make_shared<team_inclusion_cost_adder>();
    set_function_t cw = std::make_shared<cost_wrapper>(team_inclusion);

    node_array_t nodes;
    size_t num_nodes = 5;
    for (size_t i = 0; i < num_nodes; i++)
    {
        node n = {i, std::vector<skill_t>(), 0, -1};
        nodes.push_back(std::make_shared<node>(n));
    }

    greedy_minimizer gm(vc);
    auto result = gm.minimize(cw, nodes);
    EXPECT_EQ(-static_cast<double>(num_nodes), result.first);
    EXPECT_EQ(num_nodes, result.second.size());
}

TEST_F(greedy_minimizer_test, hire_none)
{
    constraint_t vc = std::make_shared<vacuous_constraint>();

    // need a function to minimize
    cost_calculator_t team_inclusion = std::make_shared<team_inclusion_cost_adder>();
    set_function_t cw = std::make_shared<cost_wrapper>(team_inclusion);

    node_array_t nodes;
    size_t num_nodes = 5;
    for (size_t i = 0; i < num_nodes; i++)
    {
        node n = {i, std::vector<skill_t>(), 0, 1};
        nodes.push_back(std::make_shared<node>(n));
    }

    greedy_minimizer gm(vc);
    auto result = gm.minimize(cw, nodes);
    EXPECT_EQ(0, result.first);
    EXPECT_EQ(0, result.second.size());
}

TEST_F(greedy_minimizer_test, hire_constrained)
{
    constraint_t bc = std::make_shared<hiring_budget_constraint>(2);

    // need a function to minimize
    cost_calculator_t team_inclusion = std::make_shared<team_inclusion_cost_adder>();
    set_function_t cw = std::make_shared<cost_wrapper>(team_inclusion);

    node_array_t nodes;
    size_t num_nodes = 5;
    for (size_t i = 0; i < num_nodes; i++)
    {
        node_t n;
        if (i == num_nodes - 2)
        {
            n = std::make_shared<node>(node{i, std::vector<skill_t>(), 1, -3});
        }
        else if (i == num_nodes - 1)
        {
            n = std::make_shared<node>(node{i, std::vector<skill_t>(), 1, -2});
        }
        else
        {
            n = std::make_shared<node>(node{i, std::vector<skill_t>(), 1, -1});
        }
        nodes.push_back(n);
    }

    greedy_minimizer gm(bc);
    auto result = gm.minimize(cw, nodes);

    EXPECT_EQ(-5, result.first);
    EXPECT_EQ(2, result.second.size());
    EXPECT_TRUE(bc->satisfied_by(result.second));
}

