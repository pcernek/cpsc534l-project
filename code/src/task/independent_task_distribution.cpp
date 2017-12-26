//
// Created by paul on 22/12/17.
//

#include "independent_task_distribution.h"

#include <cmath>

using namespace hh;

independent_task_distribution::independent_task_distribution(
        const std::unordered_map<skill_t, probability_t> &likelihoods) :
        factored_distribution_(likelihoods)
{

}

double independent_task_distribution::calc_log_likelihood(const task_t &t) const
{
    probability_t log_likelihood = 0;
    for (const auto &elt : factored_distribution_)
    {
        const skill_t &s = elt.first;
        const probability_t &p = elt.second;
        if (t.count(s) > 0)
        {
            log_likelihood += std::log(p);
        }
        else
        {
            log_likelihood += std::log(1 - p);
        }
    }
    return log_likelihood;
}

double independent_task_distribution::calc_expectation_over_tasks(std::function<double(const task_t &t)> func) const
{
    return 0;
}
