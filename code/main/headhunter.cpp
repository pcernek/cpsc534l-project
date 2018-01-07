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
#include "instance.h"
#include "io/instance_loader.h"

using namespace hh;

enum cmd_line_args
{
    PROGRAM_NAME,
    ALGORITHM,
    INSTANCE_FILE_NAME,
    BUDGET,
    CANDIDATES
};

enum algorithm
{
    GREEDY_RS,
    MC_RS,
    MC_MC,
    GREEDY_MC,
    MAX_ALGO
};

struct cmdline_params
{
    algorithm algo;
    std::string instance_file_name;

    bool override_budget = false;
    double budget;

    bool override_candidates = false;
    std::vector<hh::id_t> candidates;
};

algorithm parse_algorithm(const std::string &algo_name)
{
    std::vector<std::string> valid_algos = {
            "greedy_rs",
            "mc_rs",
            "mc_mc",
            "greedy_mc"
    };
    for (auto i = 0; i < MAX_ALGO; i++)
    {
        if (algo_name == valid_algos[i])
        {
            INFO("Running " << algo_name);
            return static_cast<algorithm>(i);
        }
    }

    ERROR("Invalid algorithm specified: " << algo_name);
}

cmdline_params parse_cmdline_args(int argc, char **argv)
{
    cmdline_params p;

    if (argc < INSTANCE_FILE_NAME + 1) {
        ERROR("Insufficient command line arguments.\n"
                      << "Must specify at least choice of algorithm and path to file representing a problem instance.");
    }

    p.algo = parse_algorithm({argv[ALGORITHM]});
    p.instance_file_name = {argv[INSTANCE_FILE_NAME]};

    p.override_budget = (argc >= BUDGET + 1);
    if (p.override_budget) {
        p.budget = std::stod(std::string(argv[BUDGET]));
        INFO("Detected an overriding budget: " << p.budget)
    }

    // every arg thereafter is a candidate id
    p.override_candidates = (argc >= CANDIDATES + 1);
    if (p.override_candidates) {
        for (int i = CANDIDATES; i < argc; i++) {
            auto candidate_id = static_cast<hh::id_t>(std::stoi(argv[i]));
            p.candidates.push_back(candidate_id);
        }

        INFO("Loaded " << p.candidates.size() << " candidates from command line. Overriding those in input file.");
    }

    return p;
}

set_function_t build_objective(const cmdline_params &p, const instance &tf)
{
    set_function_t objective;

    utility_calculator_t uc = std::make_shared<expected_coverage_calculator>(tf.T);
    cost_calculator_t cc = std::make_shared<team_inclusion_cost_adder>();

    set_function_t util_func = std::make_shared<util_wrapper>(uc);
    set_function_t cost_func = std::make_shared<cost_wrapper>(cc);
    set_function_t inverse_ratio = std::make_shared<cost_over_util>(cc, uc);

    constraint_t vc = std::make_shared<vacuous_constraint>();

    const node_set everyone_except_candidates = tf.G->nodes.minus(tf.candidates);

    switch (p.algo)
    {
        case GREEDY_RS:
        case MC_RS: {
            minimizer_t rs_min = std::make_shared<greed_ratio_minimizer>(vc, util_func);
            objective = std::make_shared<min_evaluator>(everyone_except_candidates, rs_min, inverse_ratio);
            break;
        }
        case MC_MC: {
            minimizer_t mc_min1 = std::make_shared<monte_carlo_minimizer>(vc, 100);
            objective = std::make_shared<min_evaluator>(everyone_except_candidates, mc_min1, inverse_ratio);
            break;
        }
        case GREEDY_MC: {
            minimizer_t mc_min2 = std::make_shared<monte_carlo_minimizer>(vc, 200);
            objective = std::make_shared<min_evaluator>(everyone_except_candidates, mc_min2, inverse_ratio);
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
        default:
            // Should never get here if the algorithm parser does its job
            ERROR("Unrecognized algorithm id: " << p.algo);
    }

    return m;
}

int main(int argc, char* argv[]) {

    cmdline_params params = parse_cmdline_args(argc, argv);

    DEBUG("Loading file " << params.instance_file_name);
    instance tf = instance_loader::load_instance_from_file(params.instance_file_name);
    INFO("Finished reading instance from file!");

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

    minimizer_t m = build_minimizer(params, tf);
    set_function_t objective = build_objective(params, tf);

    const auto &result = m->minimize(objective, tf.candidates);

    value_t opt_value = result.first;
    const auto &best = result.second;

    INFO("Top " << tf.budget << " candidates: ");
    for (const auto &c : best.array())
    {
        INFO(std::to_string(c->id));
    }

    INFO("...with a value of " << opt_value);
    return 0;
}
