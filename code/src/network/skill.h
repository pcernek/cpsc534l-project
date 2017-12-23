//
// Created by paul on 21/12/17.
//

#ifndef HEADHUNTER_SKILL_H
#define HEADHUNTER_SKILL_H

#include <string>
#include <memory>

namespace hh
{

struct skill
{
    skill() = delete;

    const id_t id;

    bool operator==(const skill &other) const
    {
        return id == other.id;
    }
};

typedef std::shared_ptr<const skill> skill_t;

}

#endif //HEADHUNTER_SKILL_H
