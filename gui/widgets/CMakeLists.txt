
include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(phos_widgets_SRCS moduletabs.cpp modulewidget.cpp rcuwidget.cpp branchwidget.cpp fecbutton.cpp)
qt4_automoc(${phos_widgets_SRCS})
add_library(PhosWidgets ${phos_widgets_SRCS})


target_link_libraries(PhosWidgets ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})

 