# Avoid multi inclusion of this file
if(COMMON_QT_CMAKE_INCLUDED)
   return()
endif()
set(COMMON_QT_CMAKE_INCLUDED true)

#include cmake common functions
include(common)

# Create source group for the given qt source and generated files
# SOURCE_FILES The list of source files to add
# GENERATED_UI_HPP_FILES hpp files generated from ui source files
# GENERATED_HPP_CPPMOC_FILES moc cpp files generated from hpp source files
macro(commonQt_source_group SOURCE_FILES GENERATED_UI_HPP_FILES GENERATED_HPP_CPPMOC_FILES)
	# source files group
	common_source_group("Source Files" "${SOURCE_FILES}" "${CMAKE_CURRENT_SOURCE_DIR}/src")

	# Generate hpp from ui and group them
	set(SOURCE_UI_FILES ${SOURCE_FILES})
	list(FILTER SOURCE_UI_FILES INCLUDE REGEX ".ui$")
	if(NOT "${SOURCE_UI_FILES}" STREQUAL "")
		qt5_wrap_ui(${GENERATED_UI_HPP_FILES} ${SOURCE_UI_FILES})
		common_source_group("Generated Files" "${${GENERATED_UI_HPP_FILES}}" "${CMAKE_CURRENT_BINARY_DIR}")
	endif()

	# Generate cpp moc from hpp and group them
	set(SOURCE_HPP_FILES ${SOURCE_FILES})
	list(FILTER SOURCE_HPP_FILES INCLUDE REGEX ".hpp$")
	if(NOT "${SOURCE_HPP_FILES}" STREQUAL "")
		qt5_wrap_cpp(${GENERATED_HPP_CPPMOC_FILES} ${SOURCE_HPP_FILES})
		common_source_group("Generated Files" "${${GENERATED_HPP_CPPMOC_FILES}}" "${CMAKE_CURRENT_BINARY_DIR}/src")	
	endif()
endmacro()

# Setup Qt
macro(commonQt_setup_qt)
	# Enable automatic Qt precompiler
	set(CMAKE_AUTOMOC ON)
	set(CMAKE_AUTORCC ON)
	set(CMAKE_AUTOUIC ON)
	
	# Find Qt5 and required components
	find_package(Qt5 COMPONENTS Core Gui Multimedia MultimediaWidgets Network OpenGL Widgets REQUIRED)
endmacro()

# Copy needed dll in the project target directory
# PROJECT_NAME Main project target name
# DLL_PLUGIN A dll plugin for a module
macro(commonQt_copy_dll PROJECT_NAME DLL_PLUGIN)
	# Find the release *.dll file
	get_target_property(DLL_PLUGIN_PATH ${DLL_PLUGIN} LOCATION)
	get_filename_component(DLL_PLUGIN_FOLDER ${DLL_PLUGIN_PATH} DIRECTORY)
	get_filename_component(DLL_PLUGIN_FOLDER_NAME ${DLL_PLUGIN_FOLDER} NAME)	
	
	# Find the debug *d.dll file
	get_target_property(DLL_PLUGIN_DEBUG_PATH ${DLL_PLUGIN} IMPORTED_LOCATION_DEBUG)
	get_filename_component(DLL_PLUGIN_DEBUG_FOLDER ${DLL_PLUGIN_DEBUG_PATH} DIRECTORY)
	get_filename_component(DLL_PLUGIN_DEBUG_FOLDER_NAME ${DLL_PLUGIN_DEBUG_FOLDER} NAME)	
	
	# Copy dlls
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		 COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:${PROJECT_NAME}>/${DLL_PLUGIN_FOLDER_NAME}/
		 COMMAND ${CMAKE_COMMAND} -E copy_if_different $<$<CONFIG:Debug>:${DLL_PLUGIN_DEBUG_PATH}> $<$<NOT:$<CONFIG:Debug>>:${DLL_PLUGIN_PATH}> $<TARGET_FILE_DIR:${PROJECT_NAME}>/${DLL_PLUGIN_FOLDER_NAME})
endmacro()

# Link target to libraries and copy qt dlls to executable folder
# PROJECT_NAME Main project target name
macro(commonQt_target_link PROJECT_NAME)
	# Link executable to needed libraries
	target_link_libraries(${PROJECT_NAME} 
		Qt5::Core
		Qt5::Gui
		Qt5::Multimedia
		Qt5::MultimediaWidgets
		Qt5::Network
		Qt5::OpenGL
		Qt5::Widgets
	)
	
	# Copy dlls
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Core> $<TARGET_FILE_DIR:${PROJECT_NAME}>
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Gui> $<TARGET_FILE_DIR:${PROJECT_NAME}>
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Multimedia> $<TARGET_FILE_DIR:${PROJECT_NAME}>
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::MultimediaWidgets> $<TARGET_FILE_DIR:${PROJECT_NAME}>
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Network> $<TARGET_FILE_DIR:${PROJECT_NAME}>
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::OpenGL> $<TARGET_FILE_DIR:${PROJECT_NAME}>		
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Widgets> $<TARGET_FILE_DIR:${PROJECT_NAME}>	
	)
	
	# Copy dll plugins
	foreach(QTMODULE Core;Gui;Multimedia;MultimediaWidgets;Network;OpenGL;Widgets)
		if(NOT QTMODULE STREQUAL "")
			foreach(PLUGIN ${Qt5${QTMODULE}_PLUGINS})
				commonQt_copy_dll(${PROJECT_NAME} ${PLUGIN})
			endforeach()
		endif()
	endforeach()
endmacro()