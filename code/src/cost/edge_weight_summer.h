//
// Created by paul on 22/12/17.
//

#ifndef HEADHUNTER_EDGE_WEIGHT_SUMMER_H
#define HEADHUNTER_EDGE_WEIGHT_SUMMER_H

#include <typedefs.h>
#include <network/graph.h>

#include <utility>
#include "cost_calculator.h"

namespace hh
{

/**
 * The simplest communication cost function you can imagine: just add up the edge weights in the induced
 * subgraph of the team you're considering.
 *
 * Nice, because it's MODULAR.
 *
 * N.B. "summer" as in "doer of sums", not the season
 */
class edge_weight_summer : public cost_calculator
{

public:

    /**
     * Presumes that we'll want to compute the costs of many different subsets of nodes on a single
     * underlying graph that never changes (during the lifetime of this object)
     * @param g - the underlying graph
     */
    explicit edge_weight_summer(graph_t g) : g_(std::move(g))
    {

    }

    /**
     * Implemented as if the graph were undirected (uses only the upper left diagonal of the edge cost matrix).
     * @param nodes - the nodes representing a team for which to compute communication cost
     * @return the sum of the edge weights of the subgraph induced by these nodes on the underlying graph
     */
    value_t calc_cost(const node_array_t &nodes) const override;

private:

    const std::shared_ptr<const graph> g_;
};

}

#endif //HEADHUNTER_EDGE_WEIGHT_SUMMER_H
