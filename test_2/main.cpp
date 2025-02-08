#include "SG90.hpp"
#include "pico/stdlib.h"
#include <iostream>

int main() {
    // サンプルコード
    SG90 sg90(18,-90,90,0,50);

    // サーボ動作開始
    sg90.start();
    sleep_ms(5000);

    // 現在の角度を表示
    std::cout << "Current angle: " << 0 << std::endl;

    sg90.setAngle(40);
    sleep_ms(5000);

    // 初期位置に移動
    sg90.setIniAngle();
    sleep_ms(3000);

    // 現在の角度を表示
    std::cout << "Angle after initialization: " << 0 << std::endl;
    sleep_ms(3000);

    // サーボ動作停止
    sg90.stop();

    return 0;
}