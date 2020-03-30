cmake_minimum_required(VERSION 3.15.2 FATAL_ERROR)

# Add common funtions folder
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/ext/cmake)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Include Qt common functions
include(commonQt)

# Project base information
project(mediaBrowser VERSION 1.0.0 LANGUAGES CXX)

# Setup Qt project
commonQt_setup_qt()

# Set project flags
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add project source files
set(SOURCE_FILES
	${CMAKE_CURRENT_SOURCE_DIR}/src/core/controller.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/core/controller.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/core/viewInterface.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/ui/analysis.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/ui/analysis.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/ui/fileSystemBrowser.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/ui/fileSystemBrowser.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/ui/histogram.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/ui/histogram.hpp	
	${CMAKE_CURRENT_SOURCE_DIR}/src/ui/log.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/ui/log.hpp	
	${CMAKE_CURRENT_SOURCE_DIR}/src/ui/mainWindow.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/ui/mainWindow.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/ui/metadataBrowser.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/ui/metadataBrowser.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/ui/player.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/ui/player.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)
commonQt_source_group("${SOURCE_FILES}" GENERATED_UI_HPP_FILES GENERATED_HPP_CPPMOC_FILES)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/ext/3rdparty/qt/qtpropertybrowser)

# Compute executable
add_executable(mediaBrowser WIN32
	${SOURCE_FILES}
	${GENERATED_UI_HPP_FILES}
	${GENERATED_HPP_CPPMOC_FILES}
)

#include Include current header directory
target_include_directories(mediaBrowser PRIVATE 
	${CMAKE_CURRENT_SOURCE_DIR}/src
	${CMAKE_CURRENT_SOURCE_DIR}/ext/3rdparty/qt
)

# Set current target as active
set_directory_properties(PROPERTIES VS_STARTUP_PROJECT mediaBrowser)

# Link and copy dlls
commonQt_target_link(${PROJECT_NAME})

# Copy samples
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	 COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/res/samples $<TARGET_FILE_DIR:${PROJECT_NAME}>/_samples
)

target_link_libraries(mediaBrowser PropertyBrowser)