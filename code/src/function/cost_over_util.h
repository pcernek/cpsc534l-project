//
// Created by paul on 04/01/18.
//

#ifndef HEADHUNTER_MOD_OVER_SUBMOD_H
#define HEADHUNTER_MOD_OVER_SUBMOD_H

#include <utility/utility_calculator.h>
#include <cost/cost_calculator.h>
#include <vector>
#include <memory>
#include <typedefs.h>
#include <network/graph.h>
#include "set_function.h"

namespace hh
{

/**
 * A generic base class intended to equip derived classes with the capability of calculating
 * utilities, costs, and their ratios.
 */
class cost_over_util : public set_function
{
public:

    /**
     * Accepting arbitrary utility and cost functions enhances
     * the flexibility of inheritors of this class.
     * @param uc
     * @param cc
     */
    cost_over_util(cost_calculator_t cc, utility_calculator_t uc) :
            uc_(move(uc)), cc_(move(cc))
    {

    }

    value_t eval(const node_array_t &nodes) const override
    {
        value_t c = cc_->calc_cost(nodes);
        value_t u = uc_->calc_utility(nodes);
        return safe_quotient(c, u);
    }

private:
    const utility_calculator_t uc_;
    const cost_calculator_t cc_;
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

#endif //HEADHUNTER_MOD_OVER_SUBMOD_H
