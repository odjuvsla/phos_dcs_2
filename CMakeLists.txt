project(phos_dcs_2)
cmake_minimum_required(VERSION 2.6)
find_package(Qt4 REQUIRED)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set(phos_dcs_2_SRCS phos_dcs_2.cpp main.cpp)
qt4_automoc(${phos_dcs_2_SRCS})
add_executable(phos_dcs_2 ${phos_dcs_2_SRCS})
target_link_libraries(phos_dcs_2 ${QT_QTCORE_LIBRARY})
