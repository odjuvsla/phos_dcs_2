cmake_minimum_required( VERSION 2.6 )

# Since this is supposed to be a stand alone library we put the requirement for 
# QT here as well. 
find_package ( Qt4 REQUIRED )
include ( ${QT_USE_FILE} )

include_directories (SYSTEM
		      ${QT_QTCORE_INCLUDE_DIR} ${QT_QTGUI_INCLUDE_DIR}
		    )

add_subdirectory(backend)
add_subdirectory(gui)
add_subdirectory(dao/sql)
