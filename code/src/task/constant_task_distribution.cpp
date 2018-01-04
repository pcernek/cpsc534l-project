//
// Created by paul on 22/12/17.
//

#include "constant_task_distribution.h"

using namespace hh;

constant_task_distribution::constant_task_distribution(const task_t &t) : constant_task_(t)
{

}

double constant_task_distribution::calc_expectation_over_tasks(std::function<double(const task_t &t)> func) const
{
    return func(constant_task_);
}

double constant_task_distribution::calc_log_likelihood(const task_t &t) const
{
    for (const auto &s: t)
    {
        if (constant_task_.count(s) == 0)
        {
            return -std::numeric_limits<double>::infinity();
        }
    }
    return 0;
}

double constant_task_distribution::calc_likelihood(const task_t &t) const
{
    for (const skill_t  &s : t)
    {
        if (constant_task_.count(s) == 0)
        {
            return 0;
        }
    }
    return 1;
}
