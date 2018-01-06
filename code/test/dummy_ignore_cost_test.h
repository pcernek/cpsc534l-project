//
// Created by paul on 05/01/18.
//

#ifndef HEADHUNTER_DUMMY_IGNORE_COST_TEST_H
#define HEADHUNTER_DUMMY_IGNORE_COST_TEST_H

#include <gtest/gtest.h>
#include <io/instance_loader.h>

namespace hh
{

class dummy_ignore_cost_test : public ::testing::Test
{

public:
    dummy_ignore_cost_test() : tf_(instance_loader::load_instance_from_file("../res/dummy_ignore_cost.tf")) {

    }

protected:
    const instance tf_;
};

}

#endif //HEADHUNTER_DUMMY_IGNORE_COST_TEST_H
