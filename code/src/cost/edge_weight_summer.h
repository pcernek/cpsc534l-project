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

class edge_weight_summer : public cost_calculator
{

public:

    explicit edge_weight_summer(graph_t g) : g_(std::move(g))
    {

    }

    value_t calc_cost(const node_array_t &nodes) const override;

private:

    const std::shared_ptr<const graph> g_;
};

}

#endif //HEADHUNTER_EDGE_WEIGHT_SUMMER_H
