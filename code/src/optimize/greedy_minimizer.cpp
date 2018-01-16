//
// Created by paul on 04/01/18.
//

#include <algorithm>
#include <messages.h>
#include <iostream>
#include <ostream>
#include <utility>
#include "greedy_minimizer.h"
#include "greed_ratio_minimizer.h"

hh::greedy_minimizer::greedy_minimizer(hh::constraint_t c) : c_(std::move(c))
{

}

std::pair<hh::value_t, hh::node_set_t>
hh::greedy_minimizer::minimize(hh::set_function_t f, const hh::node_set_t &candidates)
{
    if (candidates.empty())
    {
        WARN("Received empty ground set as argument for greed_ratio_minimizer.");
        return std::make_pair(MAX_VALUE, candidates);
    }
    node_set_t candidates_copy = candidates;
    std::vector<value_t> solution_values;
    node_set_t cur_candidate_solution;

    while (!candidates_copy.empty() && c_->satisfied_by(cur_candidate_solution))
    {
        // This is the greedy part
        auto best_node = greedy_choose_node(candidates_copy, cur_candidate_solution, f);
        cur_candidate_solution.add(best_node);
        if (!c_->satisfied_by(cur_candidate_solution))
        {
            cur_candidate_solution.remove(best_node);
            break;
        }
        auto cur_val = f->eval(cur_candidate_solution);
        solution_values.push_back(cur_val);
        candidates_copy.remove(best_node);
    }

    const auto best_value_iter = min_element(solution_values.begin(), solution_values.end());
    const auto index_of_best_solution = best_value_iter - solution_values.begin();
    const auto solution_slice_end = cur_candidate_solution.array().begin() + index_of_best_solution + 1;

    const node_set_t solution({cur_candidate_solution.array().begin(), solution_slice_end});
    return std::make_pair(*best_value_iter, solution);
}

hh::node_t
hh::greedy_minimizer::greedy_choose_node(const hh::node_set_t &candidate_nodes,
                                         const hh::node_set_t &cur_solution,
                                         hh::set_function_t f) const
{
    std::vector<value_t> vals(candidate_nodes.size());
    for (int i = 0; i < candidate_nodes.size(); i++)
    {
        node_set_t combined(cur_solution.array());
        combined.add(candidate_nodes.array()[i]);
        vals[i] = f->eval(combined);
    }

    // Find the node from the candidate set with the smallest value
    value_t min_so_far = MAX_VALUE;
    node_t best_node = nullptr;
    for (int i = 0; i < candidate_nodes.size(); i++)
    {
        const auto v = vals[i];
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
