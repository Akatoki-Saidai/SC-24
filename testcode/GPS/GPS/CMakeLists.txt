#Add an executable target to be build from the source files
add_executable(gps NEMAParser.cpp main.cpp SerialConnection.cpp)

#Pull in our pico_stdlib which aggregates commonly used features
target_link_libraries(gps 
    pico_stdlib 
    hardware_gpio
    hardware_pwm
    hardware_uart
    )

#Enable USB output, disable UART output
pico_enable_stdio_usb(gps 1)
pico_enable_stdio_uart(gps 0)

#Create map/bin/hex/uf2 file etc.
pico_add_extra_outputs(gps)