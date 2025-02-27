# CMake最小バージョン設定
cmake_minimum_required(VERSION 3.12)

# プログラミング言語を設定
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Pico-SDKのパスを設定 (環境によって違う)
# set(PICO_SDK_PATH "C:/Pico/pico-sdk")

# SDKの読み込み (プロジェクトに関する設定の前にある必要がある)
include(pico_sdk_import.cmake)

# プロジェクトを設定
project(test C CXX ASM)


#以下fmからコピー

# 例外を有効にする
set(PICO_CXX_ENABLE_EXCEPTIONS 1)
set(PICO_CXX_ENABLE_RTTI 1)
# 以下の資料を参考にしました
# https://community.element14.com/products/raspberry-pi/b/blog/posts/raspberry-pico-and-cmake---enable-c-exceptions-and-rtti-run-time-type-information

# 警告レベルを上げる
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /EHsc")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++17")
endif()
# 以下の資料を参考にしました
# https://theolizer.com/cpp-school1/cpp-school1-7/#w4

#以上


# Pico SDKの初期化
pico_sdk_init()

# ソースコードのファイルを指定
add_executable(test_project
    s35_main.cpp
    s35.cpp
    s35.hpp
)

# Pico SDKのライブラリとリンク
target_link_libraries(test_project pico_stdlib hardware_pwm hardware_gpio)

# USB出力を有効にし，UART出力を無効にする
pico_enable_stdio_usb(test_project 1)
pico_enable_stdio_uart(test_project 0)

# uf2ファイルの生成
pico_add_extra_outputs(test_project)