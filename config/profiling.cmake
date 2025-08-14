if(ENABLE_PROFILING)
  if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    find_program(GPROF2DOT_EXECUTABLE gprof2dot)
    find_program(DOT_EXECUTABLE dot)

    if(GPROF2DOT_EXECUTABLE AND DOT_EXECUTABLE)
      message("gprof2dot and Graphviz found, enabling graphical profiling report")

      add_custom_command(
        OUTPUT ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/gmon.out
        COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} ./QtSecureTemplate
        WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
        DEPENDS ${PROJECT_NAME}
        COMMENT "Running application for gprof profiling"
        VERBATIM
      )

      add_custom_target(run_profiling
        COMMAND ${CMAKE_COMMAND} -E make_directory ${PROJECT_ROOT_DIR}/reports
        COMMAND gprof ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/QtSecureTemplate ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/gmon.out -n ${CMAKE_PROJECT_ROOT}/src/main.cpp | ${GPROF2DOT_EXECUTABLE} | ${DOT_EXECUTABLE} -Tpng -o ${PROJECT_ROOT_DIR}/reports/profile.png
        DEPENDS ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/gmon.out
        COMMENT "Generating graphical gprof profiling report"
      )
    else()
      message(WARNING "gprof2dot or Graphviz not found, skipping graphical profiling report")
      message(STATUS "Please install gprof2dot (pip install gprof2dot) and Graphviz (https://graphviz.org/download/)")

       add_custom_target(run_profiling
        COMMAND ${CMAKE_COMMAND} -E make_directory ${PROJECT_ROOT_DIR}/reports
        COMMAND gprof ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/QtSecureTemplate ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/gmon.out > ${PROJECT_ROOT_DIR}/reports/profile.txt
        DEPENDS ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/gmon.out 
        COMMENT "Generating gprof profiling report"
      )
    endif()

  elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
   add_custom_target(run_profiling
      COMMAND ${CMAKE_COMMAND} -E make_directory ${PROJECT_ROOT_DIR}/reports
      COMMAND perf record -o ${PROJECT_ROOT_DIR}/reports/perf.data ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/QtSecureTemplate
      COMMAND perf report -i ${PROJECT_ROOT_DIR}/reports/perf.data > ${PROJECT_ROOT_DIR}/reports/profile.txt
      DEPENDS ${PROJECT_NAME}
      COMMENT "Running perf profiling"
    )
  elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    message(STATUS "Please use Visual Studio Profiler to profile the application")
  else()
    message(WARNING "Profiling is not supported for this compiler")
  endif()
endif()