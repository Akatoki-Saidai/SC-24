# ビルドを実行するファイルを追加
add_library(BMP280 STATIC
    ${CMAKE_CURRENT_LIST_DIR}/bmp280.cpp
)
# 以下の資料を参考にしました
# https://qiita.com/kikochan/items/732e46e92e7f29c18ce9
# https://qiita.com/shohirose/items/45fb49c6b429e8b204ac

# ライブラリの読み込み
target_link_libraries(BMP280
    pico_stdlib
    hardware_i2c
    hardware_flash
)


# cmake_minimum_required(VERSION 3.12)

# include(pico_sdk_import.cmake)

# project(project1 C CXX ASM)
# set(CMAKE_C_STANDARD 11)
# set(CMAKE_CXX_STANDARD 17)

# pico_sdk_init()

# add_executable(BMP280
#     bmp280.cpp
# )

# target_link_libraries(BMP280
#     pico_stdlib
#     hardware_i2c
# )

# pico_enable_stdio_usb(BMP280 1)
# pico_enable_stdio_uart(BMP280 0)

# pico_add_extra_outputs(BMP280)