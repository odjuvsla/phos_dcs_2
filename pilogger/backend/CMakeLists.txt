project( backend )
cmake_minimum_required( VERSION 2.6 )
set ( CMAKE_BUILD_TYPE Release )
add_definitions ( -Wall )
find_package ( Qt4 REQUIRED )
include ( ${QT_USE_FILE} )
include_directories (
	${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}
	${QT_QTCORE_INCLUDE_DIR} ${QT_QTCORE_INCLUDE_DIR}
	)
set ( backend_HDRS
	
	)

set ( backend_SRCS ../dao/sql/logdatabase.cpp pilogger.cpp ../model/logelement.cpp 
	)

set ( log_MOCS
	  pilogger.h ../model/logelement.h
	)
QT4_WRAP_CPP(MOCS ${log_MOCS})

add_library ( PiLogger ${backend_SRCS} ${MOCS})
target_link_libraries ( PiLogger  ${QT_QTCORE_LIBRARY} ${QT_QTCORE_LIBRARY} )

add_subdirectory(test)