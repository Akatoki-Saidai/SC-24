#Add an executable target to be build from the source files
add_executable(SDcard main.cpp hw_config.c)

# Tell CMake where to find other source code
add_subdirectory(lib/no-OS-FatFS-SD-SPI-RPi-Pico/FatFs_SPI build)

#Pull in our pico_stdlib which aggregates commonly used features
target_link_libraries(SDcard 
    pico_stdlib 
    FatFs_SPI
    )

#Enable USB output, disable UART output
pico_enable_stdio_usb(SDcard 1)
pico_enable_stdio_uart(SDcard 0)

#Create map/bin/hex/uf2 file etc.
pico_add_extra_outputs(SDcard)