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

std::pair<hh::value_t, hh::node_array_t>
hh::greedy_minimizer::minimize(hh::set_function_t f, const hh::node_array_t &ground_set)
{
    node_array_t candidate_nodes = ground_set;
    std::vector<value_t> solution_values;
    node_array_t cur_candidate_solution;

    while (!candidate_nodes.empty() && c_->satisfied_by(cur_candidate_solution))
    {
        // This is the greedy part
        auto best_node = greedy_choose_node(candidate_nodes, cur_candidate_solution, f);
        cur_candidate_solution.push_back(best_node);
        auto cur_val = f->eval(cur_candidate_solution);
        solution_values.push_back(cur_val);
        // remove other nodes that wouldn't contribute
        candidate_nodes.erase(std::find(candidate_nodes.begin(), candidate_nodes.end(), best_node));
    }

    const auto best_value_iter = min_element(solution_values.begin(), solution_values.end());
    const auto index_of_best_solution = best_value_iter - solution_values.begin();
    const auto solution_slice_end = cur_candidate_solution.begin() + index_of_best_solution + 1;

    const node_array_t solution = {cur_candidate_solution.begin(), solution_slice_end};
    return make_pair(*best_value_iter, solution);
}

hh::node_t
hh::greedy_minimizer::greedy_choose_node(const hh::node_array_t &candidate_nodes,
                                         const hh::node_array_t &cur_solution,
                                         hh::set_function_t f) const
{
    std::vector<value_t> vals(candidate_nodes.size());
    transform(candidate_nodes.begin(), candidate_nodes.end(), vals.begin(),
              [this, cur_solution, f](const node_t &n) {
                  node_array_t combined(cur_solution);
                  combined.insert(combined.end(), n);
                  return f->eval(combined);
              });

    // Find the node from the candidate set with the smallest value
    value_t min_so_far = MAX_VALUE;
    node_t best_node = nullptr;
    for (int i = 0; i < candidate_nodes.size(); i++)
    {
        const auto v = vals[i];
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

//    DEBUG(typeid(*f).name() << " Choosing " << best_node-> id << " with val " << min_so_far);
    return best_node;
}