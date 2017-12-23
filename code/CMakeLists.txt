cmake_minimum_required(VERSION 3.5)
set(PROBLEM_NAME headhunter)
project(${PROBLEM_NAME})

set(CMAKE_CXX_STANDARD 11)

include_directories(src)

add_executable(${PROBLEM_NAME} main.cpp src/network/node.h src/network/skill.h src/io/instance_loader.cpp src/io/instance_loader.h src/network/graph.cpp src/network/graph.h src/instance.h src/task/task_distribution.h src/solver/greed_ratio_top_k_solver.cpp src/solver/greed_ratio_top_k_solver.h src/typedefs.h src/solver/top_k_solver.h src/cost/cost_calculator.h src/utility/utility_calculator.h src/constants.h src/messages.h src/solver/bottom_k_solver.h src/cost/edge_weight_summer.cpp src/cost/edge_weight_summer.h src/task/independent_task_distribution.cpp src/task/independent_task_distribution.h src/utility/expected_coverage_calculator.cpp src/utility/expected_coverage_calculator.h src/task/constant_task_distribution.cpp src/task/constant_task_distribution.h)
