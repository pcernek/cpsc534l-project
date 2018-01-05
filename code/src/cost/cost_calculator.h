//
// Created by paul on 22/12/17.
//

#ifndef HEADHUNTER_COST_H
#define HEADHUNTER_COST_H

namespace hh
{

/**
 * Interface class representing the functionality of calculating the communication
 * cost of a team
 */
class cost_calculator
{

public:

    /**
     * Calculate the cost of the given set of nodes.
     * @param nodes
     * @return
     */
    virtual value_t calc_cost(const node_set_t &nodes) const = 0;

    /**
     * NOTE: Assumes nodes does not contain target_node
     * @param target_node
     * @param nodes
     * @return
     */
    virtual value_t calc_marginal_cost(const node_t &target_node, const node_set_t &nodes) const
    {
        const auto cost_without = calc_cost(nodes);
        node_set_t augmented_nodes(nodes);
        augmented_nodes.add(target_node);
        const auto cost_with = calc_cost(augmented_nodes);
        return cost_with - cost_without;
    }

};

typedef std::shared_ptr<const cost_calculator> cost_calculator_t;

}


#endif //HEADHUNTER_COST_H
