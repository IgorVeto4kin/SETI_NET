set(MODULE_NAME tests)

add_executable(core_tests
  unit/core_test.cpp
)
add_executable(gui_tests
  unit/gui_test.cpp
)

set_target_properties(core_tests PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/tests/unit"
)
set_target_properties(gui_tests PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/tests/unit"
)

target_include_directories(core_tests
  PUBLIC
    ${PROJECT_ROOT_DIR}/include
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(core_tests
  PRIVATE
    core
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Test
)

target_include_directories(gui_tests
  PUBLIC
    ${PROJECT_ROOT_DIR}/include
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(gui_tests
  PRIVATE
    gui
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Test
)

target_sources(core_tests
  PRIVATE
    unit/core_test.cpp
)
target_sources(gui_tests
  PRIVATE
    unit/gui_test.cpp
)

add_test(NAME core_tests COMMAND core_tests)
add_test(NAME gui_tests COMMAND gui_tests)

add_subdirectory(fuzz)

# Таргет для запуска тестов и перемещения их логов
add_custom_target(run_tests
  COMMAND ${CMAKE_COMMAND} -E make_directory ${PROJECT_ROOT_DIR}/reports
  COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_BINARY_DIR} ctest
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/Testing/Temporary/LastTest.log ${PROJECT_ROOT_DIR}/reports/test_results.log
  DEPENDS core_tests gui_tests
  COMMENT "Running tests and moving results to reports directory"
)