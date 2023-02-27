add_library(mocklib SHARED
        clocks.cpp
        gpio.cpp
        mocklib.cpp
        pio.cpp
        time.cpp
        )
include_directories (./)
