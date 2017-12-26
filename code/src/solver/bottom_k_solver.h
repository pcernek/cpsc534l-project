//
// Created by paul on 22/12/17.
//

#ifndef HEADHUNTER_BOTTOM_K_SOLVER_H
#define HEADHUNTER_BOTTOM_K_SOLVER_H


#include <vector>
#include <memory>

#include <typedefs.h>
#include <network/graph.h>
#include <task/task_distribution.h>
#include <utility/utility_calculator.h>
#include <cost/cost_calculator.h>
#include "ratio_solver.h"

namespace hh
{

/**
 * TODO: This class is out of date, and lags behind e.g. top_k_solver.
 * If in doubt, update the interface of this class by mirroring the interface of top_k_solver.
 */
class bottom_k_solver : public ratio_solver
{

public:
    using ratio_solver::ratio_solver;

    virtual std::vector<node_t>
    bottom_k(const graph &g, const task_distribution &t, const std::vector<node_t> &candidates, int k) = 0;

};

}

#endif //HEADHUNTER_BOTTOM_K_SOLVER_H
