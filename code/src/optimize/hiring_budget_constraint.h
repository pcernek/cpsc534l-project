//
// Created by paul on 04/01/18.
//

#ifndef HEADHUNTER_BUDGET_CONSTRAINT_H
#define HEADHUNTER_BUDGET_CONSTRAINT_H

#include "constraint.h"

namespace hh
{

class hiring_budget_constraint : public constraint
{
public:
    explicit hiring_budget_constraint(double budget) : budget_(budget)
    {

    }

    bool satisfied_by(const node_array_t &candidate_solution) const override
    {
        double sum = 0;
        for (const node_t &n : candidate_solution)
        {
            sum += n->hiring_cost;
        }
        return sum <= budget_;
    }

private:
    const double budget_;
};

}


#endif //HEADHUNTER_BUDGET_CONSTRAINT_H
