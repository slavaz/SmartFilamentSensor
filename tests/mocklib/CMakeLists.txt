add_library(mocklib SHARED
        clocks.cpp
        gpio.cpp
        pio.cpp
        time.cpp
        )
include_directories (./)
