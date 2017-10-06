cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
cmake_policy(SET CMP0054 OLD)
cmake_policy(SET CMP0045 OLD)

if (NOT EXISTS ${CMAKE_CACHEFILE_DIR}/cmake)
  execute_process(
    COMMAND git clone https://github.com/uael/cmake-modules.git cmake
    RESULT_VARIABLE result OUTPUT_QUIET
    WORKING_DIRECTORY ${CMAKE_CACHEFILE_DIR}
  )
endif ()

set(CMAKE_MODULE_PATH "${CMAKE_CACHEFILE_DIR}/cmake")
include(ProjectDependency)

set(CMAKE_C_STANDARD 99)
set(BUILD_SHARED_LIBS OFF)

project(uds C)
project_dependency(uerr GIT_REPOSITORY https://github.com/uael/uerr.git)

set(uds_INC_DIR ${CMAKE_CURRENT_LIST_DIR}/include)
set(uds_SRC_DIR ${CMAKE_CURRENT_LIST_DIR}/src)
set(uds_TEST_DIR ${CMAKE_CURRENT_LIST_DIR}/test)

file(GLOB_RECURSE uds_SRCS ${uds_SRCS} ${uds_SRC_DIR}/*.c)
file(GLOB_RECURSE uds_HDRS ${uds_HDRS} ${uds_INC_DIR}/uds/*.h)
set(uds_HDR ${uds_INC_DIR}/uds.h)

add_library(uds ${uds_SRCS} ${uds_HDRS} ${uds_HDR})
target_include_directories(uds PUBLIC ${uds_INC_DIR})
target_link_libraries(uds PUBLIC uerr)

set(CMAKE_C_FLAGS "")
set(CMAKE_C_FLAGS_DEBUG "")
set(CMAKE_C_FLAGS_RELEASE "")

if (MSVC)
  target_compile_options(uds
    PUBLIC /MT$<$<CONFIG:Debug>:d> /Oy /Za /W3
    PUBLIC /D_CRT_SECURE_NO_WARNINGS
    PUBLIC /O$<$<CONFIG:Debug>:d>$<$<CONFIG:Release>:x>)
else ()
  target_compile_options(uds
    PUBLIC -Wall -Werror -Wextra -fomit-frame-pointer -ansi -pedantic -pedantic
    PUBLIC -Wno-missing-field-initializers
    PUBLIC -O$<$<CONFIG:Debug>:0 -g3>$<$<CONFIG:Release>:3>)
endif ()

get_directory_property(uds_PARENT PARENT_DIRECTORY)
if (NOT uds_PARENT)
  set(uds_DEVEL TRUE)
elseif (NOT uds_DEVEL)
  set(uds_DEVEL FALSE)
endif ()
if (uds_DEVEL AND EXISTS ${uds_TEST_DIR})
  project_dependency(cute GIT_REPOSITORY https://github.com/uael/cute.git)
  if (NOT uds_PARENT)
    enable_testing()
  endif ()

  file(GLOB uds_TEST_SRCS ${uds_TEST_SRCS} ${uds_TEST_DIR}/*.c)
  foreach (uds_TEST_SRC ${uds_TEST_SRCS})
    get_filename_component(uds_TEST_NAME ${uds_TEST_SRC} NAME_WE)
    add_executable(test_uds_${uds_TEST_NAME} ${uds_TEST_SRC})
    add_dependencies(test_uds_${uds_TEST_NAME} uds cute)
    target_link_libraries(test_uds_${uds_TEST_NAME} uds cute)
    add_test(${uds_TEST_NAME} test_uds_${uds_TEST_NAME})
  endforeach ()
endif ()

install(FILES ${uds_HDRS} DESTINATION include/uds)
install(FILES ${uds_HDR} DESTINATION include)