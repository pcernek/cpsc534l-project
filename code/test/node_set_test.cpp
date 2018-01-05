//
// Created by paul on 05/01/18.
//

#include <gtest/gtest.h>
#include <network/node.h>

using namespace hh;

TEST(node_set_test, node_equality)
{
    hh::id_t common_id = 99;
    node_t n1 = std::make_shared<node>(node{common_id});
    node_t n2 = std::make_shared<node>(node{common_id});

    EXPECT_TRUE(hh::node_t_equality()(n1, n2));
}

TEST(node_set_test, node_inequality)
{
    node_t n1 = std::make_shared<node>(node{42});
    node_t n2 = std::make_shared<node>(node{43});

    EXPECT_FALSE(hh::node_t_equality()(n1, n2));
}

TEST(node_set_test, contains)
{
    node_set nodes;
    hh::id_t common_id = 99;
    node_t n1 = std::make_shared<node>(node{common_id});
    node_t n2 = std::make_shared<node>(node{common_id});

    nodes.add(n1);

    EXPECT_TRUE(nodes.contains(n1));
    EXPECT_TRUE(nodes.contains(n2));
}

TEST(node_set_test, does_not_contain)
{
    node_set nodes;
    node_t n1 = std::make_shared<node>(node{42});
    node_t n2 = std::make_shared<node>(node{43});

    nodes.add(n1);

    EXPECT_TRUE(nodes.contains(n1));
    EXPECT_FALSE(nodes.contains(n2));
}

TEST(node_set_test, add_twice)
{
    node_set nodes;
    hh::id_t common_id = 99;
    node_t n1 = std::make_shared<node>(node{common_id});
    node_t n2 = std::make_shared<node>(node{common_id});

    nodes.add(n1);
    nodes.add(n2);

    EXPECT_EQ(1, nodes.size());
}

TEST(node_set_test, remove)
{
    node_set nodes;
    hh::id_t common_id = 99;
    node_t n1 = std::make_shared<node>(node{common_id});

    nodes.add(n1);

    EXPECT_TRUE(nodes.contains(n1));
    EXPECT_EQ(1, nodes.size());

    nodes.remove(n1);

    EXPECT_FALSE(nodes.contains(n1));
    EXPECT_EQ(0, nodes.size());
}

TEST(node_set_test, graceful_remove)
{
    node_set nodes;
    node_t n1 = std::make_shared<node>(node{42});
    node_t n2 = std::make_shared<node>(node{43});

    nodes.add(n1);
    nodes.remove(n2);

    EXPECT_TRUE(nodes.contains(n1));
    EXPECT_FALSE(nodes.contains(n2));
    EXPECT_EQ(1, nodes.size());
}

TEST(node_set_test, get_array)
{
    node_set nodes;
    node_t n1 = std::make_shared<node>(node{42});
    node_t n2 = std::make_shared<node>(node{43});

    nodes.add(n1);
    nodes.add(n2);

    auto narray = nodes.array();
    EXPECT_EQ(n1, narray[0]);
    EXPECT_EQ(n2, narray[1]);
}

TEST(node_set_test, array_map_synced)
{
    node_set nodes;
    node_t n1 = std::make_shared<node>(node{42});

    nodes.add(n1);

    auto narray = nodes.array();
    EXPECT_EQ(1, narray.size());
    EXPECT_EQ(n1, narray[0]);

    nodes.remove(n1);

    auto narray2 = nodes.array();
    EXPECT_EQ(0, narray2.size());
}

TEST(node_set_test, memory_safety)
{
    node_set nodes;
    node_t n1 = std::make_shared<node>(node{42});
    node_t n2 = std::make_shared<node>(node{43});
    node_t n3 = std::make_shared<node>(node{44});

    nodes.add(n1);
    nodes.add(n2);

    nodes.remove(n1);
    // Make sure this doesn't generate a segfault
    nodes.add(n3);
}