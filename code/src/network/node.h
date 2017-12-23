//
// Created by paul on 21/12/17.
//

#ifndef HEADHUNTER_NODE_H
#define HEADHUNTER_NODE_H

#include <vector>

#include "skill.h"

namespace hh
{

struct node
{
    node() = delete;

    const id_t id;

    const std::vector<skill_t> skills;
};

typedef std::shared_ptr<const node> node_t;

typedef std::vector<node_t> node_array_t;

}

#endif //HEADHUNTER_NODE_H
