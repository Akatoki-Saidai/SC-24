#include <array>
#include <cmath>
#include <iostream>
#include <math.h>
#include <vector>

#include "pico/stdlib.h"

#include "servo/servo.hpp"

int main() {
  // ************************************************** //
  //                       setup                        //
  // ************************************************** //
  stdio_init_all();
  sleep_ms(100);
  printf("init_ok\n");


  Servo servo_l(26, 50); // 左のサーボ
  servo_l.start();
  Servo servo_r(27, 50); // 右のサーボ
  servo_r.start();

  // ピンのセットアップ
  gpio_init(15);
  gpio_init(16);
  gpio_set_Dir(15. GPIO_IN);
  gpio_set_Dir(16. GPIO_IN);
  gpio_pull_up(15);
  gpio_pull_up(16);

  // ************************************************** //
  //                        loop                        //
  // ************************************************** //
  while (true) {
    try {
      if (gpio_get(15)) {
        servo_r.left_turn();
      } else {
        servo_r.stop_turn();
      }
      if (gpio_get(16)) {
        servo_l.left_turn();
      } else {
        servo_l.stop_turn();
      }
      sleep_ms(10);
    } catch (const std::exception &e) {
      printf("%s", e.what());
    }
  }
}
