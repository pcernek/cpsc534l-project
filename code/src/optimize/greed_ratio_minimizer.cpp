//
// Created by paul on 04/01/18.
//

#include "greed_ratio_minimizer.h"

#include <algorithm>
#include <messages.h>

/**
 * TODO: This class contains much code duplicated from greedy_minimizer. Consider merging.
 */

hh::greed_ratio_minimizer::
greed_ratio_minimizer(constraint_t c, set_function_t submodular_denominator) :
        c_(std::move(c)), submodular_denominator_(std::move(submodular_denominator))
{

}

std::pair<hh::value_t, hh::node_set_t>
hh::greed_ratio_minimizer::minimize(set_function_t f, const node_set_t &candidates)
{
    if (candidates.empty())
    {
        WARN("Received empty candidate set as argument for greed_ratio_minimizer.");
        return std::make_pair(MAX_VALUE, candidates);
    }
    node_set_t candidate_copy(candidates.array());
    std::vector<value_t> solution_values;
    node_set_t cur_candidate_solution;

    while (!candidate_copy.empty() && c_->satisfied_by(cur_candidate_solution))
    {
        // This is the greedy part
        auto best_node = greedy_choose_node(candidate_copy, cur_candidate_solution, f);
        cur_candidate_solution.add(best_node);
        if (!c_->satisfied_by(cur_candidate_solution))
        {
            cur_candidate_solution.remove(best_node);
            break;
        }
        auto cur_val = f->eval(cur_candidate_solution);
        solution_values.push_back(cur_val);
        candidate_copy.remove(best_node);
        // remove other nodes that wouldn't contribute
        candidate_copy = remove_useless_candidate_nodes(candidate_copy, cur_candidate_solution, f);
    }

    const auto best_value_iter = min_element(solution_values.begin(), solution_values.end());
    const auto index_of_best_solution = best_value_iter - solution_values.begin();
    const auto solution_slice_end = cur_candidate_solution.array().begin() + index_of_best_solution + 1;

    const node_set_t solution({cur_candidate_solution.array().begin(), solution_slice_end});
    return std::make_pair(*best_value_iter, solution);
}

hh::node_set_t hh::greed_ratio_minimizer::remove_useless_candidate_nodes(const node_set_t &candidates,
                                                                         const node_set_t &cur_solution,
                                                                         const set_function_t f) const
{
    // TODO: This is a bit of a hack to get around our use of a custom container for nodes
    node_array_t filtered(candidates.array());
    auto filtered_end = std::remove_if(filtered.begin(), filtered.end(), [this, cur_solution](const node_t &n){
        bool has_zero_marginal_utility = this->submodular_denominator_->has_zero_marginal_gain(n, cur_solution);
        return has_zero_marginal_utility;
    });
    filtered.erase(filtered_end, filtered.end());
    return node_set_t(filtered);
}

hh::node_t
hh::greed_ratio_minimizer::greedy_choose_node(const node_set_t &candidate_nodes,
                                              const node_set_t &cur_solution,
                                              set_function_t f) const
{
    std::vector<value_t> marginal_gains;
    for (int i = 0; i < candidate_nodes.size(); i++)
    {
        value_t mg = f->marginal_gain(candidate_nodes.array()[i], cur_solution);
        marginal_gains.push_back(mg);
    }

    // Find the node from the candidate set with the smallest marginal gain go the current solution
    value_t min_so_far = MAX_VALUE;
    node_t best_node = nullptr;
    for (int i = 0; i < candidate_nodes.size(); i++)
    {
        const auto v = marginal_gains[i];
        if (v < min_so_far)
        {
            min_so_far = v;
            best_node = candidate_nodes.array()[i];
        }
    }

    if (min_so_far == MAX_VALUE)
    {
        WARN("Of " << candidate_nodes.size() << ", candidate nodes, none were found with value below " << MAX_VALUE);
        throw std::exception(); // this is necessary because otherwise we're returning a null pointer!
    }

    return best_node;
}