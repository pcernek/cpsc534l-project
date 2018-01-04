//
// Created by paul on 03/01/18.
//

#include <numeric>
#include "team_inclusion_cost_adder.h"

hh::value_t hh::team_inclusion_cost_adder::calc_cost(const hh::node_array_t &nodes) const
{
    return std::accumulate(nodes.begin(), nodes.end(), 0, [](value_t cur_sum, node_t cur_node) {
        return cur_sum + cur_node->team_inclusion_cost;
    });
}
