cmake_minimum_required(VERSION 3.13)

project(SmartFilamentSensor_tests
    LANGUAGES C CXX ASM
)

add_subdirectory(mocklib)

enable_testing()
find_package(GTest REQUIRED)
include(GoogleTest)

include_directories (mocklib ../src)


add_executable(movement_sensor__test
    movement_sensor__test.cpp
    ../src/movement_sensor.cpp
)
target_link_libraries(movement_sensor__test GTest::GTest GTest::Main mocklib)
gtest_discover_tests(movement_sensor__test)


add_executable(pin_output__test
    pin_output__test.cpp
    ../src/pin_output.cpp
)
target_link_libraries(pin_output__test GTest::GTest GTest::Main mocklib)
gtest_discover_tests(pin_output__test)
