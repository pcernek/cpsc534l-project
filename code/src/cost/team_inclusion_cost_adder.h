//
// Created by paul on 03/01/18.
//

#ifndef HEADHUNTER_NODE_COST_ADDER_H
#define HEADHUNTER_NODE_COST_ADDER_H

#include <network/graph.h>
#include "cost_calculator.h"

namespace hh
{

class team_inclusion_cost_adder : public cost_calculator
{
public:
    
    value_t calc_cost(const node_array_t &nodes) const override;

};

}

#endif //HEADHUNTER_NODE_COST_ADDER_H
