//
// Created by paul on 08/01/18.
//

#ifndef HEADHUNTER_INDEPENDENT_APPROX_DISTRIBUTION_H
#define HEADHUNTER_INDEPENDENT_APPROX_DISTRIBUTION_H

#include <unordered_map>
#include "task_distribution.h"
#include "independent_task_distribution.h"

namespace hh
{

class independent_approx_distribution : public independent_task_distribution
{
public:
    independent_approx_distribution(
                size_t num_samples,
                const std::unordered_map<hh::skill_t, hh::task_distribution::probability_t> &skill_probs);

    double calc_expectation_over_tasks(std::function<double(const task_t &t)> func) const override;

    size_t num_samples;

protected:
    std::unordered_set<skill_t> all_skills_;

    task_t draw_sample(const task_t &ground_set) const;
};

}

#endif //HEADHUNTER_INDEPENDENT_APPROX_DISTRIBUTION_H
