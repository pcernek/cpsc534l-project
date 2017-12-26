//
// Created by paul on 22/12/17.
//

#include "edge_weight_summer.h"

hh::value_t hh::edge_weight_summer::calc_cost(const hh::node_array_t &nodes) const
{
    value_t sum = 0;
    for (int i = 0; i < nodes.size(); i++)
    {
        auto node1_id = nodes[i]->id;
        for (int j = i; j < nodes.size(); j++)
        {
            auto node2_id = nodes[j]->id;
            sum += g_->get_edge_weight(node1_id, node2_id);
        }
    }

    return sum;
}
