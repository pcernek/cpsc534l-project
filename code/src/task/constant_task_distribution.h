//
// Created by paul on 22/12/17.
//

#ifndef HEADHUNTER_CONSTANT_TASK_DISRIBUTION_H
#define HEADHUNTER_CONSTANT_TASK_DISRIBUTION_H

#include "task_distribution.h"

namespace hh
{

class constant_task_distribution : public task_distribution
{

public:
    explicit constant_task_distribution(const task_t &t);

    double calc_expectation_over_tasks(std::function<double(const task_t &t)> func) const override;

    double calc_log_likelihood(const task_t &t) const override;

private:
    const task_t constant_task_;

};

}

#endif //HEADHUNTER_CONSTANT_TASK_DISRIBUTION_H
