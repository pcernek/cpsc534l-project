//
// Created by paul on 03/01/18.
//

#include <numeric>
#include "team_inclusion_cost_adder.h"

hh::value_t hh::team_inclusion_cost_adder::calc_cost(const hh::node_set_t &nodes) const
{
    value_t sum = 0;
    for (const node_t &n : nodes.array())
    {
        sum += n->team_inclusion_cost;
    }
    return sum;
}
