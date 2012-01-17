project(phos_dcs_2)
cmake_minimum_required(VERSION 2.6)
find_package(Qt4 REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic -Woverloaded-virtual -Weffc++ -Wctor-dtor-privacy")

include_directories(SYSTEM ${QT_INCLUDES})
include_directories( ${CMAKE_CURRENT_BINARY_DIR} logger common $ENV{FEECLIENT})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic -Woverloaded-virtual -Weffc++ -Wctor-dtor-privacy")
#set(CMAKE_CXX_FALGS "${CMAKE_CXX_FLAGS} -Wno")
include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR} logger common )

set(FEECLIENT $ENV{FEECLIENT})
include_directories(SYSTEM ${FEECLIENT}/include)
find_library(FEELIB FeeClient ${FEECLIENT}/lib)
find_library(DIMLIB dim ${FEECLIENT}/lib)

add_subdirectory(logger)
add_subdirectory(pilogger)
add_subdirectory(gui)
add_subdirectory(common)
add_subdirectory(backend)

