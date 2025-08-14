macro(add_recursive retVal dir ext1 excl)
  file(GLOB_RECURSE _tmp_list ${dir}/${ext1})
  set(${retVal} "")
  foreach(f ${_tmp_list})
    if(NOT f MATCHES ${excl})
      list(APPEND ${retVal} ${f})
    endif()
  endforeach()
endmacro(add_recursive)

find_program(CLANG_TIDY_EXECUTABLE NAMES clang-tidy)
find_program(CPPCHECK_EXECUTABLE NAMES cppcheck)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

function(add_static_analyzers_target)
  add_recursive(ALL_SOURCES_FILES_CXX "." "*.[ch]pp" "/Build/|/tests/|.*moc")
  add_recursive(ALL_SOURCES_FILES_C "." "*.[ch]" "/Build/|/tests/|.*moc")

  # Clang-Tidy
  if(CLANG_TIDY_EXECUTABLE)
    message("Clang-Tidy found: ${CLANG_TIDY_EXECUTABLE}")
    set(CLANG_TIDY_COMMAND
      ${CLANG_TIDY_EXECUTABLE}
      -format-style=file
      -header-filter=.*
      -p ${CMAKE_BINARY_DIR}
      ${ALL_SOURCES_FILES_C}
      ${ALL_SOURCES_FILES_CXX}
    )
  else()
    message(WARNING "Clang-Tidy not found. Skipping Clang-Tidy analysis.")
  endif()

  # Cppcheck
  if(CPPCHECK_EXECUTABLE)
    message("Cppcheck found: ${CPPCHECK_EXECUTABLE}")
    set(CPPCHECK_COMMAND
      ${CPPCHECK_EXECUTABLE}
      --enable=all
      --xml
      --output-file=${PROJECT_ROOT_DIR}/reports/cppcheck_report.xml
      ${ALL_SOURCES_FILES_C}
      ${ALL_SOURCES_FILES_CXX}
    )
  else()
    message(WARNING "Cppcheck not found. Skipping Cppcheck analysis.")
  endif()

  add_custom_target(run_static_analyzers
    COMMAND ${CMAKE_COMMAND} -E make_directory ${PROJECT_ROOT_DIR}/reports
    COMMAND ${CLANG_TIDY_COMMAND} > ${PROJECT_ROOT_DIR}/reports/clang_tidy_report.txt
    COMMAND ${CPPCHECK_COMMAND}
    DEPENDS ${PROJECT_NAME}
    COMMENT "Running static analyzers"
  )
endfunction()