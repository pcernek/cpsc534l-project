//
// Created by paul on 04/01/18.
//

#ifndef HEADHUNTER_COST_WRAPPER_H
#define HEADHUNTER_COST_WRAPPER_H

#include <cost/cost_calculator.h>
#include "set_function.h"

namespace hh
{

class cost_wrapper : public set_function
{

public:
    explicit cost_wrapper(cost_calculator_t c) : c_(std::move(c))
    {

    }

    value_t eval(const node_array_t &nodes) const override
    {
        return c_->calc_cost(nodes);
    }

private:
    const cost_calculator_t c_;
};

}

#endif //HEADHUNTER_COST_WRAPPER_H
