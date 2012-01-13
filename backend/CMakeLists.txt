

set(FEECLIENT $ENV{FEECLIENT})
include_directories(SYSTEM ${FEECLIENT}/include)
find_library(FEELIB FeeClient ${FEECLIENT}/lib)
find_library(DIMLIB dim ${FEECLIENT}/lib)

set(phosDcsBackend_SRCS registers/bc/bcversion.cpp registers/rcu/control.cpp registers/rcu/da_fsm.cpp registers/rcu/evmngpr_st.cpp registers/rcu/insseqpr_st.cpp registers/rcu/rdofsmpr_st.cpp registers/rcu/abdfsmpr_st.cpp registers/rcu/blth_mm_cnt.cpp registers/rcu/add_mm_cnt.cpp registers/rcu/dstb_numb.cpp registers/rcu/dstb_numa.cpp registers/rcu/cstbbcnt.cpp registers/rcu/cstbacnt.cpp registers/rcu/ackb_cnt.cpp registers/rcu/acka_cnt.cpp registers/rcu/trsfbcnt.cpp registers/rcu/trsfacnt.cpp registers/rcu/dstb_bcnt.cpp registers/rcu/dstb_acnt.cpp registers/rcu/ttcl2_rcnt.cpp registers/rcu/ttcl2_acnt.cpp registers/rcu/auxtrgcnt.cpp registers/rcu/swttrgcnt.cpp registers/rcu/mebstcnt.cpp registers/rcu/busbsy.cpp registers/rcu/altbsst_trsf.cpp registers/rcu/altbusstatus.cpp registers/rcu/rdoerr.cpp registers/rcu/fecerrb.cpp registers/rcu/fecerra.cpp registers/rcu/rcuid.cpp registers/rcu/bp_version.cpp registers/rcu/rcu_version.cpp registers/rcu/altrocfg2.cpp registers/rcu/altrocfg1.cpp registers/rcu/rdomod.cpp registers/rcu/trgconf.cpp registers/rcu/altroif.cpp registers/rcu/actfeclist.cpp registers/register.cpp    fec.cpp rcu.cpp phosdcsinterface.cpp phosdcsclient.cpp phosregisters.cpp binarycompiler.cpp instructionmaker.cpp)

set(Backend_MOC_HDRS phosdcsinterface.h)

QT4_WRAP_CPP(Backend_MOC_SRCS ${Backend_MOC_HDRS})

add_library(PhosDcsBackend ${phosDcsBackend_SRCS} ${Backend_MOC_SRCS})

target_link_libraries(PhosDcsBackend ${FEELIB} ${DIMLIB} PhosDcsLogging PiLogger ${QT_QTCORE_LIBRARY} )

add_subdirectory(registermaps)
include_directories(registermaps)

add_subdirectory(registers)
include_directories(registers)
include_directories(registers/rcu)

add_subdirectory(tests)
