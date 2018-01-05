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

    std::pair<value_t, node_array_t> minimize(set_function_t f, const node_array_t &ground_set) override;

protected:

    virtual hh::node_array_t remove_useless_candidate_nodes(const node_array_t &candidates, const node_array_t &cur_solution,
                                                                const set_function_t f) const;
private:

    constraint_t c_;

    std::pair<value_t, node_t> greedy_choose_node(const node_array_t &candidate_nodes,
                                                  const node_array_t &cur_solution,
                                                  set_function_t f) const;
};

}

#endif //HEADHUNTER_GREEDY_MINIMIZER_H
