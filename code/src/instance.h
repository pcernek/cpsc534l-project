//
// Created by paul on 21/12/17.
//

#ifndef HEADHUNTER_INSTANCE_H
#define HEADHUNTER_INSTANCE_H


#include "network/graph.h"
#include "task/task_distribution.h"

#include <memory>

namespace hh
{

/**
 * A container to group all the elements of an instance of the top-k or bottom-k problem.
 * Note that "top-k" corresponds to "give me the top k most valuable employees in the network
 * (given the task distribution)"
 *
 * TODO: Currently doesn't specify whether it's top-k or bottom-k. Should we add this?
 */
struct instance
{
    instance() = delete; // Prevent this struct from being instantiated with default values for its members

    const graph_t G;

    const task_distribution_t T;

    /**
     * A subset of all the nodes in the graph. We limit our search over these nodes.
     * If you want to search over the entire set, just set the candidate nodes equal to
     * the set of all nodes in the graph.
     */
    const node_array_t candidates;

    /**
     * The 'k' in either "top-k" or "bottom-k"
     */
    const size_t k;
};

}


#endif //HEADHUNTER_INSTANCE_H
