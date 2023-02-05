file(GLOB EVENT_HANDLERS_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} event/*.cpp)

add_executable(SmartFilamentSensor
        main.cpp
        pin_output.cpp
        event_controller.cpp
        events_handler.cpp
        sensor_management.cpp
        movement_sensor.cpp
        timer.cpp
        rgb_led.cpp
        ${EVENT_HANDLERS_SOURCES}
        )


set_target_properties(
    SmartFilamentSensor
    PROPERTIES
        OUTPUT_NAME "${PROJECT_NAME}-${VERSION}"
)

pico_set_program_name(SmartFilamentSensor "SmartFilamentSensor")
pico_set_program_version(SmartFilamentSensor "0.1")

pico_enable_stdio_usb(SmartFilamentSensor 1)
pico_enable_stdio_uart(SmartFilamentSensor 0)

# pull in common dependencies
target_link_libraries(SmartFilamentSensor
        hardware_pio
        pico_stdlib
        )

# create map/bin/hex file etc.
pico_add_extra_outputs(SmartFilamentSensor)
