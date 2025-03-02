#include "fm.hpp"

int main() {
  // ************************************************** //
  //                       setup                        //
  // ************************************************** //
  stdio_init_all();
  sleep_ms(2000);
  printf("init_ok\n");

  S35 s35_left(18, 50); // 左のサーボ
  s35_left.start();
  // S35 s35_right(18,50);//右のサーボ

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
  BMP280 bmp280(i2c1);

  // BNO055のセットアップ
  BNO055 bno055(i2c1);

  // UARTのセットアップ
  uart_init(uart0, 38400);
  gpio_set_function(0, GPIO_FUNC_UART);
  gpio_set_function(1, GPIO_FUNC_UART);

  // GPSのセットアップ
  GPS gps(uart0);

  Phase phase = Phase::Wait;

  // ************************************************** //
  //                        loop                        //
  // ************************************************** //
  while (true) {
    try {
      // sleep_ms(2000);
      // bmp280.read();
      // bno055.read();
      // gps.read();
      // s35_left.left_turn();
      // sleep_ms(2000);
      // s35_left.right_turn();

      switch (phase) {
      case Phase::Wait:
        wait_phase(phase, bmp280, bno055);
        break;
      case Phase::Fall:
        fall_phase(phase, bmp280, bno055, gps);
        break;
      case Phase::Goal:
        goal_phase(phase, bmp280, gps);
        break;
      }
    } catch (const std::exception &e) {
      printf("%s", e.what());
    }
  }
}