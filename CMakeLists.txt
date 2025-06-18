cmake_minimum_required(VERSION 3.5)
project(seti-net LANGUAGES CXX)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_AUTOGEN_BUILD_DIR ${CMAKE_BINARY_DIR}/autogen)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOGEN_VERBOSE ON)

configure_file(
    "${CMAKE_SOURCE_DIR}/.project_root"
    COPYONLY
)

# find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Core Gui Network)
#find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Core Gui Network)

find_package(Qt6 COMPONENTS Widgets Core Gui Network)
if (NOT Qt6_FOUND)
    message("not found")
    find_package(Qt5 COMPONENTS Widgets Core Gui Network)
endif()

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/core/netinfo.cpp
    src/core/netinfo.h
    src/gui/mainwindow.cpp
    src/gui/mainwindow.h
    src/logs/logwriter.cpp   
    src/logs/logwriter.h 
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/src/core
    ${CMAKE_SOURCE_DIR}/src/gui
    ${CMAKE_SOURCE_DIR}/src/logs
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Widgets
    Qt6::Core
    Qt6::Gui
    Qt6::Network
)


target_compile_definitions(${PROJECT_NAME} PRIVATE QT_DEPRECATED_WARNINGS)
