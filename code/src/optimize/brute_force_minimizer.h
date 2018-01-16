//
// Created by paul on 07/01/18.
//

#ifndef HEADHUNTER_BRUTE_FORCE_MINIMIZER_H
#define HEADHUNTER_BRUTE_FORCE_MINIMIZER_H

#include "minimizer.h"

namespace hh
{

class brute_force_minimizer : public minimizer
{
public:
    std::pair<value_t, node_set_t> minimize(set_function_t f, const node_set_t &candidates) override;

private:
    node_set_t generate_subset(const node_set_t &candidates, size_t subset_id) const;
};

}

#endif //HEADHUNTER_BRUTE_FORCE_MINIMIZER_H
