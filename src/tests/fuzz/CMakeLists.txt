set(MODULE_NAME fuzz_tests)

add_executable(fuzz_core
  fuzz_core.cpp
)

# add_executable(fuzz_gui
#   fuzz_gui.cpp
# )

set_target_properties(fuzz_core PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/tests/fuzz"
)
# set_target_properties(fuzz_gui PROPERTIES
#   RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/tests/fuzz"
# )

target_include_directories(fuzz_core
  PUBLIC
    ${PROJECT_ROOT_DIR}/include
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(fuzz_core
  PRIVATE
    core
    Qt${QT_VERSION_MAJOR}::Core
    # Qt${QT_VERSION_MAJOR}::Test
)

# target_include_directories(fuzz_gui
#   PUBLIC
#     ${PROJECT_ROOT_DIR}/include
#   PRIVATE
#     ${CMAKE_CURRENT_SOURCE_DIR}
# )

# target_link_libraries(fuzz_gui
#   PRIVATE
#     gui
#     Qt${QT_VERSION_MAJOR}::Core
#     # Qt${QT_VERSION_MAJOR}::Widgets
#     # Qt${QT_VERSION_MAJOR}::Test
# )

target_sources(fuzz_core
  PRIVATE
  fuzz_core.cpp
)
# target_sources(fuzz_gui
#   PRIVATE
#     fuzz_gui.cpp
# )

find_program(AFL_FUZZ_EXECUTABLE afl-fuzz)
if(AFL_FUZZ_EXECUTABLE)
  message("AFL found: ${AFL_FUZZ_EXECUTABLE}")

  add_custom_target(run_fuzz_core
    COMMAND ${AFL_FUZZ_EXECUTABLE}
            -m none
            -i ${CMAKE_SOURCE_DIR}/src/tests/fuzz/fuzzin/ 
            -o ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/tests/fuzz/fuzzout 
            --
            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/tests/fuzz/fuzz_core
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    DEPENDS fuzz_core
    COMMENT "Running AFL fuzzer for core module"
  )
else()
  message(WARNING "AFL afl-fuzz not found. Skipping AFL integration.")
endif()