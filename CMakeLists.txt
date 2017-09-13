cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
cmake_policy(SET CMP0054 OLD)
cmake_policy(SET CMP0045 OLD)

project(uds C)
set(CMAKE_C_STANDARD 90)
set(${PROJECT_NAME}_VENDOR "uael")
set(${PROJECT_NAME}_CONTACT "github.com/uael/uds/issues")
set(${PROJECT_NAME}_SUMMARY
  "uael platform independent c Data Structures abstraction")
set(${PROJECT_NAME}_MAJOR 0)
set(${PROJECT_NAME}_MINOR 1)
set(${PROJECT_NAME}_PATCH 0)
set(${PROJECT_NAME}_README README.md)
set(${PROJECT_NAME}_LICENSE LICENSE)
set(${PROJECT_NAME}_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/include)
set(${PROJECT_NAME}_TEST_DIR ${CMAKE_CURRENT_LIST_DIR}/test)

if (EXISTS ${CMAKE_CURRENT_LIST_DIR}/vendor)
  file(GLOB ${PROJECT_NAME}_VENDORS ${${PROJECT_NAME}_VENDORS}
    ${CMAKE_CURRENT_LIST_DIR}/vendor/*/)
  foreach (VENDOR ${${PROJECT_NAME}_VENDORS})
    if (EXISTS ${VENDOR}/CMakeLists.txt AND NOT ${VENDOR} STREQUAL
      ${CMAKE_CURRENT_LIST_DIR})
      add_subdirectory(${VENDOR})
    endif ()
  endforeach ()
endif()

get_directory_property(${PROJECT_NAME}_PARENT PARENT_DIRECTORY)
if (NOT ${PROJECT_NAME}_PARENT)
  set(${PROJECT_NAME}_DEVEL TRUE)
endif ()

set(${PROJECT_NAME}_HEADERS)
set(${PROJECT_NAME}_SOURCES)

if (EXISTS ${${PROJECT_NAME}_INCLUDE_DIR})
  file(GLOB_RECURSE ${PROJECT_NAME}_HEADERS ${${PROJECT_NAME}_HEADERS}
    ${${PROJECT_NAME}_INCLUDE_DIR}/${PROJECT_NAME}/*.h)
  file(GLOB ${PROJECT_NAME}_MODULES ${${PROJECT_NAME}_MODULES}
    ${${PROJECT_NAME}_INCLUDE_DIR}/*/)
  foreach (MODULE ${${PROJECT_NAME}_MODULES})
    file(GLOB_RECURSE ${PROJECT_NAME}_HEADERS ${${PROJECT_NAME}_HEADERS}
      ${MODULE}/*.h)
  endforeach ()
endif ()

if (EXISTS ${${PROJECT_NAME}_INCLUDE_DIR}/${PROJECT_NAME}.h)
  set(${PROJECT_NAME}_HEADER ${${PROJECT_NAME}_INCLUDE_DIR}/${PROJECT_NAME}.h)
else ()
  set(${PROJECT_NAME}_HEADER)
endif ()

add_library(${PROJECT_NAME} INTERFACE)
target_link_libraries(${PROJECT_NAME} INTERFACE uty)

if (EXISTS ${${PROJECT_NAME}_INCLUDE_DIR})
  target_include_directories(${PROJECT_NAME} INTERFACE
    ${${PROJECT_NAME}_INCLUDE_DIR})
endif ()

if (${PROJECT_NAME}_DEVEL)
  if (EXISTS ${${PROJECT_NAME}_TEST_DIR})
    enable_testing()

    file(GLOB ctest_SOURCES ${ctest_SOURCES} ${${PROJECT_NAME}_TEST_DIR}/*.c)
    foreach (ctest_SRC ${ctest_SOURCES})
      get_filename_component(ctest_NAME ${ctest_SRC} NAME_WE)
      add_executable(test_${ctest_NAME} ${ctest_SRC})
      add_dependencies(test_${ctest_NAME} ${PROJECT_NAME})
      target_link_libraries(test_${ctest_NAME} ${PROJECT_NAME})
      add_test(${ctest_NAME} test_${ctest_NAME})
    endforeach ()
  endif ()
endif ()

install(TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION bin
  ARCHIVE DESTINATION lib
  PUBLIC_HEADER DESTINATION include/${PROJECT_NAME})
if (EXISTS ${${PROJECT_NAME}_INCLUDE_DIR}/${PROJECT_NAME}.h)
  install(FILES ${${PROJECT_NAME}_INCLUDE_DIR}/${PROJECT_NAME}.h
    DESTINATION include)
endif ()
