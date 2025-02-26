// #include "s35.hpp"

// int main() {
//     // サンプルコード
//     stdio_init_all();    
//     gpio_init(PICO_DEFAULT_LED_PIN);
//     gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
//     gpio_put(PICO_DEFAULT_LED_PIN, 0);
//     gpio_put(PICO_DEFAULT_LED_PIN, 1);
//     sleep_ms(250);

//     S35 s35(18,50);  // S35(int ピン番号,int 周波数)

//     // サーボ動作開始
//     s35.start();
//     gpio_put(PICO_DEFAULT_LED_PIN, 0);
//     sleep_ms(500);
//     gpio_put(PICO_DEFAULT_LED_PIN, 1);
//     sleep_ms(5000);

//     // 左回転
//     std::cout << "left turn!!" << std::endl;
//     s35.left_turn();
//     sleep_ms(5000);

//     // 右回転
//     std::cout << "right turn!!" << std::endl;
//     s35.right_turn();
//     sleep_ms(5000);
    
//     std::cout << "stop turn!!" << std::endl;
//     s35.stop_turn();

//     // サーボ動作停止
//     s35.stop();

//     return 0;
// }