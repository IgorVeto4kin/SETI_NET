# Таргет покрытия кода с тестами
if(ENABLE_CODE_COVERAGE)
  add_custom_target(code_coverage
    COMMAND ${CMAKE_COMMAND} -E make_directory ${PROJECT_ROOT_DIR}/reports/coverage
    COMMAND ${CMAKE_COMMAND} -E chdir ${PROJECT_ROOT_DIR} ${CMAKE_COMMAND} -E remove -f reports/coverage/coverage.info
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target run_tests
    COMMAND lcov --capture --directory ${CMAKE_BINARY_DIR} --output-file ${PROJECT_ROOT_DIR}/reports/coverage/coverage.info
    COMMAND lcov --remove ${PROJECT_ROOT_DIR}/reports/coverage/coverage.info '/usr/*' '${PROJECT_ROOT_DIR}/Build/*_autogen/*' --output-file ${PROJECT_ROOT_DIR}/reports/coverage/coverage.info
    COMMAND genhtml ${PROJECT_ROOT_DIR}/reports/coverage/coverage.info --output-directory ${PROJECT_ROOT_DIR}/reports/coverage
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    DEPENDS ${PROJECT_NAME} core_tests gui_tests # Зависимости от тестов
    COMMENT "Generating code coverage report with tests"
  )
endif()

# Таргет покрытия кода только самого приложения
if(ENABLE_APP_COVERAGE)
  add_custom_target(app_coverage
    COMMAND ${CMAKE_COMMAND} -E make_directory ${PROJECT_ROOT_DIR}/reports/coverage
    COMMAND ${CMAKE_COMMAND} -E chdir ${PROJECT_ROOT_DIR} ${CMAKE_COMMAND} -E remove -f reports/coverage/coverage.info
    COMMAND lcov --capture --directory ${CMAKE_BINARY_DIR} --output-file ${PROJECT_ROOT_DIR}/reports/coverage/coverage.info
    COMMAND lcov --remove ${PROJECT_ROOT_DIR}/reports/coverage/coverage.info '/usr/*' '${PROJECT_ROOT_DIR}/Build/*_autogen/*' --output-file ${PROJECT_ROOT_DIR}/reports/coverage/coverage.info
    COMMAND genhtml ${PROJECT_ROOT_DIR}/reports/coverage/coverage.info --output-directory ${PROJECT_ROOT_DIR}/reports/coverage
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    DEPENDS ${PROJECT_NAME} # Зависимость только от приложения
    COMMENT "Generating code coverage report for application only"
  )
endif()