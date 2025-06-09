cmake_minimum_required(VERSION 3.18.0)
project(programming_languages_2 VERSION 0.3.0)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(CTest)
add_subdirectory(googletest)

include(helpers.cmake)

add_lab_exercises(Warehouse)
