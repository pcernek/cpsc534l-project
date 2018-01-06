//
// Created by paul on 05/01/18.
//

#include <gtest/gtest.h>
#include <instance.h>
#include <io/instance_loader.h>
#include "instance_loader_test.h"

using namespace hh;

TEST(instance_loader_test, basic)
{
    std::string fname = "../res/dummy_ignore_cost.tf";
    const instance tf = instance_loader::load_instance_from_file(fname);

    EXPECT_EQ(2, tf.budget);
    EXPECT_EQ(3, tf.candidates.size());
    EXPECT_EQ(4, tf.G->nodes.size());
}