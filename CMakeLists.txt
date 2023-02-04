cmake_minimum_required(VERSION 3.18)

include(ExternalProject)

ExternalProject_Add(
    SmatrFilamentSensor_tests
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/tests
    PREFIX ${CMAKE_BINARY_DIR}/tests
    BINARY_DIR ${CMAKE_BINARY_DIR}/tests
    INSTALL_COMMAND ""
    BUILD_ALWAYS 1
 )


include(cmake/pico_sdk_import.cmake)
include(cmake/version.cmake)

project(SmartFilamentSensor
    LANGUAGES C CXX ASM
)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.3.0")
    message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.3.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

pico_sdk_init()

add_subdirectory(src)

ADD_CUSTOM_TARGET(test
  COMMAND make -C ${CMAKE_BINARY_DIR}/tests test
)