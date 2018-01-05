//
// Created by paul on 04/01/18.
//

#include "greed_ratio_minimizer.h"
#include "greedy_minimizer.h"

#include <algorithm>
#include <messages.h>

hh::greed_ratio_minimizer::
greed_ratio_minimizer(constraint_t c, set_function_t submodular_denominator) :
        greedy_minimizer(c), constraint_(std::move(c)), submodular_denominator_(std::move(submodular_denominator))
{

}

hh::node_array_t hh::greed_ratio_minimizer::remove_useless_candidate_nodes(const node_array_t &candidates,
                                                                           const node_array_t &cur_solution,
                                                                           const set_function_t f) const
{
    node_array_t filtered(candidates);
    auto filtered_end = std::remove_if(filtered.begin(), filtered.end(), [this, cur_solution](const node_t &n){
        bool has_zero_marginal_utility = this->submodular_denominator_->has_zero_marginal_gain(n, cur_solution);
        return has_zero_marginal_utility;
    });
    filtered.erase(filtered_end, filtered.end());
    return filtered;
}
