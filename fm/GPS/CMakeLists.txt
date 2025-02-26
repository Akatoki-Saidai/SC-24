# ビルドを実行するファイルを追加
add_library(GPS STATIC
    ${CMAKE_CURRENT_LIST_DIR}/nema_parser.cpp
    ${CMAKE_CURRENT_LIST_DIR}/gps.cpp
)
# 以下の資料を参考にしました
# https://qiita.com/kikochan/items/732e46e92e7f29c18ce9
# https://qiita.com/shohirose/items/45fb49c6b429e8b204ac

# ライブラリの読み込み
target_link_libraries(GPS
    pico_stdlib
    hardware_uart
)


# cmake_minimum_required(VERSION 3.12)

# include(pico_sdk_import.cmake)

# project(project1 C CXX ASM)
# set(CMAKE_C_STANDARD 11)
# set(CMAKE_CXX_STANDARD 17)

# pico_sdk_init()

# add_executable(GPS
#     nema_parser.cpp
# )

# target_link_libraries(GPS
#     pico_stdlib
#     hardware_i2c
# )

# pico_enable_stdio_usb(GPS 1)
# pico_enable_stdio_uart(GPS 0)

# pico_add_extra_outputs(GPS)