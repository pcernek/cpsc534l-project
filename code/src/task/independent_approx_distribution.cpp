//
// Created by paul on 08/01/18.
//

#include "independent_approx_distribution.h"

hh::independent_approx_distribution::independent_approx_distribution(
            size_t num_samples,
            const std::unordered_map<hh::skill_t, hh::task_distribution::probability_t> &skill_probs)
        : independent_task_distribution(skill_probs),
          num_samples(num_samples)
{
    for (auto k_v : factored_distribution_)
    {
        skill_t s = k_v.first;
        all_skills_.insert(s);
    }
}

double
hh::independent_approx_distribution::calc_expectation_over_tasks(std::function<double(const hh::task_t &)> func) const
{
    double moving_avg = 0;
    for (int t = 1; t <= num_samples; t++)
    {
        task_t cur_sample = draw_sample(all_skills_);

        value_t cur_val = func(cur_sample);
        moving_avg = (1.0 / t) * (cur_val + moving_avg * (t - 1));
    }
    return moving_avg;
}

hh::task_t hh::independent_approx_distribution::draw_sample(const hh::task_t &ground_set) const
{
    task_t sample;

    for (const skill_t &s : all_skills_)
    {
        if (std::rand() <= factored_distribution_.at(s))
        {
            sample.insert(s);
        }
    }
    return sample;
}