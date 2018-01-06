//
// Created by paul on 05/01/18.
//

#include <utility/expected_coverage_calculator.h>
#include <cost/team_inclusion_cost_adder.h>
#include <function/set_function.h>
#include <optimize/constraint.h>
#include <function/util_wrapper.h>
#include <function/cost_wrapper.h>
#include <optimize/vacuous_constraint.h>
#include <optimize/hiring_budget_constraint.h>
#include <optimize/greedy_minimizer.h>
#include <function/cost_over_util.h>
#include <optimize/greed_ratio_minimizer.h>
#include <function/min_evaluator.h>
#include "dummy_ignore_cost_test.h"

using namespace hh;

TEST_F(dummy_ignore_cost_test, check_rs_subroutine)
{
    utility_calculator_t uc = std::make_shared<expected_coverage_calculator>(tf_.T);
    cost_calculator_t cc = std::make_shared<team_inclusion_cost_adder>();

    set_function_t util_func = std::make_shared<util_wrapper>(uc);
    set_function_t cost_func = std::make_shared<cost_wrapper>(cc);

    // This is a somewhat contrived example where we're applying a hiring constraint to an instance
    // of team formation. We do this because it's easier to think about
    constraint_t bc = std::make_shared<hiring_budget_constraint>(tf_.budget);

    const auto &ground_set = tf_.G->nodes;
    const auto &candidates = tf_.candidates;
    node_set_t combined(ground_set);
    combined.add_all(candidates);

    set_function_t inverse_ratio = std::make_shared<cost_over_util>(cc, uc);
    minimizer_t rs_min = std::make_shared<greed_ratio_minimizer>(bc, util_func);

    auto result = rs_min->minimize(inverse_ratio, combined);

    EXPECT_EQ(1, result.second.size());
    EXPECT_TRUE(result.second.contains(std::make_shared<node>(node{2})));
}

TEST_F(dummy_ignore_cost_test, check_solution)
{
    // TODO: This is supposed to become something
    utility_calculator_t uc = std::make_shared<expected_coverage_calculator>(tf_.T);
    cost_calculator_t cc = std::make_shared<team_inclusion_cost_adder>();

    set_function_t util_func = std::make_shared<util_wrapper>(uc);
    set_function_t cost_func = std::make_shared<cost_wrapper>(cc);

    constraint_t vc = std::make_shared<vacuous_constraint>();
    constraint_t bc = std::make_shared<hiring_budget_constraint>(tf_.budget);
    minimizer_t greedy_min = std::make_shared<greedy_minimizer>(bc);

    set_function_t inverse_ratio = std::make_shared<cost_over_util>(cc, uc);
    minimizer_t rs_min = std::make_shared<greed_ratio_minimizer>(vc, util_func);
    set_function_t inner = std::make_shared<min_evaluator>(tf_.G->nodes, rs_min, inverse_ratio);

    const auto &result = greedy_min->minimize(inner, tf_.candidates);
}