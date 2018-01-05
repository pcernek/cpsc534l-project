//
// Created by paul on 04/01/18.
//

#ifndef HEADHUNTER_VACUOUS_CONSTRAINT_H
#define HEADHUNTER_VACUOUS_CONSTRAINT_H

#include "constraint.h"

namespace hh
{

class vacuous_constraint : public constraint
{
public:
    bool satisfied_by(const node_array_t &candidate_solution) const override
    {
        return true;
    }
};

}

#endif //HEADHUNTER_VACUOUS_CONSTRAINT_H
