cmake_minimum_required(VERSION 3.13)

project(SmartFilamentSensor_tests
    LANGUAGES C CXX ASM
)

add_subdirectory(mocklib)

enable_testing()
find_package(GTest REQUIRED)
include(GoogleTest)

set(CMAKE_ROOT_DIR ..)
set(CMAKE_ROOT_SRC_DIR ${CMAKE_ROOT_DIR}/src)

include_directories (mocklib ${CMAKE_ROOT_SRC_DIR})


file(GLOB TEST_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *__test.cpp)

foreach(testSrc ${TEST_SRCS})
    get_filename_component(testName ${testSrc} NAME_WE)

    if (testName MATCHES "^(.*)__test$")
        set(sourceFileName ${CMAKE_MATCH_1})
        add_executable(${testName} ${testSrc} ${CMAKE_ROOT_SRC_DIR}/${sourceFileName}.cpp)
        target_link_libraries(${testName} GTest::GTest GTest::Main mocklib)
        gtest_discover_tests(${testName})
    endif()
endforeach(testSrc)
