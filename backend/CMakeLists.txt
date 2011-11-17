
include_directories($ENV{FEECLIENT}/include)
set(FEECLIENT $ENV{FEECLIENT})

find_library(FEELIB FeeClient ${FEECLIENT}/lib)
find_library(DIMLIB dim ${FEECLIENT}/lib)

include_directories($ENV{FEECLIENT}/include)

set(phosDcsBackend_SRCS fec.cpp rcu.cpp phosdcsinterface.cpp phosdcsclient.cpp phosregisters.cpp binarycompiler.cpp instructionmaker.cpp)
qt4_automoc(${phosDcsBackend_SRCS})
add_library(PhosDcsBackend ${phosDcsBackend_SRCS})

target_link_libraries(PhosDcsBackend ${FEELIB} ${DIMLIB} PhosDcsLogging ${QT_QTCORE_LIBRARY} )


add_subdirectory(tests)