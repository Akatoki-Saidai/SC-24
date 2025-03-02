#ifndef SC24_FM_S35_HPP_
#define SC24_FM_S35_HPP_

#include <cmath>
#include <iostream>

#include "hardware/gpio.h"
#include "hardware/pwm.h"
#include "pico/stdlib.h"

class S35 {
public:
  S35(int pin = 18, int freq = 50); // コンストラクタ
  ~S35();                           // デストラクタ

  void start();
  void stop();
  void left_turn();
  void right_turn();
  void stop_turn();

private:
  int pin;
  int freq;
};

#endif // SC24_FM_S35_HPP_