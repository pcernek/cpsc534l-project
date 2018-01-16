//
// Created by paul on 07/01/18.
//

#include "brute_force_minimizer.h"

hh::node_set_t hh::brute_force_minimizer::generate_subset(const hh::node_set_t &candidates, size_t subset_id) const
{
    hh::node_set_t subset;
    for (unsigned int j = 0; j < candidates.size(); j++)
    {
        if (subset_id & (1 << j))
        {
            subset.add(candidates.get(j));
        }
    }

    return subset;
}

std::pair<hh::value_t, hh::node_set_t>
hh::brute_force_minimizer::minimize(hh::set_function_t f, const hh::node_set_t &candidates)
{
    value_t min_val_so_far = MAX_VALUE;
    node_set_t best_sample_so_far;

    auto powerSet = static_cast<size_t>(std::pow(2, candidates.size()));
    // Start from 1 -- not interested in the empty set as an optimum
    for (size_t i = 1; i < powerSet; i++)
    {
        node_set_t cur_subset = generate_subset(candidates, i);
        value_t cur_val = f->eval(cur_subset);
        if (cur_val < min_val_so_far)
        {
            min_val_so_far = cur_val;
            best_sample_so_far = cur_subset;
        }

    }

    return std::pair<hh::value_t, hh::node_set_t>(min_val_so_far, best_sample_so_far);
}
