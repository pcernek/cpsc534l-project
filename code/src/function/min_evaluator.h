//
// Created by paul on 04/01/18.
//

#ifndef HEADHUNTER_MIN_EXPECTED_VALUE_H
#define HEADHUNTER_MIN_EXPECTED_VALUE_H

#include <optimize/minimizer.h>
#include <instance.h>

#include <utility>
#include <optimize/greed_ratio_minimizer.h>
#include "set_function.h"

namespace hh
{

class min_evaluator : public set_function
{
public:
    min_evaluator(const node_array_t &ground_set, minimizer_t m, set_function_t f) :
            ground_set_(std::move(ground_set)), m_(std::move(m)), f_(std::move(f))

    {

    }

    value_t eval(const node_array_t &nodes) const override
    {
        node_array_t combined;
        combined.reserve(ground_set_.size() + nodes.size());
        combined.insert(combined.end(), ground_set_.begin(), ground_set_.end());
        combined.insert(combined.end(), nodes.begin(), nodes.end());

        auto tmp_result = m_->minimize(f_, combined);
        return tmp_result.first;
    }

private:
    const node_array_t ground_set_;
    minimizer_t m_;
    set_function_t f_;
};

}

#endif //HEADHUNTER_MIN_EXPECTED_VALUE_H
