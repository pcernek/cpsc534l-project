//
// Created by paul on 04/01/18.
//

#ifndef HEADHUNTER_UNCONSTRAINED_MC_MINIMIZER_H
#define HEADHUNTER_UNCONSTRAINED_MC_MINIMIZER_H

#include <network/node.h>

#include <utility>
#include <constants.h>
#include <random>
#include "minimizer.h"
#include "constraint.h"

namespace hh
{

class monte_carlo_minimizer : public minimizer
{

public:

    static const size_t DEFAULT_NUM_SAMPLES = 1000 * 1000;

    explicit monte_carlo_minimizer(constraint_t c, size_t num_samples = DEFAULT_NUM_SAMPLES);

    std::pair<value_t, node_array_t> minimize(set_function_t f, const node_array_t &ground_set) override;

    void set_num_samples(size_t num_samples);

private:
    size_t num_samples_;
    std::random_device rd_; // no idea what this does, but it's required by the random bit generator
    std::mt19937 gen_; // a random bit generator required by the bernoulli distribution
    std::bernoulli_distribution rand_; // bernoulli distribution used to randomly sample nodes

    const constraint_t constraint_;

    node_array_t draw_sample(const node_array_t &ground_set);
};

}

#endif //HEADHUNTER_UNCONSTRAINED_MC_MINIMIZER_H
