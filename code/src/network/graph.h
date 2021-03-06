//
// Created by paul on 21/12/17.
//

#ifndef HEADHUNTER_GRAPH_H
#define HEADHUNTER_GRAPH_H

#include <memory>
#include <vector>
#include <messages.h>

#include "typedefs.h"
#include "node.h"

namespace hh
{

typedef double edge_weight_t;

typedef std::vector<std::vector<edge_weight_t>> edge_weights_t;

/**
 * Represents a social network, where edge weights correspond to communication costs between nodes.
 * Currently, is always a complete graph.
 */
struct graph
{
    graph() = delete; // Prevent this struct from being instantiated with default values for its members

    /**
     * Currently represented as a full matrix because that's simplest, but could be streamlined.
     */
    const edge_weights_t edge_weights;

    /**
     * It's useful to have a list of pointers to all the nodes in the graph.
     */
    const node_set_t nodes;

    double get_edge_weight(id_t node1_id, id_t node2_id) const
    {
        if (node1_id > edge_weights.size())
        {
            ERROR("Node1 id of " << node1_id << " exceeds number of rows in edge weight table ("
                                << edge_weights.size() << ")!");
        }
        if (node2_id > edge_weights[node1_id].size())
        {
            ERROR("Node2 id of " << node2_id << " exceeds number of cols in edge weight table ("
                                << edge_weights[node1_id].size() << ")!");
        }
        return edge_weights[node1_id][node2_id];
    }

};

typedef std::shared_ptr<const graph> graph_t;

}

#endif //HEADHUNTER_GRAPH_H
