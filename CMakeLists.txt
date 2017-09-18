cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
cmake_policy(SET CMP0054 OLD)
cmake_policy(SET CMP0045 OLD)

include(CMakeParseArguments)
if (NOT COMMAND project_dependency)
  function(project_dependency DEP)
    cmake_parse_arguments(DL_ARGS "" "" "" ${ARGN})
    set(DL_ARGS_BUILD_DIR "${CMAKE_BINARY_DIR}/vendor/${DEP}")
    set(DL_ARGS_SOURCE_DIR "${CMAKE_SOURCE_DIR}/vendor/${DEP}")
    file(WRITE "${DL_ARGS_BUILD_DIR}/CMakeLists.txt"
      "cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)\n"
      "project(vendor-${DEP} NONE)\n"
      "include(ExternalProject)\n"
      "ExternalProject_Add(vendor-${DEP}\n"
      "${DL_ARGS_UNPARSED_ARGUMENTS}\nSOURCE_DIR \"${DL_ARGS_SOURCE_DIR}\"\n"
      "CONFIGURE_COMMAND \"\"\nBUILD_COMMAND \"\"\nINSTALL_COMMAND \"\"\nTEST_COMMAND \"\")")
    execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}"
      -D "CMAKE_MAKE_PROGRAM:FILE=${CMAKE_MAKE_PROGRAM}" .
      RESULT_VARIABLE result OUTPUT_QUIET
      WORKING_DIRECTORY "${DL_ARGS_BUILD_DIR}")
    if (result)
      message(FATAL_ERROR "Config step for ${DEP} failed: ${result}")
    endif ()
    execute_process(COMMAND ${CMAKE_COMMAND} --build .
      RESULT_VARIABLE result OUTPUT_QUIET
      WORKING_DIRECTORY "${DL_ARGS_BUILD_DIR}")
    if (result)
      message(FATAL_ERROR "Build step for ${DEP} failed: ${result}")
    endif ()
    add_subdirectory(${DL_ARGS_SOURCE_DIR} ${DL_ARGS_BUILD_DIR}/build)
  endfunction()
endif ()

project(uds C)
project_dependency(uty GIT_REPOSITORY https://github.com/uael/uty.git)

set(uds_INC_DIR ${CMAKE_CURRENT_LIST_DIR}/include)
set(uds_TEST_DIR ${CMAKE_CURRENT_LIST_DIR}/test)

file(GLOB_RECURSE uds_HDRS ${uds_HDRS} ${uds_INC_DIR}/uds/*.h)
set(uds_HDR ${uds_INC_DIR}/uds.h)

add_library(uds INTERFACE)
target_include_directories(uds INTERFACE ${uds_INC_DIR})
target_link_libraries(uds INTERFACE uty)

get_directory_property(uds_PARENT PARENT_DIRECTORY)
if (NOT ${uds_PARENT})
  set(uds_DEVEL TRUE)
elseif (NOT ${uds_DEVEL})
  set(uds_DEVEL FALSE)
endif ()
if (${uds_DEVEL} AND EXISTS ${uds_TEST_DIR})
  if (NOT uds_PARENT)
    enable_testing()
  endif ()

  file(GLOB uds_TEST_SRCS ${uds_TEST_SRCS} ${uds_TEST_DIR}/*.c)
  foreach (uds_TEST_SRC ${uds_TEST_SRCS})
    get_filename_component(uds_TEST_NAME ${uds_TEST_SRC} NAME_WE)
    add_executable(test_${uds_TEST_NAME} ${uds_TEST_SRC})
    add_dependencies(test_${uds_TEST_NAME} uds)
    target_link_libraries(test_${uds_TEST_NAME} uds)
    add_test(${uds_TEST_NAME} test_${uds_TEST_NAME})
  endforeach ()
endif ()

install(FILES ${uds_HDRS}
  DESTINATION include/uds)
install(FILES ${uds_HDR}
  DESTINATION include)