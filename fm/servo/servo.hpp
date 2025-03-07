#ifndef SC24_FM_S35_HPP_
#define SC24_FM_S35_HPP_

#include <cmath>
#include <iostream>

#include "hardware/gpio.h"
#include "hardware/pwm.h"
#include "pico/stdlib.h"

#include "../flash/flash.hpp"

class Servo {
public:
  Servo(Flash &flash, int pin = 18, int freq = 50); // コンストラクタ
  ~Servo();                                         // デストラクタ

  void start() const;
  void stop() const;
  void left_turn() const;
  void right_turn() const;
  void stop_turn() const;
  void test_turn() const;

private:
  Flash &_flash; // 出力用のフラッシュメモリ

  int pin;
  int freq;
  Flash f;
};

#endif // SC24_FM_S35_HPP_