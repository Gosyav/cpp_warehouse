cmake_minimum_required(VERSION 3.18.0)
project(programming_languages_2 VERSION 0.3.0 LANGUAGES CXX)

# Set build type
set(CMAKE_BUILD_TYPE Debug)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable compile commands export for tools
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Enable testing
include(CTest)

# Add Google Test
add_subdirectory(googletest)

# Include helper functions
include(helpers.cmake)

# Add lab exercises
add_lab_exercises(Warehouse)
