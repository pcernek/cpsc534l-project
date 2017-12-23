//
// Created by paul on 21/12/17.
//

#ifndef HEADHUNTER_SKILL_DISTRIBUTION_H
#define HEADHUNTER_SKILL_DISTRIBUTION_H

#include <typedefs.h>
#include <network/skill.h>

namespace hh
{

typedef std::unordered_set<skill_t> task_t;

class task_distribution {

public:

    typedef double probability_t;

    virtual double calc_expectation_over_tasks(std::function<double(const task_t &t)> func) const = 0;

    virtual double calc_log_likelihood(const task_t &t) const = 0;
};

typedef std::shared_ptr<const task_distribution> task_distribution_t;

}

#endif //HEADHUNTER_SKILL_DISTRIBUTION_H
