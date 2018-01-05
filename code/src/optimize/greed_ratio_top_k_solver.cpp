//
// Created by paul on 22/12/17.
//

#include "greed_ratio_top_k_solver.h"

#include <algorithm>

using namespace hh;

std::pair<value_t, node_array_t> greed_ratio_top_k_solver::top_k(node_array_t candidate_nodes, const node_array_t &all_nodes,
                                             value_t budget) const
{
    DEBUG("Now running greed ratio to find top " << budget << " candidates");

    std::vector<value_t> solution_values;
    node_array_t cur_candidate_solution;

    while (!candidate_nodes.empty() && cur_candidate_solution.size() < budget)
    {
        candidate_nodes = nodes_with_positive_marginal_utility(candidate_nodes);
        // This is the greedy part
        auto best_node = find_best_node(candidate_nodes, cur_candidate_solution);
        cur_candidate_solution.push_back(best_node);
        auto cur_val = calc_value(cur_candidate_solution);
        solution_values.push_back(cur_val);
    }

    const auto best_value_iter = std::min_element(solution_values.begin(), solution_values.end());
    const auto index_of_best_solution = best_value_iter - solution_values.begin();
    const auto solution_slice_end = cur_candidate_solution.begin() + index_of_best_solution + 1;

    const node_array_t solution = {cur_candidate_solution.begin(), solution_slice_end};
    return std::make_pair(*best_value_iter, solution);
}

node_array_t greed_ratio_top_k_solver::nodes_with_positive_marginal_utility(const node_array_t &nodes) const
{
    node_array_t filtered(nodes);
    std::remove_if(filtered.begin(), filtered.end(), [this, nodes](const node_t &n){
        return this->uc_->has_zero_marginal_utility(n, nodes);
    });
    return filtered;
}

node_t
greed_ratio_top_k_solver::find_best_node(const node_array_t &candidate_nodes, const node_array_t &cur_solution) const
{
    std::vector<value_t> inverse_marginal_values(candidate_nodes.size());
    std::transform(candidate_nodes.begin(), candidate_nodes.end(), inverse_marginal_values.begin(),
                   [this, cur_solution](const node_t &n) {
                       return this->calc_inverse_marginal_value(n, cur_solution);
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