#include <iostream>
#include <memory>

#include <solver/greed_ratio_top_k_solver.h>
#include <utility/expected_coverage_calculator.h>
#include <cost/edge_weight_summer.h>
#include <messages.h>
#include "instance.h"
#include "io/instance_loader.h"

using namespace hh;

int main() {

    DEBUG("Starting in debug mode");
    const std::string fname = "../res/example1.tf";
    const instance tf = instance_loader::load_instance_from_file(fname);
    INFO("Done reading from file!");

    utility_calculator_t uc = std::make_shared<expected_coverage_calculator>(tf.T);
    cost_calculator_t cc = std::make_shared<edge_weight_summer>(tf.G);

    std::unique_ptr<top_k_solver> solver(new greed_ratio_top_k_solver(uc, cc));

    const auto &best = solver->top_k(tf.candidates, tf.G->nodes, tf.k);


    INFO("Top " << tf.k << " candidates: ");
    for (const auto &c : best)
    {
        INFO(std::to_string(c->id));
    }
    return 0;
}
