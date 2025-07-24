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
#message(STATUS "We fucked up finding required packages. Run \n sudo ./setup.sh \n for download them")

if (NOT Qt6_FOUND)
    message(STATUS "We fucked up finding required packages. Run \n sudo ../setup.sh \nfor download them")

    
    execute_process(
        COMMAND chmod +x install_dependances.sh
        #RESULT_VARIABLE UPDATE_RESULT
    )
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