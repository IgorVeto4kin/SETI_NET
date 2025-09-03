set(MODULE_NAME gui)

cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_library(${MODULE_NAME} STATIC
  ${CMAKE_CURRENT_SOURCE_DIR}/MainWindow/MainWindow.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/MainWindow/MainWindow.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/MainWindow/buttons.cpp
)

set_target_properties(${MODULE_NAME} PROPERTIES LIBRARY_TYPE STATIC)

find_package(Qt6 COMPONENTS Widgets Core Gui Network)

target_link_libraries(${MODULE_NAME}
  PUBLIC
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Network
  core
)

target_include_directories(${MODULE_NAME}
  PUBLIC
    ${PROJECT_ROOT_DIR}/include
)
