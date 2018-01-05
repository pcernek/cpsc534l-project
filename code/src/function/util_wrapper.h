//
// Created by paul on 04/01/18.
//

#ifndef HEADHUNTER_UTIL_WRAPPER_H
#define HEADHUNTER_UTIL_WRAPPER_H

#include <utility/utility_calculator.h>
#include "set_function.h"

namespace hh
{

class util_wrapper : public set_function
{

public:
    util_wrapper(utility_calculator_t u) : u_(std::move(u))
    {

    }

    value_t eval(const node_array_t &nodes) const override
    {
        return u_->calc_utility(nodes);
    }

private:
    utility_calculator_t u_;
};

}

#endif //HEADHUNTER_UTIL_WRAPPER_H
