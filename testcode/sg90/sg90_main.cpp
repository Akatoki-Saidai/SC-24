#include "sg90.hpp"
#include "pico/stdlib.h"
#include <iostream>

int main() {
    // サンプルコード
    stdio_init_all();    
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    gpio_put(PICO_DEFAULT_LED_PIN, 0);
    gpio_put(PICO_DEFAULT_LED_PIN, 1);
    sleep_ms(250);

    SG90 sg90(18,50);  // S35(int ピン番号,int 周波数)

    // サーボ動作開始
    sg90.start();
    gpio_put(PICO_DEFAULT_LED_PIN, 0);
    sleep_ms(500);
    gpio_put(PICO_DEFAULT_LED_PIN, 1);
    sleep_ms(5000);

    // // 左回転
    // std::cout << "left turn!!" << std::endl;
    // sg90.left_turn();
    // sleep_ms(5000);

    // // 右回転
    // std::cout << "right turn!!" << std::endl;
    // sg90.right_turn();
    // sleep_ms(5000);
    
    // std::cout << "stop turn!!" << std::endl;
    // sg90.stop_turn();

    
    std::cout << "init" << std::endl;
    sg90.init_turn();
    sleep_ms(5000);

    std::cout << "right" << std::endl;
    sg90.turn(150);
    sleep_ms(5000);

    std::cout << "init" << std::endl;
    sg90.init_turn();
    sleep_ms(5000);

    std::cout << "left" << std::endl;
    sg90.turn(0);
    sleep_ms(5000);

    std::cout << "init" << std::endl;
    sg90.init_turn();
    sleep_ms(5000);

    // サーボ動作停止
    sg90.stop();

    return 0;
}