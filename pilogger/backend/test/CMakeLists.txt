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

add_executable ( testLogBackend test.cpp)
target_link_libraries ( testLogBackend ${QT_QTCORE_LIBRARY} ${QT_QTCORE_LIBRARY} PiLogger)
