//
// Created by paul on 04/01/18.
//

#ifndef HEADHUNTER_GREEDY_MINIMIZER_H
#define HEADHUNTER_GREEDY_MINIMIZER_H

#include "minimizer.h"
#include "constraint.h"

namespace hh
{

class greedy_minimizer : public minimizer
{
public:

    explicit greedy_minimizer(constraint_t c);

    std::pair<value_t, node_set_t> minimize(set_function_t f, const node_set_t &ground_set) override;
private:

    constraint_t c_;

    node_t greedy_choose_node(const node_set_t &candidate_nodes,
                              const node_set_t &cur_solution,
                              set_function_t f) const;

};

}

#endif //HEADHUNTER_GREEDY_MINIMIZER_H
