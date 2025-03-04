# ビルドを実行するファイルを追加
add_library(Servo STATIC
    ${CMAKE_CURRENT_LIST_DIR}/servo.cpp
)
# 以下の資料を参考にしました
# https://qiita.com/kikochan/items/732e46e92e7f29c18ce9
# https://qiita.com/shohirose/items/45fb49c6b429e8b204ac

# ライブラリの読み込み
target_link_libraries(Servo
    pico_stdlib
    hardware_gpio
    hardware_pwm
    hardware_flash
)

# # CMake最小バージョン設定
# cmake_minimum_required(VERSION 3.12)

# # プログラミング言語を設定
# set(CMAKE_C_STANDARD 11)
# set(CMAKE_CXX_STANDARD 17)

# # Pico-SDKのパスを設定 (環境によって違う)
# # set(PICO_SDK_PATH "C:/Pico/pico-sdk")

# # SDKの読み込み (プロジェクトに関する設定の前にある必要がある)
# include(pico_sdk_import.cmake)

# # プロジェクトを設定
# project(test C CXX ASM)

# # Pico SDKの初期化
# pico_sdk_init()

# # ソースコードのファイルを指定
# add_executable(test_project
#     servo.cpp
# )

# # Pico SDKのライブラリとリンク
# target_link_libraries(test_project pico_stdlib hardware_pwm hardware_gpio)

# # USB出力を有効にし，UART出力を無効にする
# pico_enable_stdio_usb(test_project 1)
# pico_enable_stdio_uart(test_project 0)

# # uf2ファイルの生成
# pico_add_extra_outputs(test_project)