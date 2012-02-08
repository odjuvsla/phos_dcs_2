
include_directories(dcsinterface)
include_directories(registers)
include_directories(registers/rcu)
include_directories(registers/rcu)
include_directories(registermaps)

# create phosDcsBackend source file list
set(phosDcsBackend_SRCS dcsinterface/binarycompiler.cpp
			dcsinterface/instructionmaker.cpp
			dcsinterface/phosdcsclient.cpp
			dcsinterface/phosdcsinterface.cpp
			dcsinterface/phosregisters.cpp
			dcsinterface/rcu.cpp
                        dcsinterface/fec.cpp
   )
set(phosDcsBackend_SRCS ${phosDcsBackend_SRCS}
			registers/bc/bcversion.cpp
			registers/rcu/abdfsmpr_st.cpp
			registers/rcu/acka_cnt.cpp
			registers/rcu/ackb_cnt.cpp
			registers/rcu/actfeclist.cpp
			registers/rcu/add_mm_cnt.cpp
			registers/rcu/altbsst_trsf.cpp
			registers/rcu/altbusstatus.cpp
			registers/rcu/altrocfg1.cpp
			registers/rcu/altrocfg2.cpp
			registers/rcu/altroif.cpp
			registers/rcu/auxtrgcnt.cpp
			registers/rcu/blth_mm_cnt.cpp
			registers/rcu/bp_version.cpp
			registers/rcu/busbsy.cpp
			registers/rcu/control.cpp
			registers/rcu/cstbacnt.cpp
			registers/rcu/cstbbcnt.cpp
			registers/rcu/da_fsm.cpp
			registers/rcu/dstb_acnt.cpp
			registers/rcu/dstb_bcnt.cpp
			registers/rcu/dstb_numa.cpp
			registers/rcu/dstb_numb.cpp
			registers/rcu/evmngpr_st.cpp
			registers/rcu/fecerra.cpp
			registers/rcu/fecerrb.cpp
			registers/rcu/insseqpr_st.cpp
			registers/rcu/mebstcnt.cpp
			registers/rcu/rcu_version.cpp
			registers/rcu/rcuid.cpp
			registers/rcu/rdoerr.cpp
			registers/rcu/rdofsmpr_st.cpp
			registers/rcu/rdomod.cpp
			registers/rcu/swttrgcnt.cpp
			registers/rcu/trgconf.cpp
			registers/rcu/trsfacnt.cpp
			registers/rcu/trsfbcnt.cpp
			registers/rcu/ttcl2_acnt.cpp
			registers/rcu/ttcl2_rcnt.cpp
			registers/register.cpp
   )

qt4_automoc(${phosDcsBackend_SRCS})
add_library(PhosDcsBackend ${phosDcsBackend_SRCS})

target_link_libraries(PhosDcsBackend ${FEELIB} ${DIMLIB} PhosDcsLogging PiLogger ${QT_QTCORE_LIBRARY} )


add_subdirectory(dcsinterface)
add_subdirectory(registermaps)
add_subdirectory(registers)
add_subdirectory(tests)
