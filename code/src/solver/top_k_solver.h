//
// Created by paul on 22/12/17.
//

#ifndef HEADHUNTER_TOP_K_SOLVER_H
#define HEADHUNTER_TOP_K_SOLVER_H

#include <typedefs.h>
#include <network/graph.h>
#include <task/task_distribution.h>

#include <utility>
#include "ratio_solver.h"

namespace hh
{

/**
 * Interface class encapsulating the functionality of any solver of the problem of picking the "top k"
 * most valuable nodes from amongst a set of candidate nodes, where value is defined generically as 
 * utility divided by cost
 */
class top_k_solver : public ratio_solver
{

public:

    using ratio_solver::ratio_solver;

    /**
     * The actual function that solves an instance of the top-k problem
     * @param candidates - candidates from which to choose the top k
     * @param all_nodes - the other nodes to consider when calculating cost and utility
     * @param budget - the maximum feasible total cost of new hires
     * @return the top k most valuable nodes
     */
    virtual node_array_t top_k(node_array_t candidates, const node_array_t &all_nodes, value_t budget) const = 0;

};


}

#endif //HEADHUNTER_TOP_K_SOLVER_H
