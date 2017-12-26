//
// Created by paul on 21/12/17.
//

#ifndef HEADHUNTER_SKILL_H
#define HEADHUNTER_SKILL_H

#include <string>
#include <memory>

namespace hh
{

typedef id_t skill;
/**
 * If this funny business persists, it's due to an experimental change intended to be as backward-compatible as possible.
 */
typedef skill skill_t;

//struct skill
//{
//    skill() = delete; // Prevent this struct from being instantiated with default values for its members
//
//    const id_t id;
//
//    bool operator==(const skill &other) const
//    {
//        return id == other.id;
//    }
//};

//typedef std::shared_ptr<const skill> skill_t;

}

#endif //HEADHUNTER_SKILL_H
