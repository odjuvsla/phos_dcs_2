
include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(logger_SRCS phosdcslogging.cpp)
qt4_automoc(${logger_SRCS})
add_library(PhosDcsLogging ${logger_SRCS})
target_link_libraries(PhosDcsLogging ${QT_QTCORE_LIBRARY})

