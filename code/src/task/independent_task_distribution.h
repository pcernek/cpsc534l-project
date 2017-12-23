//
// Created by paul on 22/12/17.
//

#ifndef HEADHUNTER_INDEPENDENT_TASK_DISTRIBUTION_H
#define HEADHUNTER_INDEPENDENT_TASK_DISTRIBUTION_H

#include <unordered_map>

#include "task/task_distribution.h"

namespace hh
{

class independent_task_distribution : public task_distribution
{

public:
    explicit independent_task_distribution(const std::unordered_map<skill_t, probability_t> &likelihoods);

    double calc_expectation_over_tasks(std::function<double(const task_t &t)> func) const override;

    double calc_log_likelihood(const task_t &t) const override;

private:
    const std::unordered_map<skill_t, probability_t> factored_distribution_;
};

}

#endif //HEADHUNTER_INDEPENDENT_TASK_DISTRIBUTION_H
