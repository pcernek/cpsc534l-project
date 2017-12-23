//
// Created by paul on 22/12/17.
//

#ifndef HEADHUNTER_COST_H
#define HEADHUNTER_COST_H

namespace hh
{

class cost_calculator
{

public:

    /**
     * Calculate the cost of the subgraph induced by the given set of nodes.
     * @param nodes
     * @return
     */
    virtual value_t calc_cost(const node_array_t &nodes) const = 0;

    virtual value_t calc_marginal_cost(const node_t &n, const node_array_t &nodes) const
    {
        const auto cost_without = calc_cost(nodes);
        node_array_t augmented_nodes(nodes);
        augmented_nodes.push_back(n);
        const auto cost_with = calc_cost(augmented_nodes);
        return cost_with - cost_without;
    }

};

typedef std::shared_ptr<const cost_calculator> cost_calculator_t;

}


#endif //HEADHUNTER_COST_H
