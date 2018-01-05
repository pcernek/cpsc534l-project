# Declare test directory
set(TEST_DIR ${CMAKE_SOURCE_DIR}/test)

# Add directory to header search path
include_directories(${TEST_DIR})

# Get all code files in test directory
file(GLOB_RECURSE TEST_FILES ${TEST_DIR}/*.cpp ${TEST_DIR}/*.h)

# Create target for automated unit tests
add_executable(run_tests
        ${TEST_FILES})

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
                 ${CMAKE_BINARY_DIR}/googletest-build)

#add_subdirectory(${TEST_DIR}/lib/googletest/googlemock gmock)
#include_directories(gmock STATIC ${TEST_DIR}/lib/googletest/googlemock/include )

target_link_libraries(run_tests gtest gmock)

# Link thermo lib to test
target_link_libraries(run_tests ${SRC_LIB})
