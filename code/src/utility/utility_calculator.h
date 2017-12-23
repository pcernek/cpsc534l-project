//
// Created by paul on 22/12/17.
//

#ifndef HEADHUNTER_UTILITY_CALCULATOR_H
#define HEADHUNTER_UTILITY_CALCULATOR_H

#include <memory>

#include <typedefs.h>
#include <constants.h>

namespace hh
{

class utility_calculator
{

public:

    virtual value_t calc_utility(const node_array_t &nodes) const = 0;

    /**
     * NOTE: Assumes nodes does not contain the target node
     * @param target_node
     * @param nodes
     * @return
     */
    virtual value_t calc_marginal_utility(const node_t &target_node, const node_array_t &nodes) const
    {
        const auto util_without = calc_utility(nodes);
        node_array_t augmented_nodes(nodes);
        augmented_nodes.push_back(target_node);
        const auto util_with = calc_utility(augmented_nodes);
        return util_with - util_without;
    }

    virtual bool has_zero_marginal_utility(const node_t &target_node, const node_array_t &nodes) const
    {
        const auto util_without = calc_utility(nodes);
        node_array_t augmented_nodes(nodes);
        augmented_nodes.push_back(target_node);
        const auto util_with = calc_utility(augmented_nodes);
        return util_with - util_without < (util_without * NEGLIGIBLE_FRACTION_FOR_MARGINAL_GAIN);
    }

};

typedef std::shared_ptr<const utility_calculator> utility_calculator_t;

}

#endif //HEADHUNTER_UTILITY_CALCULATOR_H
