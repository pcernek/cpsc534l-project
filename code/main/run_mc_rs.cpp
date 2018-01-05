//
// Created by paul on 04/01/18.
//

#include <iostream>
#include <memory>

#include <optimize/greed_ratio_top_k_solver.h>
#include <utility/expected_coverage_calculator.h>
#include <cost/edge_weight_summer.h>
#include <messages.h>
#include <cost/team_inclusion_cost_adder.h>
#include <optimize/minimizer.h>
#include <optimize/monte_carlo_minimizer.h>
#include <optimize/vacuous_constraint.h>
#include <function/min_evaluator.h>
#include <optimize/greed_ratio_minimizer.h>
#include <function/cost_over_util.h>
#include <function/util_wrapper.h>
#include <function/cost_wrapper.h>
#include <optimize/hiring_budget_constraint.h>
#include "instance.h"
#include "io/instance_loader.h"

using namespace hh;

int main(int argc, char* argv[]) {

    DEBUG("Starting run RS MC");
    if (argc < 2)
    {
        std::cerr << "Error: must have at least 1 command line arg for path to input file " << std::endl;
        exit(1);
    }
    const std::string fname(argv[1]);
    DEBUG("Loading file " << fname);
    const instance tf = instance_loader::load_instance_from_file(fname);
    INFO("Finished reading instance from file!");

    utility_calculator_t uc = std::make_shared<expected_coverage_calculator>(tf.T);
    cost_calculator_t cc = std::make_shared<team_inclusion_cost_adder>();

    set_function_t util_func = std::make_shared<util_wrapper>(uc);
    set_function_t cost_func = std::make_shared<cost_wrapper>(cc);

    constraint_t vc = std::make_shared<vacuous_constraint>();
    constraint_t bc = std::make_shared<hiring_budget_constraint>(tf.budget);
    minimizer_t mc_min = std::make_shared<monte_carlo_minimizer>(bc, 10);

    set_function_t inverse_ratio = std::make_shared<cost_over_util>(cc, uc);
    minimizer_t rs_min = std::make_shared<greed_ratio_minimizer>(vc, util_func);
    set_function_t inner = std::make_shared<min_evaluator>(tf.G->nodes, rs_min, inverse_ratio);

    const auto &result = mc_min->minimize(inner, tf.candidates);

    value_t opt_value = result.first;
    const auto &best = result.second;

    INFO("Top " << tf.budget << " candidates: ");
    for (const auto &c : best)
    {
        INFO(std::to_string(c->id));
    }

    INFO("...with a value of " << opt_value);
    return 0;
}
