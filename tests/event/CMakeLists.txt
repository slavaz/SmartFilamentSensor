
enable_testing()

find_package(GTest REQUIRED)

include(GoogleTest)

get_filename_component(CMAKE_TEST_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR} PATH)
get_filename_component(CMAKE_ROOT_DIR ${CMAKE_TEST_ROOT_DIR} PATH)
set(CMAKE_ROOT_SRC_DIR ${CMAKE_ROOT_DIR}/src)
set(CMAKE_ROOT_SRC_EVENT_DIR ${CMAKE_ROOT_SRC_DIR}/event)

include_directories (${CMAKE_TEST_ROOT_DIR}/mocklib ${CMAKE_ROOT_SRC_DIR})

set(COMMON_TEST_SOURCES
        ${CMAKE_ROOT_SRC_DIR}/sensor_management.cpp   
        ${CMAKE_ROOT_SRC_DIR}/timer.cpp)

    file(GLOB TEST_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *__test.cpp)

foreach(testSrc ${TEST_SRCS})
    get_filename_component(testName ${testSrc} NAME_WE)

    if (testName MATCHES "^(.*)__test$")
        set(sourceFileName ${CMAKE_MATCH_1})
        set(EXTRA_SOURCES ${testName}_SOURCES)
        set(EXTRA_SOURCES ${${EXTRA_SOURCES}})

        add_executable(${testName} 
                ${testSrc} 
                ${CMAKE_ROOT_SRC_EVENT_DIR}/${sourceFileName}.cpp 
                ${COMMON_TEST_SOURCES} 
                ${EXTRA_SOURCES})
        target_link_libraries(${testName} GTest::gmock GTest::gmock_main GTest::gtest GTest::gtest_main mocklib)
        gtest_discover_tests(${testName})
    endif()
endforeach(testSrc)
