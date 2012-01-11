

set(FEECLIENT $ENV{FEECLIENT})
include_directories(SYSTEM ${FEECLIENT}/include)
find_library(FEELIB FeeClient ${FEECLIENT}/lib)
find_library(DIMLIB dim ${FEECLIENT}/lib)

set(phosDcsBackend_SRCS registers/dstb_bcnt.cpp registers/dstb_acnt.cpp registers/ttcl2_rcnt.cpp registers/ttcl2_acnt.cpp registers/auxtrgcnt.cpp registers/swttrgcnt.cpp registers/mebstcnt.cpp registers/busbsy.cpp registers/altbsst_trsf.cpp registers/altbusstatus.cpp registers/rdoerr.cpp registers/fecerrb.cpp registers/fecerra.cpp registers/rcuid.cpp registers/bp_version.cpp registers/rcu_version.cpp registers/altrocfg2.cpp registers/altrocfg1.cpp registers/rdomod.cpp registers/trgconf.cpp registers/altroif.cpp registers/actfeclist.cpp registers/register.cpp fec.cpp rcu.cpp phosdcsinterface.cpp phosdcsclient.cpp phosregisters.cpp binarycompiler.cpp instructionmaker.cpp)
qt4_automoc(${phosDcsBackend_SRCS})
add_library(PhosDcsBackend ${phosDcsBackend_SRCS})

target_link_libraries(PhosDcsBackend ${FEELIB} ${DIMLIB} PhosDcsLogging PiLogger ${QT_QTCORE_LIBRARY} )

add_subdirectory(registermaps)
include_directories(registermaps)

add_subdirectory(registers)
include_directories(registers)

add_subdirectory(tests)
