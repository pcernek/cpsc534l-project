//
// Created by paul on 21/12/17.
//

#include "instance_loader.h"

#include <fstream>
#include <sstream>
#include <messages.h>
#include <task/constant_task_distribution.h>

using namespace hh;

instance instance_loader::load_instance_from_file(const std::string &filename)
{
    std::ifstream in_file(filename);
    if (!in_file.is_open())
    {
        WARN("Unable to open file " << filename);
        throw std::exception();
    }

    size_t num_nodes, num_skills, num_candidates, k;

    stream_next_line(in_file) >> num_nodes;
    stream_next_line(in_file) >> num_skills;

    // TODO: (Testing) verify that all this gets parsed and loaded properly.
    const auto all_skills = generate_all_skills(num_skills);
    const auto edge_weights = load_edge_costs(in_file, num_nodes);
    const auto all_nodes = load_nodes(in_file, num_nodes, all_skills);

    const auto g = std::make_shared<graph>(graph{edge_weights, all_nodes});

    const auto td = load_distribution(in_file, num_skills);

    stream_next_line(in_file) >> num_candidates;
    DEBUG("Num candidates: " << num_candidates);
    const auto candidates = load_candidates(in_file, num_candidates, all_nodes);

    stream_next_line(in_file) >> k;

    return instance{g, td, candidates, k};
}

std::istringstream instance_loader::stream_next_line(std::ifstream &in_file)
{
    std::string line;
    do {
        std::getline(in_file, line);
        DEBUG(line);
    }
    while (line.empty() || line[0] == '#' || line[0] == '\n');

//    DEBUG("Returning line: " << line);

    return std::istringstream(line);
}

edge_weights_t instance_loader::load_edge_costs(std::ifstream &in_file,
                                                size_t num_nodes)
{
    edge_weights_t matrix(num_nodes);
    edge_weight_t w;

    for (auto &i : matrix) {
        i.resize(num_nodes);
        std::istringstream iss = stream_next_line(in_file);
        for (double &j : i) {
            iss >> w;
            j = w;
        }
    }

    return matrix;
}

node_array_t instance_loader::load_nodes(std::ifstream &in_file,
                                         size_t num_nodes, const std::vector<skill_t> &all_skills)
{
    node_array_t all_nodes(num_nodes);

    for (id_t i = 0; i < all_nodes.size(); i++)
    {
        size_t num_node_skills;
        stream_next_line(in_file) >> num_node_skills;
        std::istringstream iss = stream_next_line(in_file);

        id_t cur_skill_id;
        std::vector<skill_t> cur_skills(num_node_skills);
        for (auto &cur_skill : cur_skills) {
            iss >> cur_skill_id;
            if (cur_skill_id > all_skills.size())
            {
                WARN("Encountered skill id greater than number of skills!");
                continue;
            }
            cur_skill = all_skills[cur_skill_id];
        }

        all_nodes[i] = std::make_shared<node>(node{i, cur_skills});
    }

    return all_nodes;
}

task_distribution_t instance_loader::load_distribution(std::ifstream &in_file, size_t num_skills)
{
    stream_next_line(in_file);

    // TODO: Currently, this does not actually read in a distribution. Needs to be improved.
    std::vector<skill_t> dummy_skills;
//    dummy_skills.push_back(std::make_shared<skill>(skill{num_skills - 1}));
    dummy_skills.push_back(skill_t{num_skills - 1});

    task_t t = std::unordered_set<skill_t>(dummy_skills.begin(), dummy_skills.end());
    task_distribution_t td = std::make_shared<constant_task_distribution>(t);

    return td;
}

node_array_t instance_loader::load_candidates(std::ifstream &in_file,
                                              size_t num_candidates,
                                              const node_array_t &all_nodes)
{
    node_array_t candidates(num_candidates);

    std::istringstream iss = stream_next_line(in_file);

    id_t candidate_id;
    for (auto &candidate : candidates) {
        iss >> candidate_id;
        if (candidate_id > all_nodes.size())
        {
            WARN("Encountered candidate id greater than number of total nodes!");
            continue;
        }
        candidate = all_nodes[candidate_id];
    }

    return candidates;
}

std::vector<skill_t> instance_loader::generate_all_skills(size_t num_skills)
{
    std::vector<skill_t> all_skills(num_skills);

    for (id_t i = 0; i < all_skills.size(); i++)
    {
//        all_skills[i] = std::make_shared<skill>(skill{i});
        all_skills[i] = skill_t{i};
    }

    return all_skills;
}
