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
 * ASSUMPTION: any well-defined value is always non-negative, so setting MIN_VALUE to a negative
 * number ensures that no well-defined value will ever be smaller than it
 */
const value_t MIN_VALUE = -1;

/**
 * Having this be finite rather than infinite enables us to do hacky things,
 * like returning a large but finite quotient when one would otherwise divide by zero.
 */
const value_t MAX_VALUE = std::numeric_limits<value_t>::max();

const double NEGLIGIBLE_FRACTION_FOR_MARGINAL_GAIN = 0.001;

}

#endif //HEADHUNTER_CONSTANTS_H
