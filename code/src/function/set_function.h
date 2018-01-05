//
// Created by paul on 04/01/18.
//

#ifndef HEADHUNTER_SUBMODULAR_SET_FUNCTION_H
#define HEADHUNTER_SUBMODULAR_SET_FUNCTION_H

#include <network/node.h>
#include <constants.h>
#include "typedefs.h"

namespace hh
{

/**
 * Assumptions: function represented is monotone, non-decreasing, >= 0
 */
class set_function
{
public:
    virtual value_t eval(const node_array_t &nodes) const = 0;

    value_t marginal_gain(const node_t &n, const node_array_t &nodes) const
    {
        const auto val_without = eval(nodes);
        node_array_t augmented_nodes(nodes);
        augmented_nodes.add(n);
        const auto val_with = eval(augmented_nodes);
        return val_with - val_without;
    }

    bool has_zero_marginal_gain(const node_t &n, const node_array_t &nodes) const
    {
        const auto util_without = eval(nodes);
        node_array_t augmented_nodes(nodes);
        augmented_nodes.add(n);
        const auto util_with = eval(augmented_nodes);
        bool has_zero_marginal_utility = util_with - util_without < (util_without * NEGLIGIBLE_FRACTION_FOR_MARGINAL_GAIN);
    }
};

typedef std::shared_ptr<set_function> set_function_t;

}

#endif //HEADHUNTER_SUBMODULAR_SET_FUNCTION_H
