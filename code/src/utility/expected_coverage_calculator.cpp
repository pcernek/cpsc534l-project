//
// Created by paul on 22/12/17.
//

#include <messages.h>
#include "expected_coverage_calculator.h"

using namespace hh;

double expected_coverage_calculator::calc_coverage(const node_set_t &nodes, const task_t &t)
{
    if (t.size() == 0)
    {
        return 1.0;
    }

    std::unordered_set<skill_t> skillset = aggregate_skillset(nodes);

    return static_cast<double>(calc_intersect_size(skillset, t)) / t.size();
}

std::unordered_set<skill_t> expected_coverage_calculator::aggregate_skillset(const node_set_t &nodes)
{
    std::unordered_set<skill_t> skillset{};
    for (const auto &n : nodes.array())
    {
        for (const auto &s : n->skills)
        {
            skillset.insert(s);
        }
    }

    return skillset;
}

size_t expected_coverage_calculator::calc_intersect_size(const std::unordered_set<skill_t> &set1,
                                                         const std::unordered_set<skill_t> &set2)
{
    size_t intersect_size = 0;
    for (const auto &s : set1)
    {
        if (set2.count(s) > 0)
        {
            intersect_size++;
        }
    }
    return intersect_size;
}

value_t expected_coverage_calculator::calc_utility(const node_set_t &nodes) const
{
    auto u = distribution_->calc_expectation_over_tasks([nodes](const task_t &t){
        auto cov = calc_coverage(nodes, t);
        return cov;
    });
    // We shift everything by 1 here to avoid ever having to return 0.
    // This doesn't change the submodularity, monotonicity, or non-negativity of this function,
    // and avoids troublesome divisions-by-zero elsewhere.
    // It comes only at the cost that if the ratio function is called on the empty set,
    // the result is 0 (rather than very large, which is screwy because it makes the empty set always optimal)
    return 1 + u;
}
