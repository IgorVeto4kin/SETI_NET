cmake_minimum_required(VERSION 3.10.0)

# Настройка минимального стандарта C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Установка каталога проекта
set(PROJECT_ROOT_DIR ${CMAKE_SOURCE_DIR})

# Опции для сборки
option(ENABLE_CODE_COVERAGE "Enable code coverage with tests" OFF)
option(ENABLE_APP_COVERAGE "Enable code coverage for application only" OFF)
option(ENABLE_TESTS "Enable Enable building tests" OFF)
if(ENABLE_CODE_COVERAGE)
  set(ENABLE_TESTS "Enable building tests" ON)
endif()
option(ENABLE_SANITIZERS "Enable Address and Undefined Behavior Sanitizers" OFF)
option(ENABLE_PROFILING "Enable code profiling" OFF)
option(ENABLE_FUZZING "Enable building fuzzing tests" OFF)

if(ENABLE_FUZZING) 
  find_program(AFL_CXX_COMPILER afl-clang-fast++)
  if(AFL_CXX_COMPILER)
    set(CMAKE_CXX_COMPILER ${AFL_CXX_COMPILER})
  else()
    message(FATAL_ERROR "Don't found afl compiler")
  endif()
endif()


if(RUN_ALL_CHECKS)
  set(ENABLE_CODE_COVERAGE ON CACHE BOOL "Enable code coverage with tests" FORCE)
  set(ENABLE_TESTS ON CACHE BOOL "Enable building tests" FORCE)
  set(ENABLE_FUZZING ON CACHE BOOL "Enable building fuzzing tests" FORCE)
  set(ENABLE_SANITIZERS ON CACHE BOOL "Enable Address and Undefined Behavior Sanitizers" FORCE)
  set(ENABLE_PROFILING ON CACHE BOOL "Enable code profiling" FORCE)
endif()

project(QtSecureTemplate LANGUAGES CXX)

# Проверка ОС
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  set(OS_TYPE "LINUX")
else()
  #set(OS_TYPE "UNKNOWN")
  message(FATAL_ERROR "Unsupported OS: ${CMAKE_SYSTEM_NAME}")
endif()

#message("OS type: " ${OS_TYPE})

# Выбор компилятора
if(NOT DEFINED CMAKE_CXX_COMPILER)
  if(${OS_TYPE} STREQUAL "LINUX")
    find_program(CMAKE_CXX_COMPILER NAMES g++ clang++)
endif()

# Выбор архитектуры
if(NOT DEFINED CMAKE_SYSTEM_PROCESSOR)
  if(${OS_TYPE} STREQUAL "LINUX")
    execute_process(COMMAND uname -m OUTPUT_VARIABLE CMAKE_SYSTEM_PROCESSOR OUTPUT_STRIP_TRAILING_WHITESPACE)
endif()


message("Compiler: " ${CMAKE_CXX_COMPILER})
message("Architecture: " ${CMAKE_SYSTEM_PROCESSOR})

# Если не указан режим сборки, то устанавливается Debug
if(CMAKE_BUILD_TYPE STREQUAL "")
  set(CMAKE_BUILD_TYPE "Debug")
endif()

# Подключаем конфигурационные файлы
include(config/version.cmake)
include(config/compiler_flags.cmake)
include(config/os_settings.cmake)
include(config/build_types.cmake)
include(config/static_analyzers.cmake)
include(config/customization.cmake)

# Настройка каталогов сборки для разных типов сборок
setup_build_directories()

# Подключаем Qt
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Gui Widgets Test)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui Widgets Test)
message("Qt version: " ${QT_VERSION})
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)

# Передача основных параметров проекта
add_compile_definitions(APP_NAME="${APP_NAME}")
add_compile_definitions(PROJECT_ROOT_DIR="${PROJECT_ROOT_DIR}")
add_compile_definitions(VERSION_STR="${PROJECT_VERSION}")
add_compile_definitions(OS_TYPE="${OS_TYPE}")
add_compile_definitions(PROJECT_STYLE_SHEET="${PROJECT_STYLE_SHEET}")

configure_file(
  "${PROJECT_ROOT_DIR}/resources/main.qrc.in"
  "${PROJECT_ROOT_DIR}/resources/main.qrc"
  @ONLY
)

# Каталог с ресурсами
set(RESOURCES
  ${PROJECT_ROOT_DIR}/resources/main.qrc
)

# Создание главного исполняемого файла
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
  qt_add_executable(${PROJECT_NAME}
    MANUAL_FINALIZATION
    ${RESOURCES}
    src/main.cpp
  )
  if(${QT_VERSION_MINOR} GREATER_EQUAL 7)
    add_compile_definitions(QT_DEPRECATED_FEATURE_CHECK)  # начиная с Qt 6.7.0 часть функций из Qt5 стала deprecated 
                                                          # => define для отслеживания данных функций.
                                                          # Итогово обеспечивается поддержка как Qt5 так и Qt6 
  endif()
else()
  add_executable(${PROJECT_NAME}
    ${RESOURCES}
    src/main.cpp
  )
endif()

# Функция для добавления подпроектов
function(add_qt_module module_name module_path)
  add_subdirectory(${module_path})
  target_link_libraries(${PROJECT_NAME} PRIVATE ${module_name})
endfunction()

# Добавляем подкаталоги для модулей
add_qt_module(core src/core)
add_qt_module(gui  src/gui)

# Подключаем Qt библиотеки
target_link_libraries(${PROJECT_NAME}
  PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Test
)

if(ENABLE_TESTS)
  enable_testing()
  add_subdirectory(src/tests)
  add_dependencies(${PROJECT_NAME} core_tests gui_tests)
  message("Test are enable")
endif()

if(ENABLE_FUZZING)
  add_subdirectory(src/tests/fuzz)
  add_dependencies(${PROJECT_NAME} fuzz_core)
  message("Fuzz test are enable")
endif()

# Toolchain
if(CMAKE_TOOLCHAIN_FILE)
  message("Using Toolchain file: " ${CMAKE_TOOLCHAIN_FILE})
endif()

add_static_analyzers_target()

# Valgrind
find_program(VALGRIND_EXECUTABLE valgrind)
if(VALGRIND_EXECUTABLE)
  message("Valgrind found: ${VALGRIND_EXECUTABLE}")
  set(VALGRIND_SUPPRESSIONS "${PROJECT_ROOT_DIR}/config/valgrind.supp")

  add_custom_target(run_valgrind
    COMMAND ${VALGRIND_EXECUTABLE}
          --leak-check=full
          --suppressions=${VALGRIND_SUPPRESSIONS} 
          --xml=yes
          --xml-file=${PROJECT_ROOT_DIR}/reports/valgrind_report.xml
          ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    DEPENDS ${PROJECT_NAME}
    COMMENT "Running Valgrind memory check"
  )
else()
  message(WARNING "Valgrind not found. Skipping Valgrind integration.")
endif()

# Покрытие кода
if(ENABLE_CODE_COVERAGE OR ENABLE_APP_COVERAGE)
  include(config/code_coverage.cmake)
endif()

# Профилирование
if(ENABLE_PROFILING)
  include(config/profiling.cmake)
endif()

