include(CMakeParseArguments)

if (NOT COMMAND project_dependency)
  function(project_dependency DEP)
    get_property(loaded GLOBAL PROPERTY ${DEP}_LOADED)
    if (NOT loaded)
      cmake_parse_arguments(DL_ARGS "" "" "" ${ARGN})
      set(DL_ARGS_BUILD_DIR "${CMAKE_BINARY_DIR}/vendor/${DEP}")
      set(DL_ARGS_SOURCE_DIR "${CMAKE_SOURCE_DIR}/vendor/${DEP}")
      file(WRITE "${DL_ARGS_BUILD_DIR}/CMakeLists.txt"
        "cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)\n"
        "project(vendor-${DEP} NONE)\n"
        "include(ExternalProject)\n"
        "ExternalProject_Add(vendor-${DEP}\n"
        "${DL_ARGS_UNPARSED_ARGUMENTS}\nSOURCE_DIR \"${DL_ARGS_SOURCE_DIR}\"\n"
        "CONFIGURE_COMMAND \"\"\nBUILD_COMMAND \"\"\nINSTALL_COMMAND \"\"\n"
        "TEST_COMMAND \"\"\nUPDATE_COMMAND \"\"\nPATCH_COMMAND \"\")"
      )
      execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}"
        RESULT_VARIABLE result OUTPUT_QUIET
        WORKING_DIRECTORY "${DL_ARGS_BUILD_DIR}"
      )
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
      set_property(GLOBAL PROPERTY ${DEP}_LOADED TRUE)
    endif ()
  endfunction()
endif ()
