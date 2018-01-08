# Create target to for executable to run the main program

set(PROGRAM_DIR main)

add_executable(run_whole_team_greed_ratio ${PROGRAM_DIR}/run_whole_team_greed_ratio.cpp)
target_link_libraries(run_whole_team_greed_ratio ${SRC_LIB})

add_executable(run_${PROBLEM_NAME} ${PROGRAM_DIR}/headhunter.cpp)
target_link_libraries(run_${PROBLEM_NAME} ${SRC_LIB})
