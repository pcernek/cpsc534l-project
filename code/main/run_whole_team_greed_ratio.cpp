#include <iostream>
#include <memory>

#include <utility/expected_coverage_calculator.h>
#include <cost/edge_weight_summer.h>
#include <messages.h>
#include <cost/team_inclusion_cost_adder.h>
#include <function/util_wrapper.h>
#include <function/cost_wrapper.h>
#include <optimize/vacuous_constraint.h>
#include <optimize/hiring_budget_constraint.h>
#include <optimize/greedy_minimizer.h>
#include <function/cost_over_util.h>
#include <optimize/greed_ratio_minimizer.h>
#include "instance.h"
#include "io/instance_loader.h"

using namespace hh;

int main(int argc, char* argv[]) {

    DEBUG("Starting in debug mode");
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

    constraint_t bc = std::make_shared<hiring_budget_constraint>(tf.budget);

    set_function_t inverse_ratio = std::make_shared<cost_over_util>(cc, uc);
    minimizer_t rs_min = std::make_shared<greed_ratio_minimizer>(bc, util_func);

    const auto &result = rs_min->minimize(inverse_ratio, tf.G->nodes);

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
