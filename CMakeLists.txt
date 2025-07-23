cmake_minimum_required(VERSION 3.16)
project(seti-net VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable automatic MOC, UIC, and RCC for Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)


set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_AUTOGEN_BUILD_DIR ${CMAKE_BINARY_DIR}/autogen)

set(CMAKE_AUTOGEN_VERBOSE ON)


configure_file(
    "${CMAKE_SOURCE_DIR}/.project_root"
    COPYONLY
)

# Find Qt6 with required components
find_package(Qt6 COMPONENTS Widgets Core Gui Network)

if (NOT Qt6_FOUND)
    message(STATUS "Qt6 modules not found. Attempting to install on Ubuntu...")

    # Install Qt6 base and required modules using apt
    execute_process(
        COMMAND sudo apt update
        RESULT_VARIABLE UPDATE_RESULT
    )
    if (NOT UPDATE_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to run 'sudo apt update'. Please ensure you have sudo privileges and try again.")
    endif()

    # Install qt6-base-dev (includes Core, Gui) and additional modules
    execute_process(
        COMMAND sudo apt install -y qt6-base-dev qt6-network-dev
        RESULT_VARIABLE INSTALL_RESULT
    )
    if (NOT INSTALL_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to install Qt6 modules. Please install 'qt6-base-dev' and 'qt6-network-dev' manually using 'sudo apt install qt6-base-dev qt6-network-dev'.")
    endif()

    # Re-run find_package after installation attempt
    find_package(Qt6 COMPONENTS Widgets Core Gui Network REQUIRED)
    if (NOT Qt6_FOUND)
        message(FATAL_ERROR "Qt6 modules still not found after installation attempt. Please verify Qt6 installation and set Qt6_DIR if necessary.")
    endif()
endif()

# Add executable or library target
add_executable(${PROJECT_NAME}
    src/main.cpp
    src/core/netinfo.cpp
    src/core/netinfo.h
    src/gui/mainwindow.cpp
    src/gui/mainwindow.h
    src/logs/logwriter.cpp   
    src/logs/logwriter.h
    src/applyment/applyment.h
    src/applyment/applyment.cpp


)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/src/core
    ${CMAKE_SOURCE_DIR}/src/gui
    ${CMAKE_SOURCE_DIR}/src/logs
    ${CMAKE_SOURCE_DIR}/src/applyment

)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Widgets
    Qt6::Core
    Qt6::Gui
    Qt6::Network
)

target_compile_definitions(${PROJECT_NAME} PRIVATE QT_DEPRECATED_WARNINGS)