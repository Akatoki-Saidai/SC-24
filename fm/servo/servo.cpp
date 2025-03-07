#include "servo.hpp"

Servo::Servo(Flash &flash, int pin, int freq)
    : _flash(flash), pin(pin), freq(freq) {}

Servo::~Servo() { stop(); }

void Servo::start() const {
  // gpio_init(pin);               // ピンの初期化
  // gpio_set_dir(pin, GPIO_OUT);  // 出力ピンとして設定

  // PWMの設定
  gpio_set_function(pin, GPIO_FUNC_PWM);
  uint slice_num = pwm_gpio_to_slice_num(pin);
  static pwm_config servo_slice_config = pwm_get_default_config();

  // pwm_config_set_clkdiv(&servo_slice_config, 100); // クロック分周 (50Hz)
  pwm_set_clkdiv(slice_num, 100); // クロック分周 (50Hz)
  // pwm_config_set_wrap(&servo_slice_config, 24999); // 1周期20ms
  pwm_set_wrap(slice_num, 24999); // 1周期20ms
  // pwm_init(slice_num, &servo_slice_config, true);
  pwm_set_enabled(slice_num, true); // PWMを有効化
  // 参考：https://rikei-tawamure.com/entry/2021/02/08/213335
  // pwm_set_wrapは(24999+1)/125000000[s]=20[ms]が一周期となる。詳しくは参考サイトのクロックの分割のところを参照。
  //  1周期の秒数 = ((ラップ + 1) * 分周比) / 125000000
}

void Servo::stop() const {
  uint slice_num = pwm_gpio_to_slice_num(pin);
  pwm_set_enabled(slice_num, false); // PWMを無効化
  gpio_set_dir(pin, GPIO_IN);        // ピンを入力に設定
}

// pwm_set_gpio_levelとpwm_set_chan_levelは迷ったけど、スライスがよくわかんなかったから一旦set使う
// 参考：https://raspberry.memo.wiki/d/PWM%C0%A9%B8%E6
// デューティサイクルの時に出てくる65535は16bitの最大値。picoのpwmが16bitのカウンタを使用してるらしい

void Servo::left_turn() const {
  printf("servo left_turn\n");
  _flash.write("servo left_turn\n");
  // パルス幅を設定(1000[us]~2000[us]で動作するらしい)
  double pulse_width = 2600; //[us]

  // uint slice_num = pwm_gpio_to_slice_num(pin);  //
  // これを使っていないのは本当に正常？

  // デューティカウントの計算
  uint duty_cycle =
      ((pulse_width / 20000) * (24999 + 1)) - 1; // duty比換算で0.1

  // PWMデューティサイクルの設定
  pwm_set_gpio_level(pin, duty_cycle); // 正規化されたデューティサイクル
}

void Servo::right_turn() const {
  printf("servo right_turn\n");
  _flash.write("servo right_turn\n");

  // パルス幅を設定(1000[us]~2000[us]で動作するらしい)
  double pulse_width = 1000; //[us]

  // uint slice_num = pwm_gpio_to_slice_num(pin);  //
  // これを使っていないのは本当に正常？

  // デューティカウントの計算
  uint duty_cycle = ((pulse_width / 20000) * (24999 + 1)) - 1;

  // PWMデューティサイクルの設定
  pwm_set_gpio_level(pin, duty_cycle); // 正規化されたデューティサイクル
}

void Servo::stop_turn() const {

  // パルス幅を設定(1000[us]~2000[us]で動作するらしい)
  double pulse_width = 1800; //[us]

  // uint slice_num = pwm_gpio_to_slice_num(pin);  //
  // これを使っていないのは本当に正常？

  // デューティカウントの計算
  uint duty_cycle = ((pulse_width / 20000) * (24999 + 1)) - 1;

  // PWMデューティサイクルの設定
  pwm_set_gpio_level(pin, duty_cycle); // 正規化されたデューティサイクル
}

void Servo::test_turn() const {

  for (int i = 200; i < 3200; i += 100) {
    // パルス幅を設定(1000[us]~2000[us]で動作するらしい)
    double pulse_width = i; //[us]
    printf("pulse_width: %f\n", pulse_width);

    // uint slice_num = pwm_gpio_to_slice_num(pin);  //
    // これを使っていないのは本当に正常？

    // デューティカウントの計算
    uint duty_cycle = ((pulse_width / 20000) * (24999 + 1)) - 1;

    // PWMデューティサイクルの設定
    pwm_set_gpio_level(pin, duty_cycle); // 正規化されたデューティサイクル
    sleep_ms(1000);
  }
}