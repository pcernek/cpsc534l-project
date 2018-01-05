//
// Created by paul on 04/01/18.
//

#include "monte_carlo_minimizer.h"

#include <utility>

namespace hh
{

monte_carlo_minimizer::monte_carlo_minimizer(constraint_t constraint, size_t num_samples) :
        constraint_(std::move(constraint)), num_samples_(num_samples), gen_(rd_())
{

}

std::pair<value_t, node_set_t>
monte_carlo_minimizer::minimize(set_function_t f, const node_set_t &ground_set)
{
    value_t min_val_so_far = MAX_VALUE;
    node_set_t best_so_far = ground_set;

    for (int i = 0; i < num_samples_; i++)
    {
        node_set_t cur_sample = draw_sample(ground_set);
        if(!constraint_->satisfied_by(cur_sample))
        {
            i--; // TODO: Make sure that this is the desired behavior
            continue;
        }
        value_t cur_val = f->eval(cur_sample);
        if (cur_val < min_val_so_far)
        {
            min_val_so_far = cur_val;
            best_so_far = cur_sample;
        }
    }
    return {min_val_so_far, best_so_far};
}

void monte_carlo_minimizer::set_num_samples(size_t num_samples)
{
    num_samples_ = num_samples;
}

node_set_t monte_carlo_minimizer::draw_sample(const node_set_t &ground_set)
{
    node_set_t sample;

    for (const node_t &n : ground_set.array())
    {
        if (rand_(gen_))
        {
            sample.add(n);
        }
    }
    return sample;
}

}