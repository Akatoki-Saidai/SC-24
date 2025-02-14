#include "s35.hpp"
#include "pico/stdlib.h"
#include <iostream>

int main() {
    // サンプルコード
    S35 s35(18,50);

    // サーボ動作開始
    s35.start();
    sleep_ms(5000);

    // 左回転
    std::cout << "left turn!!" << std::endl;
    s35.left_turn();
    sleep_ms(5000);

    // 右回転
    std::cout << "right turn!!" << std::endl;
    s35.right_turn();
    sleep_ms(5000);
    
    std::cout << "stop turn!!" << std::endl;
    s35.stop_turn();

    // サーボ動作停止
    s35.stop();

    return 0;
}