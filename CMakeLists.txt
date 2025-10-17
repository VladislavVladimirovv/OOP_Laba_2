cmake_minimum_required(VERSION 3.10)
project(OOP_LABA_2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

include_directories(include)

add_executable(main src/main.cpp src/octal.cpp)

add_executable(test_octal tests/test_octal.cpp src/octal.cpp)
target_link_libraries(test_octal GTest::gtest_main Threads::Threads)

enable_testing()
add_test(NAME OctalTests COMMAND test_octal)

add_custom_target(run_tests
    COMMAND ./test_octal
    DEPENDS test_octal
    COMMENT "Running Octal tests"
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)