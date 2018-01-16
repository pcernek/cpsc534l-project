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
 * The exact nature of the optimization routine (max hire, min fire, etc.) to be performed on this
 * instance is intentionally left unspecified.
 */
struct instance
{
    instance() = delete; // Prevent this struct from being instantiated with default values for its members

    const graph_t G;

    const task_distribution_t T;

    /**
     * The set of nodes forming the initial organization. We make this a subset of the whole graph
     * to allow for more flexible permutations on the number/set of candidates while keeping a
     * consistent initial membership of the organization.
     */
    node_set_t ground_set;

    /**
     * A subset of all the nodes in the graph. We limit our search over these nodes.
     * If you want to search over the entire set, just set the candidate nodes equal to
     * the set of all nodes in the graph.
     */
    node_set_t candidates;

    /**
     * Budget with which to hire
     */
    value_t budget;
};

typedef std::shared_ptr<instance> instance_t;

}


#endif //HEADHUNTER_INSTANCE_H
