#include <iostream>
#include <memory>

#include <optimize/greed_ratio_top_k_solver.h>
#include <utility/expected_coverage_calculator.h>
#include <cost/edge_weight_summer.h>
#include <messages.h>
#include <cost/team_inclusion_cost_adder.h>
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

    std::unique_ptr<top_k_solver> solver(new greed_ratio_top_k_solver(uc, cc));

    const auto &result = solver->top_k(tf.candidates, tf.G->nodes, tf.budget);

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
