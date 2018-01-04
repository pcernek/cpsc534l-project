//
// Created by paul on 21/12/17.
//

#ifndef HEADHUNTER_NODE_H
#define HEADHUNTER_NODE_H

#include <vector>
#include <typedefs.h>

#include "skill.h"

namespace hh
{

const value_t DEFAULT_HIRING_COST = 1;

const value_t DEFAULT_TEAM_INCLUSION_COST = 1;

struct node
{
    node() = delete;

    const id_t id;

    const std::vector<skill_t> skills;

    const value_t hiring_cost;

    const value_t team_inclusion_cost;
};

typedef std::shared_ptr<const node> node_t;

typedef std::vector<node_t> node_array_t;

}

#endif //HEADHUNTER_NODE_H
