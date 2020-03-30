cmake_minimum_required(VERSION 3.15.2 FATAL_ERROR)

project(PropertyBrowser)

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

# Sources and headers
set(QT_PROPERTY_EDITOR_HEADERS
	qtpropertybrowser.h
	qtpropertymanager.h
	qteditorfactory.h
	qtvariantproperty.h
	qttreepropertybrowser.h
	qtbuttonpropertybrowser.h
	qtgroupboxpropertybrowser.h
	qtpropertybrowserutils_p.h
)
set(QT_PROPERTY_EDITOR_SOURCES
	qtpropertybrowser.cpp
	qtpropertymanager.cpp
	qteditorfactory.cpp
	qtvariantproperty.cpp
	qttreepropertybrowser.cpp
	qtbuttonpropertybrowser.cpp
	qtgroupboxpropertybrowser.cpp
	qtpropertybrowserutils.cpp
)

# Include headers
include_directories(
	${CMAKE_CURRENT_BINARY_DIR}
	${CMAKE_CURRENT_BINARY_DIR}/src)
	include_directories(src)
	INCLUDE_DIRECTORIES(
	${QT_INCLUDE_DIR}
)

# Generate cpp moc files (for the corresponding headers)
qt5_generate_moc(qtpropertybrowser.h ${CMAKE_CURRENT_BINARY_DIR}/moc_qtpropertybrowser.cpp)
qt5_generate_moc(qtpropertymanager.h ${CMAKE_CURRENT_BINARY_DIR}/moc_qtpropertymanager.cpp)
qt5_generate_moc(qteditorfactory.h ${CMAKE_CURRENT_BINARY_DIR}/moc_qteditorfactory.cpp)
qt5_generate_moc(qtvariantproperty.h ${CMAKE_CURRENT_BINARY_DIR}/moc_qtvariantproperty.cpp)
qt5_generate_moc(qttreepropertybrowser.h ${CMAKE_CURRENT_BINARY_DIR}/moc_qttreepropertybrowser.cpp)
qt5_generate_moc(qtbuttonpropertybrowser.h ${CMAKE_CURRENT_BINARY_DIR}/moc_qtbuttonpropertybrowser.cpp)
qt5_generate_moc(qtgroupboxpropertybrowser.h ${CMAKE_CURRENT_BINARY_DIR}/moc_qtgroupboxpropertybrowser.cpp)
qt5_generate_moc(qtpropertymanager.cpp ${CMAKE_CURRENT_BINARY_DIR}/qtpropertymanager.moc)
qt5_generate_moc(qteditorfactory.cpp ${CMAKE_CURRENT_BINARY_DIR}/qteditorfactory.moc)
qt5_generate_moc(qttreepropertybrowser.cpp ${CMAKE_CURRENT_BINARY_DIR}/qttreepropertybrowser.moc)

# Get cpp needed for moc files generation
set(QT_PROPERTY_EDITOR_HEADERS_ONLY_MOC
  ${CMAKE_CURRENT_BINARY_DIR}/moc_qtpropertybrowser.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/moc_qtpropertymanager.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/moc_qteditorfactory.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/moc_qtvariantproperty.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/moc_qttreepropertybrowser.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/moc_qtbuttonpropertybrowser.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/moc_qtgroupboxpropertybrowser.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/qtpropertymanager.moc
  ${CMAKE_CURRENT_BINARY_DIR}/qteditorfactory.moc
  ${CMAKE_CURRENT_BINARY_DIR}/qttreepropertybrowser.moc
)
set_source_files_properties(${QT_PROPERTY_EDITOR_HEADERS_ONLY_MOC} PROPERTIES HEADER_FILE_ONLY true)

# Generate cpp moc files (for the corresponding headers)
qt5_generate_moc(qtpropertybrowserutils_p.h ${CMAKE_CURRENT_BINARY_DIR}/moc_qtpropertybrowserutils_p.cpp)

set(QT_PROPERTY_EDITOR_HEADERS_MOC 
	${CMAKE_CURRENT_BINARY_DIR}/moc_qtpropertybrowserutils_p.cpp
)
set(QT_PROPERTY_EDITOR_MOC
  ${QT_PROPERTY_EDITOR_HEADERS_MOC}
  ${QT_PROPERTY_EDITOR_HEADERS_ONLY_MOC}
)

# Resources
qt5_add_resources(QT_PROPERTY_EDITOR_RESOURCES qtpropertybrowser.qrc)
qt5_add_resources(RESOURCE_SRCS qtpropertybrowser.qrc)

set(SOURCES
	${extension_MOC}
	${QT_PROPERTY_EDITOR_MOC}
	${QT_PROPERTY_EDITOR_SOURCES}
	${QT_PROPERTY_EDITOR_RESOURCES}
)

add_library(PropertyBrowser 
	${QT_PROPERTY_EDITOR_HEADERS} 
	${SOURCES}
)

# Link executable to needed libraries
target_link_libraries(PropertyBrowser
	Qt5::Core
	Qt5::Gui
	Qt5::Widgets
)	

# Add needed definitions
add_definitions(${QT_DEFINITIONS})
add_definitions(-DQT_DLL)
add_definitions(-DQT_QTPROPERTYBROWSER_EXPORT)
add_definitions(-DQT_PLUGIN)
add_definitions(-DQT_SHARED)

# Installation
install(TARGETS PropertyBrowser LIBRARY DESTINATION lib ${INSTALL_TARGETS_DEFAULT_ARGS} )