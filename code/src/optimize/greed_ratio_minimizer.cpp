//
// Created by paul on 04/01/18.
//

#include "greed_ratio_minimizer.h"

#include <utility>
#include <algorithm>
#include <constants.h>
#include <messages.h>

hh::greed_ratio_minimizer::
greed_ratio_minimizer(constraint_t c, set_function_t submodular_denominator) :
        constraint_(std::move(c)),
        submodular_denominator_(submodular_denominator)
{

}

std::pair<hh::value_t, hh::node_array_t>
hh::greed_ratio_minimizer::minimize(set_function_t f, const node_array_t &ground_set)
{
    node_array_t candidate_nodes = ground_set;
    std::vector<value_t> solution_values;
    node_array_t cur_candidate_solution;

    while (!candidate_nodes.empty() && constraint_->satisfied_by(cur_candidate_solution))
    {
        // This is the greedy part
        auto best_node = find_best_node(candidate_nodes, cur_candidate_solution, f);
        cur_candidate_solution.push_back(best_node);
        auto cur_val = f->eval(cur_candidate_solution);
        solution_values.push_back(cur_val);
        // remove other nodes that wouldn't contribute
        candidate_nodes = nodes_with_positive_marginal_utility(candidate_nodes);
    }

    const auto best_value_iter = std::min_element(solution_values.begin(), solution_values.end());
    const auto index_of_best_solution = best_value_iter - solution_values.begin();
    const auto solution_slice_end = cur_candidate_solution.begin() + index_of_best_solution + 1;

    const node_array_t solution = {cur_candidate_solution.begin(), solution_slice_end};
    return std::make_pair(*best_value_iter, solution);
}

hh::node_array_t hh::greed_ratio_minimizer::nodes_with_positive_marginal_utility(const hh::node_array_t &nodes) const
{
    node_array_t filtered(nodes);
    auto past_the_end = std::remove_if(filtered.begin(), filtered.end(), [this, nodes](const node_t &n){
        bool has_zero_marginal_utility = this->submodular_denominator_->has_zero_marginal_gain(n, nodes);
        return has_zero_marginal_utility;
    });
    filtered.erase(past_the_end, filtered.end());
    return filtered;
}

hh::node_t hh::greed_ratio_minimizer::find_best_node(const hh::node_array_t &candidate_nodes,
                                                     const hh::node_array_t &cur_solution,
                                                     set_function_t f) const
{
    std::vector<value_t> inverse_marginal_values(candidate_nodes.size());
    std::transform(candidate_nodes.begin(), candidate_nodes.end(), inverse_marginal_values.begin(),
                   [this, cur_solution, f](const node_t &n) {
                       return f->marginal_gain(n, cur_solution);
                   });

    value_t min_so_far = MAX_VALUE;
    node_t best_node = nullptr;
    for (int i = 0; i < candidate_nodes.size(); i++)
    {
        const auto v = inverse_marginal_values[i];
        if (v < min_so_far)
        {
            min_so_far = v;
            best_node = candidate_nodes[i];
        }
    }

    if (min_so_far == MAX_VALUE)
    {
        WARN("Of " << candidate_nodes.size() << ", candidate nodes, none were found with value below " << MAX_VALUE);
        throw std::exception(); // this is necessary because otherwise we're returning a null pointer!
    }

    return best_node;
}
