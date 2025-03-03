#include <iostream>

#include "pico/stdlib.h"

#include "servo/servo.hpp"

int main() {
  // ************************************************** //
  //                       setup                        //
  // ************************************************** //
  stdio_init_all();
  sleep_ms(100);

  Servo servo_l(26, 50); // 左のサーボ
  servo_l.start();
  Servo servo_r(27, 50); // 右のサーボ
  servo_r.start();

  // ピンのセットアップ
  gpio_init(15);
  gpio_init(16);
  gpio_set_dir(15, GPIO_IN);
  gpio_set_dir(16, GPIO_IN);
  gpio_pull_up(15);
  gpio_pull_up(16);

  sleep_ms(1000);

  printf("init_ok\n");
  // ************************************************** //
  //                        loop                        //
  // ************************************************** //
  while (true) {
    try {
      uint i1 = gpio_get(15);
      uint i2 = gpio_get(16);
      printf("%d, %d\n", i1, i2);
      if (i1) {
        servo_r.stop_turn();
      } else {
        // servo_r.left_turn();
      }
      sleep_ms(1000);
      if (i2) {
        servo_l.stop_turn();
      } else {
        // servo_l.left_turn();
      }
      sleep_ms(1000);
    } catch (const std::exception &e) {
      printf("%s", e.what());
    }
  }
}
