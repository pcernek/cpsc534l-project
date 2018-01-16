//
// Created by paul on 04/01/18.
//

#ifndef HEADHUNTER_OPTIMIZER_H
#define HEADHUNTER_OPTIMIZER_H

#include <functional>
#include <network/node.h>
#include "function/set_function.h"

namespace hh
{

class minimizer
{
public:
    virtual std::pair<value_t, node_set_t> minimize(set_function_t f, const node_set_t &candidates) = 0;
};

typedef std::shared_ptr<minimizer> minimizer_t;

}

#endif //HEADHUNTER_OPTIMIZER_H
