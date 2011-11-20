
add_executable(registerTest registerTest.cpp)
add_executable(simpleTest simpletest.cpp)

target_link_libraries(simpleTest PhosDcsBackend )
target_link_libraries(registerTest PhosDcsBackend)



