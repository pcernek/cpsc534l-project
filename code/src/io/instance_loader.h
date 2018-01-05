//
// Created by paul on 21/12/17.
//

#ifndef HEADHUNTER_INSTANCE_LOADER_H
#define HEADHUNTER_INSTANCE_LOADER_H

#include <string>
#include <task/constant_task_distribution.h>
#include "instance.h"

namespace hh
{

/**
 * Exposes a static interface for loading a problem instance from file.
 */
class instance_loader
{

public:

    static instance load_instance_from_file(const std::string &filename);

private:
    static std::istringstream stream_next_line(std::ifstream &in_file);

    static edge_weights_t load_edge_costs(std::ifstream &in_file, size_t num_nodes);

    static node_set_t load_nodes(std::ifstream &in_file, size_t num_nodes, const std::vector<skill_t> &all_skills);

    static task_distribution_t load_constant_distribution(std::ifstream &in_file, size_t num_skills, double threshold=0.005);

    static node_set_t load_candidates(std::ifstream &in_file, size_t num_candidates, const node_set_t &all_nodes);

    static std::vector<skill_t> generate_all_skills(size_t num_skills);
};

}

#endif //HEADHUNTER_INSTANCE_LOADER_H
