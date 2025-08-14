cmake_minimum_required(VERSION 3.16.0)

project(seti_net VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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


message("Compiler: " ${CMAKE_CXX_COMPILER})
message("Architecture: " ${CMAKE_SYSTEM_PROCESSOR})

# Если не указан режим сборки, то устанавливается Debug
if(CMAKE_BUILD_TYPE STREQUAL "")
  set(CMAKE_BUILD_TYPE "Debug")
endif()

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

add_subdirectory(src/core)
add_subdirectory(src/gui)

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

# Добавляем подкаталоги для модулей
#add_qt_module(core src/core)
#add_qt_module(gui  src/gui)

# Подключаем Qt библиотеки
target_link_libraries(${PROJECT_NAME}
  PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Test
    core
    gui
)