add_executable(bmp280_i2c
        bmp280_i2c.c
        )

# Pull in our (to be renamed) simple get you started dependencies
target_link_libraries(bmp280_i2c pico_stdlib hardware_i2c)

#Enable USB output, disable UART output
pico_enable_stdio_usb(bmp280_i2c 1)
pico_enable_stdio_uart(bmp280_i2c 0)

# create map/bin/hex file etc.
pico_add_extra_outputs(bmp280_i2c)

