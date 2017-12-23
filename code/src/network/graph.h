//
// Created by paul on 21/12/17.
//

#ifndef HEADHUNTER_GRAPH_H
#define HEADHUNTER_GRAPH_H

#include <memory>
#include <vector>

#include "typedefs.h"
#include "node.h"

namespace hh
{

typedef double edge_weight_t;

typedef std::vector<std::vector<edge_weight_t>> edge_weights_t;

struct graph
{
    graph() = delete;

    const edge_weights_t edge_weights;

    const node_array_t nodes;

    double get_edge_weight(id_t node1_id, id_t node2_id) const
    {
        return edge_weights[node1_id][node2_id];
    }

    const node_t get_node(id_t node_id) const
    {
        return nodes[node_id];
    }

};

typedef std::shared_ptr<const graph> graph_t;

}

#endif //HEADHUNTER_GRAPH_H
