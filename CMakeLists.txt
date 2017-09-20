cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
cmake_policy(SET CMP0054 OLD)
cmake_policy(SET CMP0045 OLD)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
include(ProjectDependency)

project(uds C)
project_dependency(uerr GIT_REPOSITORY https://github.com/uael/uerr.git)

set(uds_INC_DIR ${CMAKE_CURRENT_LIST_DIR}/include)
set(uds_TEST_DIR ${CMAKE_CURRENT_LIST_DIR}/test)

file(GLOB_RECURSE uds_HDRS ${uds_HDRS} ${uds_INC_DIR}/uds/*.h)
set(uds_HDR ${uds_INC_DIR}/uds.h)

add_library(uds INTERFACE)
target_include_directories(uds INTERFACE ${uds_INC_DIR})
target_link_libraries(uds INTERFACE uerr)

get_directory_property(uds_PARENT PARENT_DIRECTORY)
if (NOT ${uds_PARENT})
  set(uds_DEVEL TRUE)
elseif (NOT ${uds_DEVEL})
  set(uds_DEVEL FALSE)
endif ()
if (${uds_DEVEL} AND EXISTS ${uds_TEST_DIR})
  project_dependency(cute GIT_REPOSITORY https://github.com/uael/cute.git)
  if (NOT uds_PARENT)
    enable_testing()
  endif ()

  file(GLOB uds_TEST_SRCS ${uds_TEST_SRCS} ${uds_TEST_DIR}/*.c)
  foreach (uds_TEST_SRC ${uds_TEST_SRCS})
    get_filename_component(uds_TEST_NAME ${uds_TEST_SRC} NAME_WE)
    add_executable(test_${uds_TEST_NAME} ${uds_TEST_SRC})
    add_dependencies(test_${uds_TEST_NAME} uds cute)
    target_link_libraries(test_${uds_TEST_NAME} uds cute)
    add_test(${uds_TEST_NAME} test_${uds_TEST_NAME})
  endforeach ()
endif ()

install(FILES ${uds_HDRS}
  DESTINATION include/uds)
install(FILES ${uds_HDR}
  DESTINATION include)