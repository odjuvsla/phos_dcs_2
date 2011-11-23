project( gui )
	
include_directories(
	${CMAKE_CURRENT_BINARY_DIR} 
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

add_library ( PiLoggerGui ${gui_SRCS} ${UIS} ${MOCS} )
target_link_libraries ( PiLoggerGui  ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} )
