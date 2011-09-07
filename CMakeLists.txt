project(phos_dcs_2)
cmake_minimum_required(VERSION 2.6)
find_package(Qt4 REQUIRED)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR} logger common)


add_subdirectory(logger)
add_subdirectory(common)
add_subdirectory(backend)
#add_subdirectory(gui/widgets)
add_subdirectory(gui)

