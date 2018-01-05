//
// Created by paul on 04/01/18.
//

#ifndef HEADHUNTER_CONSTRAINT_H
#define HEADHUNTER_CONSTRAINT_H

#include <network/node.h>

namespace hh
{

class constraint
{
public:

    virtual bool satisfied_by(const node_array_t &candidate_solution) const = 0;

};

typedef std::shared_ptr<constraint> constraint_t;

}

#endif //HEADHUNTER_CONSTRAINT_H
