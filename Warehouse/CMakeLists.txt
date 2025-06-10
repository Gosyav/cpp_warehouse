cmake_minimum_required(VERSION 3.10)
project(Warehouse)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable warnings
add_compile_options(-Wall -Wextra -Wpedantic)

# Collect header files
file(GLOB_RECURSE HEADER_FILES
    "include/*.hpp"
    "include/*.h"
)

# Collect source files
file(GLOB_RECURSE SOURCE_FILES
    "src/*.cpp"
)

# Create the main library
add_library(Warehouse STATIC ${SOURCE_FILES} ${HEADER_FILES})

# Set include directories for library
target_include_directories(Warehouse PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Interfaces
    ${CMAKE_CURRENT_SOURCE_DIR}/include/MagicEnum
)

# Configure tests
enable_testing()
include(GoogleTest)

# Collect test files
file(GLOB_RECURSE TEST_FILES
    "test/*.cpp"
)

# Configure each test
foreach(TEST_FILE ${TEST_FILES})
    get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)
    add_executable(${TEST_NAME} ${TEST_FILE})
    target_link_libraries(${TEST_NAME} PRIVATE Warehouse gtest_main)
    target_include_directories(${TEST_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/test
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/include/MagicEnum
    )
    target_compile_definitions(${TEST_NAME} PRIVATE TESTING)
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach()