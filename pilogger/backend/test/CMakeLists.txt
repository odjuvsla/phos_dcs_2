project( backend )

add_executable ( testLogBackend test.cpp)

target_link_libraries ( testLogBackend ${QT_QTCORE_LIBRARY} ${QT_QTCORE_LIBRARY} PiLogger)
