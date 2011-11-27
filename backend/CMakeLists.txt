

set(FEECLIENT $ENV{FEECLIENT})
include_directories(${FEECLIENT}/include)
find_library(FEELIB FeeClient ${FEECLIENT}/lib)
find_library(DIMLIB dim ${FEECLIENT}/lib)

set(phosDcsBackend_SRCS registers/trgconf.cpp registers/altroif.cpp registers/actfeclist.cpp registers/register.cpp fec.cpp rcu.cpp phosdcsinterface.cpp phosdcsclient.cpp phosregisters.cpp binarycompiler.cpp instructionmaker.cpp)
qt4_automoc(${phosDcsBackend_SRCS})
add_library(PhosDcsBackend ${phosDcsBackend_SRCS})

target_link_libraries(PhosDcsBackend ${FEELIB} ${DIMLIB} PhosDcsLogging PiLogger ${QT_QTCORE_LIBRARY} )

add_subdirectory(registermaps)
include_directories(registermaps)

add_subdirectory(registers)
include_directories(registers)

add_subdirectory(tests)
