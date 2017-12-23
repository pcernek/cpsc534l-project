//
// Created by paul on 22/12/17.
//

#ifndef HEADHUNTER_HEADHUNTER_SOLVER_H
#define HEADHUNTER_HEADHUNTER_SOLVER_H

#include <typedefs.h>
#include <network/graph.h>
#include <task/task_distribution.h>
#include <utility/utility_calculator.h>
#include <cost/cost_calculator.h>

#include <utility>

namespace hh
{

class top_k_solver
{

public:

    top_k_solver(utility_calculator_t uc, cost_calculator_t cc) :
            uc_(std::move(uc)), cc_(std::move(cc))
    {

    }

    virtual node_array_t top_k(node_array_t candidates, const node_array_t &all_nodes, size_t k) const = 0;

    virtual value_t calc_value(const node_array_t &nodes) const
    {
        return uc_->calc_utility(nodes) / cc_->calc_cost(nodes);
    }

    virtual value_t calc_marginal_value(const node_t &n, const node_array_t &nodes) const
    {
        return uc_->calc_marginal_utility(n, nodes) / cc_->calc_marginal_cost(n, nodes);
    }

protected:
    const utility_calculator_t uc_;
    const cost_calculator_t cc_;

};


}

#endif //HEADHUNTER_HEADHUNTER_SOLVER_H
