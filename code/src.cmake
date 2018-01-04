# Declare source directory
set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)

include_directories(${SOURCE_DIR})

# Add include directory to header search path
#set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
#include_directories(${INCLUDE_DIR})

# Get all code files in source directory
set(SOURCE_FILES
        src/network/node.h src/network/skill.h src/io/instance_loader.cpp src/io/instance_loader.h src/network/graph.cpp src/network/graph.h src/instance.h src/task/task_distribution.h src/solver/greed_ratio_top_k_solver.cpp src/solver/greed_ratio_top_k_solver.h src/typedefs.h src/solver/top_k_solver.h src/cost/cost_calculator.h src/utility/utility_calculator.h src/constants.h src/messages.h src/solver/bottom_k_solver.h src/cost/edge_weight_summer.cpp src/cost/edge_weight_summer.h src/task/independent_task_distribution.cpp src/task/independent_task_distribution.h src/utility/expected_coverage_calculator.cpp src/utility/expected_coverage_calculator.h src/task/constant_task_distribution.cpp src/task/constant_task_distribution.h src/solver/ratio_solver.h src/debug.h
        src/cost/team_inclusion_cost_adder.cpp src/cost/team_inclusion_cost_adder.h)

# Create target for library of main functionality
set(SRC_LIB ${PROBLEM_NAME})
add_library(${SRC_LIB} STATIC ${SOURCE_FILES})
