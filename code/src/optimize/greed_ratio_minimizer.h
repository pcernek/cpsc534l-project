//
// Created by paul on 04/01/18.
//

#ifndef HEADHUNTER_RS_MINIMIZER_H
#define HEADHUNTER_RS_MINIMIZER_H

#include "minimizer.h"
#include "constraint.h"
#include "greedy_minimizer.h"

namespace hh
{

/**
 * Implementation of the GREED RATIO algorithm in Bai et al. 2016, for minimizing
 * the ratio of a modular function and a submodular function.
 */
class greed_ratio_minimizer : public minimizer
{
public:

    explicit greed_ratio_minimizer(constraint_t c, set_function_t submodular_denominator);
    std::pair<value_t, node_array_t> minimize(set_function_t f, const node_array_t &ground_set) override;

protected:

    hh::node_array_t remove_useless_candidate_nodes(const node_array_t &candidates,
                                                    const node_array_t &cur_solution,
                                                    const set_function_t f) const;

private:

    node_t greedy_choose_node(const node_array_t &candidate_nodes,
                              const node_array_t &cur_solution,
                              set_function_t f) const;
    const constraint_t c_;

    set_function_t submodular_denominator_;

};

}

#endif //HEADHUNTER_RS_MINIMIZER_H