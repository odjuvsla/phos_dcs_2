
add_executable(registerTest registerTest.cpp)
add_executable(simpleTest simpletest.cpp)
add_executable(readRegisters readRegisters.cpp)

target_link_libraries(simpleTest PhosDcsBackend ${PiLogger})
target_link_libraries(registerTest PhosDcsBackend ${PiLogger})
target_link_libraries(readRegisters PhosDcsBackend ${PiLogger})


