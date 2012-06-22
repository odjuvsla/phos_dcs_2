include_directories(${CMAKE_CURRENT_BINARY_DIR})
add_subdirectory(widgets)

set(phos_gui_2_SRCS phosgui.cpp phos_gui_2.cpp)
qt4_automoc(${phos_gui_2_SRCS})
add_executable(phos_gui_2 ${phos_gui_2_SRCS})

target_link_libraries(phos_gui_2 PhosDcsBackend PhosDcsLogging PhosWidgets PiLogger PiLoggerGui ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${phos_widgets} )


