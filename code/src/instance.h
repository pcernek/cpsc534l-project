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

struct instance
{
    instance() = delete;

    const graph_t G;

    const task_distribution_t T;

    const node_array_t candidates;

    const size_t k;
};

}


#endif //HEADHUNTER_INSTANCE_H
