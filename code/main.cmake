# Create target to for executable to run the main program
set(MAIN_EXEC run_${PROBLEM_NAME})

add_executable(${MAIN_EXEC} main.cpp)

target_link_libraries(${MAIN_EXEC} ${SRC_LIB})
