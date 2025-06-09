cmake_minimum_required(VERSION 3.18.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

add_compile_options(
  -Wall
  -Werror
  -Wextra
  -Wundef
  -Wunused
  -Weffc++
  -Wshadow
  -Wformat
  -Wcomment
  -Wpedantic
  -Wnarrowing
  -Wlogical-op
  -Wcast-align
  -Wreturn-type
  -Winvalid-pch
  -Wtrampolines
  -Wuseless-cast
  -Wunused-macros
  -Wunused-result
  -Wold-style-cast
  -Wredundant-decls
  -Wduplicated-cond
  -Wredundant-decls
  -Wunused-parameter
  -Wnon-virtual-dtor
  -Wdouble-promotion
  -Wformat-overflow=2
  -Woverloaded-virtual
  -Wmissing-attributes
  -Wduplicated-branches
  -Wimplicit-fallthrough
  -Wno-stringop-overflow
  -Wmissing-declarations
  -Wmissing-include-dirs
  -Wmisleading-indentation
  -Wmissing-format-attribute
  -Wconversion
  -Wsign-conversion
  -Wnull-dereference)

macro(add_lab_exercises LAB_NAME)
  if(EXISTS ${CMAKE_SOURCE_DIR}/${LAB_NAME})
    message(STATUS "Lab ${LAB_NAME} found.")
    add_subdirectory(${LAB_NAME})
  endif()
endmacro(add_lab_exercises)

macro(add_lab_targets)
  file(GLOB_RECURSE ${PROJECT_NAME}_HEADER_H CONFIGURE_DEPENDS include/**.h*)
  file(GLOB_RECURSE ${PROJECT_NAME}_SRC_CPP CONFIGURE_DEPENDS src/**.cpp)

  add_library(${PROJECT_NAME} ${${PROJECT_NAME}_HEADER_H}
                              ${${PROJECT_NAME}_SRC_CPP})
  target_include_directories(${PROJECT_NAME} PUBLIC include)

  if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
    add_executable(${PROJECT_NAME}_Example src/main.cpp)
    target_link_libraries(${PROJECT_NAME}_Example ${PROJECT_NAME})

    target_include_directories(${PROJECT_NAME}_Example PUBLIC include)
  endif()

  # add each test file as separate test executable
  file(GLOB_RECURSE ${PROJECT_NAME}_TEST_CPP CONFIGURE_DEPENDS test/**.cpp)
  file(GLOB_RECURSE ${PROJECT_NAME}_TEST_H CONFIGURE_DEPENDS test/**.h*)
  foreach(TEST_FILE ${${PROJECT_NAME}_TEST_CPP})
    get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)
    add_executable(${TEST_NAME} test/${TEST_NAME}.cpp ${${PROJECT_NAME}_TEST_H})
    target_include_directories(${TEST_NAME} PRIVATE test)
    target_link_libraries(${TEST_NAME} gtest_main ${PROJECT_NAME})
    set_target_properties(
      ${TEST_NAME}
      PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                 ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test/${PROJECT_NAME})
    add_test(
      NAME ${TEST_NAME}
      COMMAND ${TEST_NAME}
      WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test/${PROJECT_NAME})
    set_tests_properties(${TEST_NAME} PROPERTIES TIMEOUT 1)
  endforeach()
endmacro(add_lab_targets)

macro(add_lab_targets_separated)
  file(GLOB_RECURSE HEADER_FILES CONFIGURE_DEPENDS include/*.h*)

  foreach(HEADER_FILE ${HEADER_FILES})
    get_filename_component(BASE_NAME ${HEADER_FILE} NAME_WE)

    file(GLOB_RECURSE SRC_FILE src/${BASE_NAME}.c*)

    # Create a library
    if(SRC_FILE)
      add_library(${PROJECT_NAME}_${BASE_NAME} ${SRC_FILE} ${HEADER_FILE})
      target_include_directories(${PROJECT_NAME}_${BASE_NAME} PUBLIC include)
    else()
      add_library(${PROJECT_NAME}_${BASE_NAME} INTERFACE ${HEADER_FILE})
    endif()

    # Create test executable
    file(GLOB_RECURSE TEST_FILE test/Test${PROJECT_NAME}${BASE_NAME}.cpp)
    file(GLOB_RECURSE TEST_HELPERS_FILES test/*.h*)
    get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)
    add_executable(${TEST_NAME} ${TEST_FILE})
    target_include_directories(${TEST_NAME} PRIVATE test)
    target_include_directories(${TEST_NAME} PRIVATE include)
    target_link_libraries(${TEST_NAME} gtest_main ${PROJECT_NAME}_${BASE_NAME})
    set_target_properties(
      ${TEST_NAME}
      PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                 ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test/${PROJECT_NAME})
    add_test(
      NAME ${TEST_NAME}
      COMMAND ${TEST_NAME}
      WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test/${PROJECT_NAME})
    set_tests_properties(${TEST_NAME} PROPERTIES TIMEOUT 1)
  endforeach()

  # Add the main executable if `main.cpp` exists
  if(EXISTS ${CMAKE_SOURCE_DIR}/src/main.cpp)
    add_executable(${PROJECT_NAME}_Example src/main.cpp)
    target_link_libraries(${PROJECT_NAME}_Example ${PROJECT_NAME})
    target_include_directories(${PROJECT_NAME}_Example PUBLIC include)
  endif()

endmacro(add_lab_targets_separated)
