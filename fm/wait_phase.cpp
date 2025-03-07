#include "wait_phase.hpp"

void wait_phase(Phase &phase, Flash &flash, BMP280 &bmp280, BNO055 &bno055) {
  // auto bmp_data = bmp280.read();
  // double altitude = bmp_data.altitude();
  auto bno_data = bno055.read(); //{accel,grv,mag}の順番で入っている想定
  auto bmp_data = bmp280.read();
  double accel_abs =
      abs(bno_data.accel[0]) + abs(bno_data.accel[1]) + abs(bno_data.accel[2]);
  static double max_alt = -9999;
  max_alt = std::max(max_alt, bmp_data.altitude);
  printf("accel_abs: %f\n", accel_abs);
  if (20 < accel_abs && 20 < bmp_data.altitude &&
      3 < max_alt - bmp_data.altitude && max_alt - bmp_data.altitude < 30) {
    phase = Phase::Fall;
    gpio_put(13, true);
    std::cout << "phase to fall!!" << std::endl;
    sleep_ms(5000);
  }
  sleep_ms(100);
}