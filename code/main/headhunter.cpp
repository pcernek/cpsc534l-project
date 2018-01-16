//
// Created by paul on 07/01/18.
//

#include <iostream>
#include <memory>

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
#include <chrono>
#include <sstream>
#include <optimize/brute_force_minimizer.h>
#include "instance.h"
#include "io/instance_loader.h"
#include "argparse.h"

using namespace hh;

set_function_t build_objective(const cmdline_params &p, const instance &tf)
{
    set_function_t objective;

    utility_calculator_t uc = std::make_shared<expected_coverage_calculator>(tf.T);
    cost_calculator_t cc = std::make_shared<team_inclusion_cost_adder>();

    set_function_t util_func = std::make_shared<util_wrapper>(uc);
    set_function_t cost_func = std::make_shared<cost_wrapper>(cc);
    set_function_t inverse_ratio = std::make_shared<cost_over_util>(cc, uc);

    constraint_t vc = std::make_shared<vacuous_constraint>();

    switch (p.algo)
    {
        case GREEDY_RS:
        case MC_RS: {
            minimizer_t rs_min = std::make_shared<greed_ratio_minimizer>(vc, util_func);
            objective = std::make_shared<min_evaluator>(tf.ground_set, rs_min, inverse_ratio);
            break;
        }
        case MC_MC: {
            minimizer_t mc_min1 = std::make_shared<monte_carlo_minimizer>(vc, 100);
            objective = std::make_shared<min_evaluator>(tf.ground_set, mc_min1, inverse_ratio);
            break;
        }
        case GREEDY_MC: {
            minimizer_t mc_min2 = std::make_shared<monte_carlo_minimizer>(vc, 200);
            objective = std::make_shared<min_evaluator>(tf.ground_set, mc_min2, inverse_ratio);
            break;
        }
        case BRUTE_FORCE: {
            minimizer_t brute_min = std::make_shared<brute_force_minimizer>();
            objective = std::make_shared<min_evaluator>(tf.ground_set, brute_min, inverse_ratio);
            break;
        }
        default:
            // Should never get here if the algorithm parser does its job
            ERROR("Unrecognized algorithm id: " << p.algo);
    }

    return objective;
}

minimizer_t build_minimizer(const cmdline_params &p, const instance &tf)
{
    minimizer_t m;

    constraint_t bc = std::make_shared<hiring_budget_constraint>(tf.budget);

    switch (p.algo)
    {
        case GREEDY_RS:
        case GREEDY_MC: {
            m = std::make_shared<greedy_minimizer>(bc);
            break;
        }
        case MC_RS: {
            m = std::make_shared<monte_carlo_minimizer>(bc, 20);
            break;
        }
        case MC_MC: {
            m = std::make_shared<monte_carlo_minimizer>(bc, 50);
            break;
        }
        case BRUTE_FORCE: {
            m = std::make_shared<brute_force_minimizer>();
            break;
        }
        default:
            // Should never get here if the algorithm parser does its job
            ERROR("Unrecognized algorithm id: " << p.algo);
    }

    return m;
}

void amend_instance(const cmdline_params &params, instance &tf)
{
    if (params.override_budget)
    {
        tf.budget = params.budget;
    }
    if (params.override_candidates)
    {
        tf.candidates.clear();
        for (const auto &c : params.candidates)
        {
            tf.candidates.add(tf.G->nodes.get(c));
        }
    }
    if (params.override_ground_set)
    {
        tf.ground_set.clear();
        for (const auto &v : params.ground_set)
        {
            tf.ground_set.add(tf.G->nodes.get(v));
        }
    }
}

int main(int argc, char* argv[]) {

    cmdline_params params = parse_cmdline_args(argc, argv);

    DEBUG("Loading file " << params.instance_file_name);
    instance tf = instance_loader::load_instance_from_file(params.instance_file_name);
    INFO("Finished reading instance from file!");

    amend_instance(params, tf);

    minimizer_t m = build_minimizer(params, tf);
    set_function_t objective = build_objective(params, tf);

    auto start = std::chrono::system_clock::now();
    const auto &result = m->minimize(objective, tf.candidates);
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    RESULT("Elapsed time (s): " << elapsed_seconds.count());

    value_t opt_value = result.first;
    const auto &best = result.second;

    // Make a results string
    std::ostringstream candidate_id_accumulator;
    for (const auto &c : best.array())
    {
        candidate_id_accumulator << std::to_string(c->id) << " ";
    }
    RESULT("Top candidates: " << candidate_id_accumulator.str());

    RESULT("Value of objective: " << opt_value);
    return 0;
}
