cmake_minimum_required(VERSION 3.5)
set(PROBLEM_NAME headhunter)
project(${PROBLEM_NAME})

set(CMAKE_CXX_STANDARD 11)

# Instructions for building a static library containing main functionality of program
include(src.cmake)

# Instructions for building main executables
include(main.cmake)

# Instructions for building tests
include(test.cmake)
