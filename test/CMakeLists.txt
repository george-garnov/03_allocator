cmake_minimum_required(VERSION 3.2)

if (DEFINED ENV{TRAVIS_BUILD_NUMBER})
    project(test VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    project(test VERSION 0.0.1)
endif()

add_executable(${PROJECT_NAME} test.cpp)

set_target_properties(
        ${PROJECT_NAME} PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS -Wpedantic -Wall -Wextra
)

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})

add_executable(version_test tests.cpp)
target_link_libraries(version_test
  ${GTEST_BOTH_LIBRARIES}
  version_lib
  pthread
)

set_target_properties(ip_filter version_test PROPERTIES
  CXX_STANDARD 14
  CXX_STANDARD_REQUIRED ON
  COMPILE_OPTIONS -Wpedantic -Wall -Wextra
)

set_target_properties(version_test PROPERTIES
  INCLUDE_DIRECTORIES ${GTEST_INCLUDE_DIRS}
)
