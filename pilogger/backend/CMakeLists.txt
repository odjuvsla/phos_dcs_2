project( backend )

include_directories(
	${CMAKE_CURRENT_BINARY_DIR} 
	)

set ( backend_SRCS ../dao/sql/logdatabase.cpp ../model/logelement.cpp pilogger.cpp 
	)

set ( backend_MOCS
	  pilogger.h
	)

QT4_WRAP_CPP(MOCS ${backend_MOCS})

add_library ( PiLogger ${backend_SRCS} ${MOCS})
target_link_libraries ( PiLogger  ${QT_QTCORE_LIBRARY} ${QT_QTCORE_LIBRARY} )

add_subdirectory(test)