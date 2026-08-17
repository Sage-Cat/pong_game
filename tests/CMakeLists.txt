add_executable(pong_core_tests PhysicsTest.cpp)
target_link_libraries(pong_core_tests PRIVATE pong_core)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(pong_core_tests PRIVATE -Wall -Wextra -Wpedantic)
elseif(MSVC)
    target_compile_options(pong_core_tests PRIVATE /W4)
endif()

add_test(NAME pong_core_tests COMMAND pong_core_tests)
