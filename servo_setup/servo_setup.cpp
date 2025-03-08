#include <iostream>
#include <pico/time.h>

#include "pico/stdlib.h"

#include "servo/servo.hpp"

int main() {
  // ************************************************** //
  //                       setup                        //
  // ************************************************** //
  stdio_init_all();
  sleep_ms(005);

  Servo servo_l(27, 50); // 左のサーボ
  servo_l.start();
  Servo servo_r(26, 50); // 右のサーボ
  servo_r.start();

  sleep_ms(100);
  // ↓ここを変えて
  servo_r.right_turn();
  // servo_r.left_turn();
  // servo_l.right_turn();
  // servo_l.left_turn();
  sleep_ms(8000);

  // while (true) {
  //   sleep_ms(1000);
  // }
}
