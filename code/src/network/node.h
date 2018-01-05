//
// Created by paul on 21/12/17.
//

#ifndef HEADHUNTER_NODE_H
#define HEADHUNTER_NODE_H

#include <vector>
#include <algorithm>

#include <typedefs.h>

#include "skill.h"

namespace hh
{

const value_t DEFAULT_HIRING_COST = 1;

const value_t DEFAULT_TEAM_INCLUSION_COST = 1;

struct node
{
    node() = delete;

    const id_t id;

    const std::vector<skill_t> skills;

    const value_t hiring_cost;

    const value_t team_inclusion_cost;

};

typedef std::shared_ptr<const node> node_t;

struct node_t_hasher
{
    size_t operator()(const hh::node_t& n) const
    {
        return std::hash<hh::id_t>()(n->id);
    }
};

struct node_t_equality
{
    bool operator()(const node_t &n1, const node_t &n2) const
    {
        if (n1 == n2)
        {
            return true;
        }
        if (n1 == nullptr || n2 == nullptr)
        {
            return false;
        }
        return n1->id == n2->id;
    }
};

class node_set
{
public:
    node_set() = default;

    explicit node_set(const std::vector<node_t> &nodes)
    {
        for (const auto &n : nodes)
        {
            add(n);
        }
    }

    const std::vector<node_t> array() const
    {
        return array_;
    }

    bool contains(const node_t &n) const
    {
        return set_.count(n) > 0;
    }

    void add(const node_t &n)
    {
        if (contains(n))
        {
            return;
        }

        array_.push_back(n);
        set_.insert(n);
    }

    void add_all(const node_set &other)
    {
        for (const node_t &n : other.array())
        {
            add(n);
        }
    }

    void remove(const node_t &n)
    {
        if (!contains(n))
        {
            return;
        }
        array_.erase(std::remove(array_.begin(), array_.end(), n));
        set_.erase(n);
    }

    size_t size() const
    {
        return array_.size();
    }

    bool empty() const
    {
        return size() == 0;
    }

private:
    std::vector<node_t> array_;
    std::unordered_set<node_t, node_t_hasher, node_t_equality> set_;
};

typedef std::vector<node_t> real_node_array;
typedef node_set node_array_t;

}

#endif //HEADHUNTER_NODE_H
