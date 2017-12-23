//
// Created by paul on 22/12/17.
//

#ifndef HEADHUNTER_BOTTOM_K_SOLVER_H
#define HEADHUNTER_BOTTOM_K_SOLVER_H


#include <vector>
#include <memory>

#include <typedefs.h>
#include <problem/graph.h>
#include <tasks/task_distribution.h>
#include <utility/utility_calculator.h>
#include <cost/cost_calculator.h>

namespace hh
{

class bottom_k_solver
{

public:

    bottom_k_solver(const utility_calculator &uc, const cost_calculator &cc) :
            uc_(uc), cc_(cc)
    {

    }

    virtual std::vector<node_t>
    bottom_k(const graph &g, const task_distribution &t, const std::vector<node_t> &candidates, int k) = 0;

    virtual double calc_inverse_value(const std::vector<node_t> &nodes)
    {
        return cc_.calc_cost(nodes) / uc_.calc_utility(nodes);
    }

    virtual double calc_inverse_marginal_value(const std::shared_ptr<const node> &n, const std::vector<node_t> &nodes)
    {
        return cc_.calc_marginal_cost(n, nodes) / uc_.calc_marginal_utility(n, nodes);
    }

protected:
    const utility_calculator uc_;
    const cost_calculator cc_;

};

}

#endif //HEADHUNTER_BOTTOM_K_SOLVER_H
