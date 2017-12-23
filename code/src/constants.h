//
// Created by paul on 22/12/17.
//

#ifndef HEADHUNTER_CONSTANTS_H
#define HEADHUNTER_CONSTANTS_H

#include <limits>

#include "typedefs.h"

namespace hh
{

/**
 * ASSUMPTION: any well-defined value is always non-negative
 */
const value_t MIN_VALUE = -1;
const value_t MAX_VALUE = std::numeric_limits<int>::infinity();

const double NEGLIGIBLE_FRACTION = 0.001;

}

#endif //HEADHUNTER_CONSTANTS_H
