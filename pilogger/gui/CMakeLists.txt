project( gui )
cmake_minimum_required( VERSION 2.6 )
set ( CMAKE_BUILD_TYPE Release )
add_definitions ( -Wall )
find_package ( Qt4 REQUIRED )
include ( ${QT_USE_FILE} )
include_directories (
	${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}
	${QT_QTCORE_INCLUDE_DIR} ${QT_QTGUI_INCLUDE_DIR} ${QT_QTCORE_INCLUDE_DIR} ${QT_QTGUI_INCLUDE_DIR}
	)
set ( gui_HDRS
	
	)

set ( gui_SRCS
	main.cpp
	logviewer.cpp
	../model/logelement.cpp
	)

set ( gui_UIS
	logviewer.ui
	)
QT4_WRAP_UI(UIS ${gui_UIS})

set ( gui_MOCS
	logviewer.h
	)
QT4_WRAP_CPP(MOCS ${gui_MOCS})

add_library ( PiLoggerGui ${gui_SRCS} ${UIS} ${RSCS} ${TRS} ${MOCS} )
target_link_libraries ( PiLoggerGui  ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} )
