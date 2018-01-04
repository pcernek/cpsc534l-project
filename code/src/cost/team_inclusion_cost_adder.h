//
// Created by paul on 03/01/18.
//

#ifndef HEADHUNTER_NODE_COST_ADDER_H
#define HEADHUNTER_NODE_COST_ADDER_H

#include <network/graph.h>
#include "cost_calculator.h"

namespace hh
{

class team_inclusion_cost_adder : public cost_calculator
{
public:
/**
     * Presumes that we'll want to compute the costs of many different subsets of nodes on a single
     * underlying graph that never changes (during the lifetime of this object)
     * @param g - the underlying graph
     */
    explicit team_inclusion_cost_adder(graph_t g) : g_(std::move(g))
    {

    }

    /**
     * Implemented as if the graph were undirected (uses only the upper left diagonal of the edge cost matrix).
     * @param nodes - the nodes representing a team for which to compute communication cost
     * @return the sum of the team inclusion costs of the nodes
     */
    value_t calc_cost(const node_array_t &nodes) const override;

private:

    const std::shared_ptr<const graph> g_;

};

}

#endif //HEADHUNTER_NODE_COST_ADDER_H
