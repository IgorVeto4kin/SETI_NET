set(MODULE_NAME core)

cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_library(${MODULE_NAME} STATIC
  ${CMAKE_CURRENT_SOURCE_DIR}/${MODULE_NAME}_apply/${MODULE_NAME}_apply.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/${MODULE_NAME}_apply/${MODULE_NAME}_apply.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/${MODULE_NAME}_logger/${MODULE_NAME}_logger.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/${MODULE_NAME}_logger/${MODULE_NAME}_logger.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/${MODULE_NAME}_network/${MODULE_NAME}_network.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/${MODULE_NAME}_network/${MODULE_NAME}_network.cpp
)

set_target_properties(${MODULE_NAME} PROPERTIES LIBRARY_TYPE STATIC)

find_package(Qt6 COMPONENTS Core Network)

target_link_libraries(${MODULE_NAME}
  PRIVATE
    Qt6::Core
    Qt6::Network
)

target_include_directories(core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR} 
)