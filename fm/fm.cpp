#include <hardware/gpio.h>

#include "fall_phase.hpp"
#include "flash/flash.hpp"
#include "goal_phase.hpp"
#include "wait_phase.hpp"

int main() {
  // ************************************************** //
  //                       setup                        //
  // ************************************************** //
  stdio_init_all();
  sleep_ms(2000);
  printf("stdio_init\n");

  // ジャイロ効果による安定化のためのモーターをセットアップ
  gpio_init(13);
  gpio_set_dir(13, GPIO_OUT);
  gpio_pull_down(13);
  gpio_put(13, false);

  // フラッシュメモリのセットアップ
  gpio_init(15);
  gpio_set_dir(15, GPIO_IN);
  gpio_pull_up(15);
  sleep_ms(100);
  Flash flash;
  // ピンをGNDに手動で繋げている場合
  if (gpio_get(15) == false) {
    printf("flash print\n");
    flash.print(); // フラッシュメモリに保存されている全データを出力
    return 0;
  }
  printf("flash NOT print\n");
  sleep_ms(10000);

  flash.clear(); // フラッシュメモリのデータをリセット
  flash.write("flash init ok\n");

  // SDカードのセットアップ
  // SD sd;

  Servo servo_l(flash, 27, 50); // 左のサーボ
  servo_l.start();
  Servo servo_r(flash, 26, 50); // 右のサーボ
  servo_r.start();

  // I2Cのセットアップ
  i2c_inst_t *const i2c_port = i2c1;
  constexpr uint8_t sda_pin = 14;
  constexpr uint8_t scl_pin = 15;
  i2c_init(i2c_port, 400 * 1000);
  gpio_set_function(sda_pin, GPIO_FUNC_I2C);
  gpio_set_function(scl_pin, GPIO_FUNC_I2C);
  gpio_pull_up(sda_pin);
  gpio_pull_up(scl_pin);

  // BMP280のセットアップ
  BMP280 bmp280(flash, i2c1);

  // BNO055のセットアップ
  BNO055 bno055(flash, i2c1);

  // UARTのセットアップ
  uart_init(uart0, 38400);
  gpio_set_function(0, GPIO_FUNC_UART);
  gpio_set_function(1, GPIO_FUNC_UART);

  // GPSのセットアップ
  GPS gps(flash, uart0);

  Phase phase = Phase::Fall; ////////////////////////////

  // ************************************************** //
  //                        loop                        //
  // ************************************************** //
  printf("測定を開始します\n");
  sleep_ms(1000);
  while (true) {
    try {
      // sleep_ms(100);
      // bmp280.read();
      //   bno055.read();

      //   gps.read();
      // servo_l.left_turn();
      // gpio_put(9, 1);
      // sleep_ms(2000);
      // servo_l.stop_turn();
      // servo_r.stop_turn();
      // sleep_ms(2000);
      // servo_l.right_turn();
      // servo_r.right_turn();
      // sleep_ms(2000);
      // servo_l.stop_turn();
      // servo_r.stop_turn();
      // sleep_ms(2000);
      // return 0;
      // sd.write("aiueo");
      // gpio_put(9, 0);

      switch (phase) {
      case Phase::Wait:
        wait_phase(phase, flash, bmp280, bno055);
        break;
      case Phase::Fall:
        fall_phase(phase, flash, bmp280, bno055, gps, servo_r, servo_l);
        break;
      case Phase::Goal:
        goal_phase(phase, flash, bmp280, bno055, gps, servo_r, servo_l);
        break;
      }
    } catch (const std::exception &e) {
      printf("%s", e.what());
      flash.write("%s", e.what());
    }
  }
}
