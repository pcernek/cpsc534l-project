//
// Created by paul on 22/12/17.
//

#ifndef HEADHUNTER_GREEDY_RANK_H
#define HEADHUNTER_GREEDY_RANK_H

#include <memory>
#include <list>

#include <network/node.h>
#include <network/graph.h>
#include <task/task_distribution.h>
#include "top_k_solver.h"

namespace hh {

class greed_ratio_top_k_solver : public top_k_solver {

public:

    using top_k_solver::top_k_solver;

    virtual node_array_t top_k(node_array_t candidate_nodes, const node_array_t &all_nodes, size_t k) const override;

private:
    node_array_t nodes_with_positive_marginal_utility(const node_array_t &nodes) const;

    node_t find_best_node(const node_array_t &candidate_nodes, const node_array_t &all_nodes) const;

};

}


#endif //HEADHUNTER_GREEDY_RANK_H
