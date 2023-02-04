cmake_minimum_required(VERSION 3.18)

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

set (sensor_management__test_SOURCES ${CMAKE_ROOT_SRC_DIR}/movement_sensor.cpp)


file(GLOB TEST_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *__test.cpp)


foreach(testSrc ${TEST_SRCS})
    get_filename_component(testName ${testSrc} NAME_WE)

    if (testName MATCHES "^(.*)__test$")
        set(sourceFileName ${CMAKE_MATCH_1})
        set(EXTRA_SOURCES ${testName}_SOURCES)
        set(EXTRA_SOURCES ${${EXTRA_SOURCES}})

        add_executable(${testName} ${testSrc} ${CMAKE_ROOT_SRC_DIR}/${sourceFileName}.cpp ${EXTRA_SOURCES})
        target_link_libraries(${testName} GTest::gmock GTest::gmock_main GTest::gtest GTest::gtest_main mocklib)
        gtest_discover_tests(${testName})
    endif()
endforeach(testSrc)
