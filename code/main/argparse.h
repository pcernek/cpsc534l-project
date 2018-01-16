//
// Created by paul on 07/01/18.
//

#ifndef HEADHUNTER_ARGPARSE_H
#define HEADHUNTER_ARGPARSE_H

#include <string>

#include "messages.h"
#include "typedefs.h"

namespace hh
{

enum algorithm
{
    GREEDY_RS,
    MC_RS,
    MC_MC,
    GREEDY_MC,
    BRUTE_FORCE,
    MAX_ALGO
};

struct cmdline_params
{
    bool algo_present = false;
    algorithm algo = MAX_ALGO;

    bool instance_file_name_present = false;
    std::string instance_file_name;

    bool override_budget = false;
    double budget = -1;

    bool override_candidates = false;
    std::vector<hh::id_t> candidates;

    bool override_ground_set = false;
    std::vector<hh::id_t> ground_set;
};

algorithm parse_algorithm(const std::string &algo_name)
{
    std::vector<std::string> valid_algos = {
            "greedy_rs",
            "mc_rs",
            "mc_mc",
            "greedy_mc",
            "brute_force"
    };
    for (auto i = 0; i < MAX_ALGO; i++)
    {
        if (algo_name == valid_algos[i])
        {
            INFO("Running " << algo_name);
            return static_cast<algorithm>(i);
        }
    }

    ERROR("Invalid algorithm specified: " << algo_name);
}

bool is_option_flag(const std::string &s)
{
    if (s.size() < 2)
    {
        return false;
    }
    return s[0] == '-' && s[1] == '-';
}

/**
 * When this method returns, the value of cur_arg_idx is guaranteed to be the index of the
 * next argument flag
 *
 * cur_arg_idx should point to the first node in the argument list
 */
std::vector<hh::id_t> parse_node_list(int argc, char**argv, int &cur_arg_idx)
{
    std::vector<hh::id_t> node_list;

    for (; cur_arg_idx < argc; cur_arg_idx++) {
        std::string next_arg(argv[cur_arg_idx]);
        if (is_option_flag(next_arg))
        {
            break;
        }
        auto candidate_id = static_cast<hh::id_t>(std::stoi(argv[cur_arg_idx]));
        node_list.push_back(candidate_id);
    }

    return node_list;
}

void check_required_args(const cmdline_params &p)
{
    if (!p.algo_present)
    {
        ERROR("Argument --algo required!");
    }
    if (!p.instance_file_name_present)
    {
        ERROR("Argument --instance-file required!")
    }
}

cmdline_params parse_cmdline_args(int argc, char **argv)
{
    cmdline_params p;

    for (int i = 1; i < argc; i++)
    {
        std::string cur_arg(argv[i]);
        if (is_option_flag(cur_arg))
        {
            if (cur_arg == "--algorithm")
            {
                p.algo = parse_algorithm(argv[++i]);
                p.algo_present = true;
            }
            else if (cur_arg == "--instance-file")
            {
                p.instance_file_name = {argv[++i]};
                p.instance_file_name_present = true;
            }
            else if (cur_arg == "--budget")
            {
                p.override_budget = true;
                p.budget = std::stod(std::string(argv[++i]));
                INFO("Detected an overriding budget: " << p.budget)
            }
            else if (cur_arg == "--ground-set")
            {
                p.override_ground_set = true;
                p.ground_set = parse_node_list(argc, argv, ++i);
                i--; // since i now points to the next argument flag,
                // but will get incremented again at the bottom of this loop

                INFO("Loaded " << p.ground_set.size() << " ground_set nodes from command line.");
            }
            else if (cur_arg == "--candidates")
            {
                p.override_candidates = true;
                p.candidates = parse_node_list(argc, argv, ++i);
                i--; // since i now points to the next argument flag,
                // but will get incremented again at the bottom of this loop

                INFO("Loaded " << p.candidates.size() << " candidates from command line. Overriding those in input file.");
            }
            else
            {
                ERROR("Unrecognized argument flag: " << cur_arg);
            }
        }
        else
        {
            ERROR("Bad arguments");
        }

    }
    check_required_args(p);

    return p;
}

}

#endif //HEADHUNTER_ARGPARSE_H
