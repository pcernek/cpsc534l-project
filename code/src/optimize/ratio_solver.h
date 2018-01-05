//
// Created by paul on 23/12/17.
//

#ifndef HEADHUNTER_RATIO_SOLVER_H
#define HEADHUNTER_RATIO_SOLVER_H

#include <utility/utility_calculator.h>
#include <cost/cost_calculator.h>
#include <vector>
#include <memory>
#include <typedefs.h>
#include <network/graph.h>

namespace hh
{

/**
 * A generic base class intended to equip derived classes with the capability of calculating
 * utilities, costs, and their ratios.
 */
class ratio_solver
{
public:

    /**
     * Accepting arbitrary utility and cost functions enhances
     * the flexibility of inheritors of this class.
     * @param uc
     * @param cc
     */
    ratio_solver(utility_calculator_t uc, cost_calculator_t cc) :
            uc_(move(uc)), cc_(move(cc))
    {

    }

    /**
     * Value is defined as the ratio of utility to cost.
     * @param nodes
     * @return
     */
    virtual value_t calc_value(const node_set_t &nodes) const
    {
        return safe_quotient(uc_->calc_utility(nodes), cc_->calc_cost(nodes));
    }

    /**
     * NOTE: Assumes nodes does not contain target_node
     * @param target_node
     * @param nodes
     * @return
     */
    virtual value_t calc_marginal_value(const node_t &target_node, const node_set_t &nodes) const
    {
        return safe_quotient(uc_->calc_marginal_utility(target_node, nodes), cc_->calc_marginal_cost(target_node, nodes));
    }

    virtual value_t calc_inverse_value(const node_set_t &nodes) const
    {
        value_t c = cc_->calc_cost(nodes);
        value_t u = uc_->calc_utility(nodes);
        return safe_quotient(c, u);
    }

    virtual value_t calc_inverse_marginal_value(const node_t &target_node, const node_set_t &nodes) const
    {
        value_t u = uc_->calc_marginal_utility(target_node, nodes);
        value_t c = cc_->calc_marginal_cost(target_node, nodes);
        return safe_quotient(c, u);
    }

protected:
    const utility_calculator_t uc_;
    const cost_calculator_t cc_;

private:
    static value_t safe_quotient(value_t numerator, value_t denominator)
    {
        if (denominator == 0)
        {
            // TODO: This is a hack that couples with checks that verify whether a value was found that is less than a starting max value
            return MAX_VALUE / 100;
        }
        return numerator / denominator;
    }
};

}

#endif //HEADHUNTER_RATIO_SOLVER_H
