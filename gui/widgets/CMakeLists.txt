
include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(phos_widgets_SRCS moduleTabs.cpp module.cpp rcu.cpp branch.cpp feecard.cpp)
qt4_automoc(${phos_widgets_SRCS})
add_library(PhosWidgets ${phos_widgets_SRCS})


target_link_libraries(PhosWidgets ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})

 