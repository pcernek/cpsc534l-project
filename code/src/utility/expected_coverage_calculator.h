//
// Created by paul on 22/12/17.
//

#ifndef HEADHUNTER_EXPECTED_COVERAGE_CALCULATOR_H
#define HEADHUNTER_EXPECTED_COVERAGE_CALCULATOR_H

#include <task/task_distribution.h>

#include <utility>
#include <network/node.h>
#include "utility_calculator.h"

namespace hh
{

class expected_coverage_calculator : public utility_calculator
{

public:
    explicit expected_coverage_calculator(std::shared_ptr<const task_distribution> dist) :
            distribution_(std::move(dist))
    {

    }

    value_t calc_utility(const node_set_t &nodes) const override ;

private:
    static double calc_coverage(const node_set_t &nodes, const task_t &t);
    static std::unordered_set<skill_t> aggregate_skillset(const node_set_t &nodes);
    static size_t calc_intersect_size(const std::unordered_set<skill_t> &set1,
                                      const std::unordered_set<skill_t> &set2);

    const std::shared_ptr<const task_distribution> distribution_;
};

}

#endif //HEADHUNTER_EXPECTED_COVERAGE_CALCULATOR_H
